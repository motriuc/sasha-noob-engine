/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_resobj.cpp
//  Created                 : 20 1 2011   0:05
//  File path               : SLibF\render3d\cpp
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////
#include "rd3afx.h"
#include "rd3_resobj.h"
#include "rd3_render.h"

namespace Rd3
{

/************************************************************************/
/*                                                                      */
/************************************************************************/

ResourceObject::ResourceObject( Render* owner, const sString& objectName, ResourceType::ResourceType type ) :
	_objectType( type ),
	_objectName( objectName ),
	_pOwner( owner ),
	_objIndex( -1 ),
	_useCount( 1 )
{
	__S_ASSERT( _pOwner != NULL );
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void ResourceObject::UnuseResource() const
{
	if( System::Mt::Dec( _useCount ) == 0 )
	{
		if( _pOwner != NULL ) {
			_pOwner->NotifyFreeResource( const_cast<ResourceObject*>( this ) );
		}
		delete this;
	}
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/

ResourceObject::~ResourceObject()
{
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

TypedResourcePool::TypedResourcePool( ResourceType::ResourceType type ):
	_type( type )
{
	_objArray.Reserve( 32 );
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

TypedResourcePool::~TypedResourcePool()
{
#ifdef _DEBUG
	
	sString objNames;
	
	for( sInt i = 0; i < _objArray.Size(); i++ )
	{
		objNames += _objArray[i]->GetObjectName() + _S(";");
	}
	
	if( _objArray.Size() > 0 )
		System::Platform::ShowWarning( _S("Resources not freed: ") + objNames );
#endif	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

sBool TypedResourcePool::Add( ResourceObject* pResource )
{
	__S_ASSERT( pResource != NULL );

	if( pResource->GetResourceType() != _type || pResource->_objIndex != -1 )
		return sFalse;

	ResourceObject* pTmp;

	if( _objMap.Lookup( pResource->GetObjectName(), pTmp ) )
		return sFalse;
	
	_objMap[pResource->GetObjectName()] = pResource;
	pResource->_objIndex = _objArray.Add( pResource );

	return sTrue;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

sBool TypedResourcePool::Remove( const sString& name )
{
	ResourceObject* pResource = NULL;

	_objMap.Remove( name, pResource );

	if( pResource == NULL )
		return sFalse;

	__S_ASSERT( _objArray[pResource->_objIndex] == pResource );

	_objArray[pResource->_objIndex] = NULL;
	pResource->_objIndex = -1;

	return sTrue;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void TypedResourcePool::Free()
{
	for( sInt i = 0; i < _objArray.Size(); i++ )
		delete _objArray[i];

	_objArray.RemoveAll();
	_objMap.RemoveAll();
}


}