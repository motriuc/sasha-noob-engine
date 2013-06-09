/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_ptr_unique.h
//  Created                 : 18 1 2012   18:12
//  File path               : SLibF\system\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 * ptr_unique
 *
 * Implements a uniques ptr witch is used only in local context
 * Ex:
 *   ptr_unique<MyObject> obj( new MyObject( ... ) ); 
 */
template< typename _Type >
class ptr_unique : public ptr_base<_Type>, private class_nocopy
{
private:
	typedef ptr_base<_Type> _BaseClass;
public:
	ptr_unique( _Type* p ) :
		_BaseClass( p )
	{
	}
	
	~ptr_unique()
	{
		_BaseClass::Release();
	}

	using _BaseClass::operator->;
	using _BaseClass::operator*;
	using _BaseClass::operator();
	using _BaseClass::IsNull;
};

/**
 * ptr_array_unique
 */
template< typename _Type >
class ptr_array_unique : private class_nocopy
{
public:
	ptr_array_unique( _Type* p ) :
		_p( p )
	{
		__S_ASSERT( _p != NULL );
	}
	
	operator _Type*()
	{
		return _p;
	}
	
	_Type* ptr()
	{
		return _p;
	}
	
	_Type* ptr( System::Types::sInt offset )
	{
		return _p + offset;
	}
	
	inline ~ptr_array_unique()
	{
		delete[] _p;
	}
private:
	_Type*	_p;
};

