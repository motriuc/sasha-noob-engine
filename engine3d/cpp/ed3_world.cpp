////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_world.cpp
//  Created            : 20 1 2012   19:09
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//  Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////


#include "ed3afx.h"
#include "ed3_world.h"
#include "ed3_rdata.h"
#include "rd3_xml_def.h"
#include "rd3_edata.h"
#include "rd3_rstate.h"
#include "ed3_edata.h"

#ifdef ED3_ENGINE_USE_PHYSICS
	#include "ed3_physics_world.h"
#endif

namespace Ed3 
{

//-----------------------------------------------------------------------
d3World::d3World() :
	_BaseClass( ObjectType::E_WORLD )
#ifdef ED3_ENGINE_USE_PHYSICS
	,
	_physicsWorld( NULL )
#endif // ED3_ENGINE_USE_PHYSICS	
{
	_defaultRenderClass = _objectClassNames.GetClass( _S("default") );
}

//-----------------------------------------------------------------------
d3World::~d3World()
{
#ifdef ED3_ENGINE_USE_PHYSICS	
	delete _physicsWorld;
#endif // ED3_ENGINE_USE_PHYSICS	
}
	
//-----------------------------------------------------------------------
void d3World::Initialize( Rd3::Render& render ) throws_error
{
	_preRenders.Initialize( render );
	_BaseClass::Initialize( render );

#ifdef ED3_ENGINE_USE_PHYSICS
	if( _physicsWorld != NULL )
		_physicsWorld->Initialize();
#endif	
	
}

//-----------------------------------------------------------------------
void d3World::AI( d3EngineData& edata )
{
#ifdef ED3_ENGINE_USE_PHYSICS
	if( _physicsWorld != NULL )
		_physicsWorld->Simulate( edata.GetDeltaTime() );
#endif
	
	_BaseClass::AI( edata );
}
	
//-----------------------------------------------------------------------
void d3World::LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( loadParams.pClassNames == NULL )
		loadParams.pClassNames = &_objectClassNames;
		
	_BaseClass::LoadFromXML( element, loadParams );
}
	
//-----------------------------------------------------------------------
sBool d3World::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
#ifdef ED3_ENGINE_USE_PHYSICS		
	if( element.GetName() == ELEMENT_PHYSICS_WORLD )
	{
		LoadPhysicsFromXml( element, loadParams );
		return sTrue;
	}
#endif // ED3_ENGINE_USE_PHYSICS
	
	if( _BaseClass::LoadFromXMLSubnode( element, loadParams ) )
		return sTrue;
	
	if( element.GetName() == ELEMENT_RESOURCES ) 
	{
		_resources.LoadFromXML( element, loadParams );
		return sTrue;
	}
	
	if( element.GetName() == ELEMENT_LIGHTS_STATIC )
	{
		_staticLights.LoadFromXml( element, loadParams.def );
		return sTrue;
	}
	
	if( element.GetName() == ELEMENT_CAMERA )
	{
		Rd3::XmlLoad_Camera( _camera, element, loadParams.def );
		return sTrue;
	}
	
	if( element.GetName() == ELEMENT_PRERENDER )
	{
		_preRenders.LoadFromXML( element, loadParams );
		return sTrue;
	}
	
	if( element.GetName() == ELEMENT_AFTER_EFFECT )
	{
		SetAfterEffect( loadParams.render.UseAfterEffect( element.GetAttributes()[ATTR_NAME] ) );
		return sTrue;
	}	
	
	return sFalse;
}

//-----------------------------------------------------------------------
void d3World::SetAfterEffect( Rd3::AfterEffect* p )
{
	_afterEffect = p;
}
		
//-----------------------------------------------------------------------
void d3World::RenderWorld( Rd3::WorldRenderState& rstate, Rd3::EngineDataForRender& edata )
{
	_preRenders.Render( rstate, edata, *this );
	
	rstate.SetAfterEffect( _afterEffect );
	rstate.SetCamera( GetCamera() );

	rstate.BeginWorldRender( edata );
	
	d3RenderData renderData( &rstate, _defaultRenderClass );
	DoRender( renderData );
	
	rstate.EndWorldRender();
}	

#ifdef ED3_ENGINE_USE_PHYSICS

//-----------------------------------------------------------------------
d3PhysicsWorld& d3World::Physics()
{
	if( _physicsWorld == NULL )
		_physicsWorld = new d3PhysicsWorld();
	
	return *_physicsWorld;
}
	
//-----------------------------------------------------------------------
void d3World::LoadPhysicsFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams )
{	
	loadParams.pPhysicsWorld = &Physics();
	
	d3Vector gravity( 0.0f, -10.0f, 0.0f );
	
	for( sInt i = 0; i < element.GetChildCount(); i++ )
	{
		const Xml::BaseDomNode& childElement = element[i];
		
		if( !Rd3::XmlCheckDef( childElement, loadParams.def ) )
			continue;
		
		if( childElement.GetName() == ELEMENT_GRAVITY )
		{
			Rd3::XmlLoad_Vector( gravity, childElement, loadParams.def );
		}
		// else if 
	}
	
	Physics().SetGravityVector( gravity );
}
	
#endif // ED3_ENGINE_USE_PHYSICS
	
	
}