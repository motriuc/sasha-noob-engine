/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_object.cpp
//  Created             : 19 1 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\cpp
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////

#include "ed3afx.h"
#include "ed3_object.h"
#include "ed3_rdata.h"
#include "rd3_rstate.h"
#include "ed3_cont_object.h"
#include "ed3_world.h"
#include "rd3_light_sel.h"

#ifdef ED3_ENGINE_USE_PHYSICS
	#include "ed3_physics_shape.h"
	#include "ed3_physics_world.h"
#endif

namespace Ed3 
{

//--------------------------------------------------------------------------------------------------------
d3Object::d3Object( ObjectType::ObjectType type, const sString& name ) :

#ifdef ED3_ENGINE_USE_PHYSICS	
	_phAutoShape( NULL ),
#endif	

#ifdef ED3_ENGINE_USE_LUA
	_luaObject( this ),
	_luaHasAI( sFalse ),
	_luaHasInit( sFalse ),
#endif
	
	_objectState( OBS_VISIBLE ),
	_objectActionState( OBAS_IDLE ),
	_transformationMatrix( 1.0f ),
	_parent( NULL ),
	_boundingBox( d3AABBox::GetEmpty() ),
	_name( name ),
	_type( type )
{
}

//--------------------------------------------------------------------------------------------------------
void d3Object::ComputeBoundingBox( d3AABBox& b )
{
}

//--------------------------------------------------------------------------------------------------------
void d3Object::Initialize( Rd3::Render& render )
{
	if( !HasState( OBS_BOUNDINGBOX ) && HasState( OBS_COMPUTE_AUTO_BBOX ) )
	{
		_boundingBox.Empty();
		
		ComputeBoundingBox( _boundingBox );
		
		if( !_boundingBox.IsEmpty() ) 
			AddState( OBS_BOUNDINGBOX );
	}	
}

//--------------------------------------------------------------------------------------------------------
void d3Object::DoLoadFromXMLFile( const sString& path, LoadDataParams& loadParams ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( loadParams.archive.Open( path ) ); 
	ptr_unique<Xml::DomDocument> pDoc( Xml::DomDocument::Read( &pStream() ) );
	
	DoLoadFromXML( pDoc().GetRoot(), loadParams );
}
	
//--------------------------------------------------------------------------------------------------------
void d3Object::LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	_name = element.GetAttributes()[ATTR_NAME];
		
	if( loadParams.pClassNames != NULL )
	{
		sString cls = element.GetAttributes()[ATTR_CLASS];
		if( cls.Length() > 0  )
			_objectClass.Add( loadParams.pClassNames->GetClassFromString( cls ) );
		else
			_objectClass.Add( loadParams.pClassNames->GetClass( _S("default") ) );
	}
	
	for( sInt i = 0; i < element.GetChildCount(); i++ )
	{
		const Xml::BaseDomNode& childElement = element[i];
		
		if( !Rd3::XmlCheckDef( childElement, loadParams.def ) )
			continue;
		
		LoadFromXMLSubnode( childElement, loadParams );
	}
	
#ifdef ED3_ENGINE_USE_LUA	
	LoadLua( element.GetAttributes()[ATTR_LUA], loadParams );
#endif	
}

//--------------------------------------------------------------------------------------------------------
sBool d3Object::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( element.GetName() == ELEMENT_TRANSFORMATION )
	{
		Rd3::XmlLoad_Transformation( _transformationMatrix, element, loadParams.def );
		_objectState |= OBS_TRANSFORMATION_MATRIX;
		return sTrue;
	}
	
	if( element.GetName() == ELEMENT_LIGHTS_STATIC_USE )
	{
		AddState( OBS_USE_WORLD_STATIC_LIGHTS );
		return sTrue;
	}
	
	if( element.GetName() == ELEMENT_BBOX )
	{
		if( element.GetAttributes()[ATTR_TYPE] == "auto" )
			AddState( OBS_COMPUTE_AUTO_BBOX );
		
		return sTrue;
	}
	
#ifdef ED3_ENGINE_USE_PHYSICS
	if( element.GetName() == ELEMENT_PHYSICS_SHAPES )
	{
		LoadFromXML_PhysicsShapes( element, loadParams );
		return sTrue;
	}
#endif // ED3_ENGINE_USE_PHYSICS
	
	return sFalse;
}
	
#ifdef ED3_ENGINE_USE_PHYSICS
//--------------------------------------------------------------------------------------------------------
void d3Object::LoadFromXML_PhysicsShapes( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( loadParams.pPhysicsWorld == NULL )
		error_throw_arg( Errors::StringError )
			_S("Physics world is NULL :")
		);
	
	for( sInt i = 0; i < element.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& childElement = element[i];
		
		if( !Rd3::XmlCheckDef( childElement, loadParams.def ) )
			continue;
		
		if( childElement.GetName() == ELEMENT_SHAPE )
		{
			sString type = childElement.GetAttributes()[ATTR_TYPE];
			
			phShape* pShape = phShape::Create( type, this );
			
			if( pShape == NULL )
				error_throw_arg( Errors::StringError )
					_S("Invalid physics shape type :") + type
				);
			
			try 
			{
				pShape->LoadFromXml( childElement, loadParams );
			}
			catch (...) {
				delete pShape;
				throw;
			}
			
			loadParams.pPhysicsWorld->AddShape( pShape );
			
			if( childElement.GetAttributes()[ATTR_PARENT_ATTACH] == _S("true") )
			{
				_phAutoShape = pShape;
			}
		}
	}
}
#endif // ED3_ENGINE_USE_PHYSICS
	
//--------------------------------------------------------------------------------------------------------
void d3Object::ApplyLights( const d3RenderData& renderData )
{
	sBool staticLight = HasState( OBS_USE_WORLD_STATIC_LIGHTS );
	
	if( staticLight )
	{
		d3World* pWorld = GetWorld();
		__S_ASSERT( pWorld != NULL );
			
		Rd3::LightSelection	objectLights( renderData.rstate().MaxLightCount() );
		
		d3Vector pos;
		d3Vector::Mul( pos, d3Vector( 0.0f ), renderData.rstate().GetTransformation() );
		
		// to do
		objectLights.SetPosition( pos );
		
		const Rd3::LightList& lights = pWorld->GetStaticLights();
		
		objectLights.AddLight( lights );
		
		ApplyLights( renderData, objectLights );
	}
}
	
//--------------------------------------------------------------------------------------------------------
void d3Object::ApplyLights( const d3RenderData& renderData, const Rd3::LightSelection& lights )
{
	for( sInt i = 0; i < lights.Size(); ++i )
	{
		renderData.rstate().SetLight( i, lights[i] );
	}
}

//--------------------------------------------------------------------------------------------------------
void d3Object::GetAbsoluteTransformationMatrix( d3Matrix& m ) const
{
	if( !HasTransformationMatrix( ) )
	{
		if( GetParent() != NULL )
			GetParent()->GetAbsoluteTransformationMatrix( m );
		
		m = d3Matrix( 1.0f );
	}
	else
	{
		m = GetTransformationMatrix();
		
		if( GetParent() != NULL )
		{
			d3Matrix mp;
			GetParent()->GetAbsoluteTransformationMatrix( mp );
			m *= mp;
		}
	}
	
}
	
//--------------------------------------------------------------------------------------------------------
void d3Object::DoRender( const d3RenderData& renderData )
{
	__S_ASSERT( _objectActionState == OBAS_IDLE );
	
	if( !renderData.RenderObject( _objectClass ) )
		return;
	
	SetActionState( OBAS_RENDER );
	
	d3Matrix renderMatrix;
	const d3Matrix* swapMatrix = NULL;
	
	Rd3::RenderState& render = renderData.rstate();

#ifdef ED3_ENGINE_USE_PHYSICS
	if( _phAutoShape != NULL ) 
	{
		_phAutoShape->GetTransformation( renderMatrix );
		swapMatrix = render.SetTransformation( &renderMatrix );
	}
	else
	{
#else
	{
#endif
		// apply transformation matrix
		if( HasTransformationMatrix() )
		{
			renderMatrix = GetTransformationMatrix();
		
			// Set new render matrix
			swapMatrix = render.AddTransformation( &renderMatrix );
		}
	}
	
	sBool bRender = sTrue;
	if( HasState( OBS_BOUNDINGBOX ) 
#ifdef _D3_DEBUG_RENDER
	   && render.GetCommonData().debug_TestBoundingBox() 
#endif
	   )
	{
		d3AABBox b;
		d3AABBox::Mul( b, _boundingBox, renderMatrix );
		bRender = render.GetFrustum().Intersect( b );
	}
	
	if( bRender )
	{
		ApplyLights( renderData );
		Render( renderData );		
	}
	
	if( swapMatrix != NULL )
	{
		// restore old render matrix
		render.SetTransformation( swapMatrix );
	}
	__S_ASSERT( _objectActionState == OBAS_RENDER );
	SetActionState( OBAS_IDLE );
}

//--------------------------------------------------------------------------------------------------------
d3Object::~d3Object()
{
}

//--------------------------------------------------------------------------------------------------------
d3World* d3Object::GetWorld()
{
	d3ObjectContiner* pParent = GetParent();
	
	while( pParent != NULL )
	{
		if( pParent->GetType() == ObjectType::E_WORLD )
			return reinterpret_cast<d3World*>( pParent );
		
		pParent = pParent->GetParent();
	}
	
	return NULL;
}
	
}
