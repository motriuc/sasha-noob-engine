/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_object.h
//  Created                 : 26 6 2007   22:32
//  File path               : SLibF\system\include
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

// _use_sObject_

#ifndef _S_SYSTEM_OBJECT_INC_
#define _S_SYSTEM_OBJECT_INC_

namespace Obj
{
using namespace Types;


/**
 * Interface that describe the class information of an Object
 */
class IType
{
public:
	/**
	 * Get Class name
	 * @return class name
	 */
	virtual const sChar* GetClassName() const = 0;

	/**
	 * Get Namespace name
	 * @return namespace name
	 */
	virtual const sChar* GetNamespace() const = 0;

	/**
	 * Get parent class of courent class
	 * @return class parent
	 */
	virtual IType* GetParent() = 0;

	/**
	 * Get parent class of courent class
	 * @return class parent
	 */
	virtual const IType* GetParent() const = 0;

	/**
	 * Check type of class
	 * @return TRUE if it is of type IType
	 */
	sBool Is( const IType* pType ) const;

	/**
	 *	Check real class type 
	 */
	sBool IsReal( const IType* pType ) const;
};

/**
 *	SLIB Runtimed object
 */
class Object
{
	_SLIB_RUNTIME_BASE( System::Obj, Object )
protected:
	Object() {}
public:
	/**
	 *	Destructor
	 */
	virtual ~Object() {}

	/**
	 * Compute Object hash code
	 * @return object hash code
	 */
	virtual sUInt GetHashCode()	const					{ return reinterpret_cast<sUInt>(this); }

	/**
	 * Object to String
	 */
	virtual sString ToString()	const					{ return sString( _S("Object") ); }

	/**
	 * Check Class Type
	 */
	sBool Is( const IType* pType ) const;

	/**
	 * returns if class real type is pType
	 */
	sBool IsReal( const IType* pType ) const;

	/**
	 *	dispatch an object message
	 */
	virtual sBool Dispatch( Message& msg )				{ return sFalse; }

	/**
	 * type safe casts
	 */
	template< typename __TYPE >
	inline __TYPE* CastTo()
	{
		if( Is( TYPE( __TYPE ) ) )
			return static_cast<__TYPE*>( this );
		return NULL;
	}

	template< typename __TYPE >
	inline const __TYPE* CastTo() const
	{
		if( Is( TYPE( __TYPE ) ) )
			return static_cast<const __TYPE*>( this );
		return NULL;
	}

};

/**
 *	base class for Message objects
 */
class Message : public Object
{
	_SLIB_RUNTIME( System::Obj, Message, System::Obj::Object )
public:
};

#include "s_system_object.inl"
}

#endif // _S_SYSTEM_OBJECT_INC_
