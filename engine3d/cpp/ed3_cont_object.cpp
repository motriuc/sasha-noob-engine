/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_cont_object.cpp
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
#include "ed3_cont_object.h"
#include "ed3_obj_factory.h"

namespace Ed3 
{

//-------------------------------------------------------------------
d3ObjectContiner::d3ObjectContiner( ObjectType::ObjectType type ) :
	_BaseClass( type )
{
	_objectClass.SetAll();
}

//-------------------------------------------------------------------
void d3ObjectContiner::Initialize( Rd3::Render& render ) throws_error
{
	for( sInt i = 0; i < _objVector.Size(); i++ )
	{
		_objVector[i]->DoInitialize( render );
	}
	return _BaseClass::Initialize( render );
}

//-------------------------------------------------------------------
void d3ObjectContiner::Uninitialize( Rd3::Render& render )
{
	for( sInt i = 0; i < _objVector.Size(); i++ )
	{
		_objVector[i]->DoUninitalize( render );
	}
	
	_BaseClass::Uninitialize( render );
}
	
//-------------------------------------------------------------------
void d3ObjectContiner::Render( const d3RenderData& renderData )
{
	for( sInt i = 0; i < _objVector.Size(); i++ )
	{
		d3Object* pObj = _objVector[i];
		
		if( pObj->IsVisible() )     // [To do] check frustum and others
		{
			pObj->DoRender( renderData );
		}
	}
}

//-------------------------------------------------------------------
d3ObjectContiner::~d3ObjectContiner()
{
	for( sInt i = 0; i < _objVector.Size(); i++ )
		delete _objVector[i];
}

//-------------------------------------------------------------------
void d3ObjectContiner::Add( d3Object* pObj )
{
	__S_ASSERT( pObj != NULL );
	
	_objVector.Add( pObj );
	pObj->_parent = this;
	
	if( pObj->GetName().Length() > 0 )
	{
		if( !_objMap.Add( pObj->GetName(), pObj ) )
			Platform::ShowWarning( _S("Object :") + pObj->GetName() + _S(" is already used") );
	}
}


//-------------------------------------------------------------------
void d3ObjectContiner::AI( d3EngineData& edata )
{
	for( sInt i = 0; i < _objVector.Size(); i++ )
	{
		d3Object* pObj = _objVector[i];
		if( !pObj->IsSuspended() )
			pObj->DoAI( edata );
	}
}

//-------------------------------------------------------------------
void d3ObjectContiner::ComputeBoundingBox( d3AABBox& b )
{
	for( sInt i = 0; i < _objVector.Size(); i++ )
	{
		d3Object* pObj = _objVector[i];
		
		if( pObj->HasBoundingBox() )
			b.Add( pObj->GetBoundingBox() );
	}
}

//-------------------------------------------------------------------
sBool d3ObjectContiner::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( _BaseClass::LoadFromXMLSubnode( element, loadParams ) )
		return sTrue;

	if( element.GetName() == ELEMENT_CHILDREN )
	{
		for( sInt j = 0; j < element.GetChildCount(); j++ )
		{
			const Xml::BaseDomNode& subChild = element[j];
				
			if( !XmlCheckDef( subChild, loadParams.def ) )
				continue;
				
			d3Object* pObj = d3ObjectFactory_Create( subChild.GetName() );
				
			if( pObj == NULL )
			{
				Platform::ShowWarning( 
					_S("[d3ObjectContiner::LoadFromXML]: Unknown object ") + subChild.GetName()
				);
				continue;
			}
				
			try
			{
				pObj->DoLoadFromXML( subChild, loadParams );
			}
			catch( Errors::Error* error )
			{
				Platform::ShowWarning(
					_S("[d3ObjectContiner::LoadFromXML]: Can't load object, Type: <") + 
					subChild.GetName() + _S(">; Name: <") + subChild.GetName() + 
					_S("> Error: ") + error->ToString()
				);
				delete pObj;
				delete error;
				continue;
			}
			Add( pObj );
		}
		
		return sTrue;
	}
	
	return sFalse;
}

}