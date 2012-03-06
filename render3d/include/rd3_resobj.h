/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_resobj.h
//  Created                 : 20 1 2011   0:05
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
#ifndef _RD3_RESOBJ_H_
#define _RD3_RESOBJ_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

namespace Rd3
{

using namespace System::Cnt;

/**
 * forward declarationss
 */
class Render;
class TypedResourcePool;
/**
 * Resource Object
 */
class ResourceObject
{
public:
	/**
	 * Return resource type
	 */
	ResourceType::ResourceType GetResourceType() const;

	/**
	 *
	 */
	const sString& GetObjectName() const;

	/**
	 *
	 */
	sInt GetResourceIndex() const;

	/**
	 * returns owner render
	 */
	Render* GetOwner() const;
	
	/**
	 *
	 */
	void UseResource() const;
	
	/**
	 *
	 */
	void UnuseResource() const;

	/**
	 * called if device was reset
	 */
	 virtual void OnReset() {}
protected:
	/**
	 * constructor
	 */ 
	ResourceObject( Render* owner, const sString& objectName, ResourceType::ResourceType type );
	
	/**
	 * destructor
	 */
	virtual ~ResourceObject();
private:
	ResourceType::ResourceType  _objectType;
	sString                     _objectName;
	Render*						_pOwner;
	sInt						_objIndex;
	mutable sInt				_useCount;

	friend class TypedResourcePool;
};
	
/**
 *	Resource 
 */
class TypedResourcePool
{
public:
	/**
	 *
	 */
	TypedResourcePool( ResourceType::ResourceType type );

	/**
	 * Retun FALSE if object with this name already exists
	 */
	sBool Add( ResourceObject* pResource );

	/**
	 * 
	 */
	sBool Remove( const sString& name );

	/**
	 * 
	 */
	void Free();

	/**
	 * 
	 */
	ResourceObject* operator[]( const sString& name );

	/**
	 *
	 */
	ResourceObject* operator[]( const sInt objectId );

	/**
	 *
	 */
	sInt GetObjectCount() const;

	/**
	 *
	 */
	~TypedResourcePool();

private:
	sVector< ResourceObject*>		_objArray;
	sMap<sString, ResourceObject*>  _objMap;
	ResourceType::ResourceType		_type;
};

	
/**
 * use_resource
 */
template< typename _ResType >
class use_resource
{
public:
	inline use_resource() :
		_res( NULL )
	{
	}
	
	inline use_resource( _ResType* pRes ) :
		_res( pRes )
	{
		AddUse();
	}
	
	inline use_resource( const use_resource<_ResType>& src ):
		_res( src._res )
	{
		AddUse();
	}
	
	inline void ResourceCreate( _ResType* pRes )
	{
		__S_ASSERT( _res != pRes );
		__S_ASSERT( pRes != NULL );
		
		Release();
		_res = pRes;
	}
	
	inline void ResourceFree()
	{
		Release();
		_res= NULL;
	}
	
	
	inline void operator = ( const use_resource<_ResType>& src )
	{
		if( &src != this ) 
		{
			Release();
			_res = src._res;
			AddUse();
		}
	}

	inline void operator = ( _ResType* pRes )
	{
		if( _res != pRes ) 
		{
			Release();
			_res = pRes;
			AddUse();
		}
	}
	
	inline ~use_resource()
	{
		Release();
	}
	
	operator _ResType*()
	{
		return _res;
	}

	operator const _ResType*() const
	{
		return _res;
	}
	
	inline _ResType& operator()()
	{
		__S_ASSERT( _res != NULL );
		return *_res;
	}

	inline const _ResType& operator()() const
	{
		__S_ASSERT( _res != NULL );
		return *_res;
	}
	
private:	
	_ResType*	_res;
	
	inline void Release()
	{
		if( _res != NULL )
			_res->UnuseResource();
	}
	
	inline void AddUse()
	{
		if( _res != NULL )
			_res->UseResource();
	}
	
};
	
#include "rd3_resobj.inl"
}


#endif // _RD3_RESOBJ_H_