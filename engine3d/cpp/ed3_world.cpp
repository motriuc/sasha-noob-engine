////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_world.cpp
//	Created            : 20 1 2012   19:09
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
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

namespace Ed3 
{

//-----------------------------------------------------------------------
d3World::d3World() :
	_BaseClass( ObjectType::E_WORLD )
{
	_defaultRenderClass = _objectClassNames.GetClass( _S("default") );
}

//-----------------------------------------------------------------------
void d3World::Initialize( Rd3::Render& render ) throws_error
{
	_preRenders.Initialize( render );
	_BaseClass::Initialize( render );
}

//-----------------------------------------------------------------------
void d3World::LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( loadParams.pClassNames == NULL )
	{
		loadParams.pClassNames = &_objectClassNames;
	}
	
	_BaseClass::LoadFromXML( element, loadParams );
}
	
//-----------------------------------------------------------------------
sBool d3World::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
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
	
	return sFalse;
}

//-----------------------------------------------------------------------
void d3World::RenderWorld( Rd3::WorldRenderState& rstate, Rd3::EngineDataForRender& edata )
{
	_preRenders.Render( rstate, edata, *this );
	
	rstate.SetCamera( GetCamera() );
	
	rstate.BeginWorldRender( edata );
	
	d3RenderData renderData( &rstate, _defaultRenderClass );
	DoRender( renderData );
	
	rstate.EndWorldRender();
}	

}