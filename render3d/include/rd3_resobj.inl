/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_resobj.inl
//  Created                 : 23 1 2011   22:56
//  File path               : SLibF\render3d\include
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

inline void ResourceObject::UseResource() const
{
	System::Mt::Inc( _useCount );
}

inline Render* ResourceObject::GetOwner() const
{
	__S_ASSERT( _pOwner != NULL );
	return _pOwner;
}

inline const sString& ResourceObject::GetObjectName() const
{
	return _objectName;
}

inline sInt ResourceObject::GetResourceIndex() const
{
	return _objIndex;
}

inline ResourceType::ResourceType ResourceObject::GetResourceType() const
{
	return _objectType;
}

inline Quality::Quality ResourceObject::GetQuality() const
{
	return _quality;
}

//////////////////////////////////////////////////////////////////////////////

inline sInt TypedResourcePool::GetObjectCount() const
{
	return _objArray.Size();
}

inline ResourceObject* TypedResourcePool::operator[]( const sString& name )
{
	ResourceObject* result = NULL;
	_objMap.Lookup( name, result );
	return result;
}

inline ResourceObject* TypedResourcePool::operator[]( const sInt objectId )
{
	return _objArray[objectId];
}


