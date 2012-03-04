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
 */
template< typename _Type >
class ptr_unique : private class_nocopy
{
public:
	inline ptr_unique( _Type* p ) :
		_p( p )
	{
	}
	
	inline _Type& operator()()
	{
		__S_ASSERT( _p != NULL );
		return *_p;
	}
	
	inline System::Types::sBool IsNull() const 
	{
		return _p == NULL;
	}
	
	inline ~ptr_unique()
	{
		delete _p;
	}
private:
	_Type*	_p;
};

/**
 * ptr_array_unique
 */
template< typename _Type >
class ptr_array_unique : private class_nocopy
{
public:
	inline ptr_array_unique( _Type* p ) :
		_p( p )
	{
		__S_ASSERT( _p != NULL );
	}
	
	inline operator _Type*()
	{
		return _p;
	}
	
	inline _Type* ptr()
	{
		return _p;
	}
	
	inline ptr_array_unique()
	{
		delete[] _p;
	}
private:
	_Type*	_p;
};

