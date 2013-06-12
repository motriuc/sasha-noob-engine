/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_ptr_weak.h
//  Created                 : 18 1 2012   18:12
//  File path               : SLibF\system\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 100%
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
 * Weak pointer implementation class
 *
 * RATING( %%- )
 */
template< typename _Type >
class ptr_weak : public ptr_base_ref< _Type >
{
private:
	typedef ptr_base_ref< _Type > _BaseClass;
public:
	/**
	 * Default constructor
	 *
	 * RATING( +-- )
	 */
	ptr_weak() :
		_BaseClass()
	{
	}

	/**
	 * copy constructor from ptr_shared
	 *
	 * RATING( +-- )
	 */
	ptr_weak( const ptr_shared< _Type >& src )
	{
		_BaseClass::AssignWeak( src );
	}

	/**
	 * copy constructor from pre_weak
	 *
	 * RATING( +-- )
	 */
	ptr_weak( const ptr_weak< _Type >& src )
	{
		_BaseClass::AssignWeak( src );
	}

#ifdef _SLIB_CPP11
	/**
	 * move constructor
	 */
	ptr_weak( const ptr_weak< _Type >&& src )
	{
		_BaseClass::operator = ( src );
		src.Reset();
	}

#endif

	void operator = ( const ptr_shared< _Type >& src )
	{
		if( _BaseClass::ReleaseWeak() )
			_BaseClass::Reset();
		_BaseClass::AssignWeak( src );
	}

	void operator = ( const ptr_weak< _Type >& src )
	{
		if( _BaseClass::operator == ( src ) )
			return;

		if( _BaseClass::ReleaseWeak() )
			_BaseClass::Reset();
		_BaseClass::AssignWeak( src );
	}

	System::Types::sBool operator == ( const ptr_weak< _Type >& src ) const
	{
		src.IsNull(); // will update the null value for weak ref 
		IsNull(); // // will update the null value for weak ref

		return _BaseClass::operator == ( src );
	}

	System::Types::sBool operator == ( const ptr_shared< _Type >& src ) const
	{
		return src == *this;
	}

	/**
	 * Returns TRUE if pointer is NULL
	 *
	 * RATING( +-- )
	 */
	System::Types::sBool IsNull() const
	{
		_BaseClass::CheckWeakRef();
		return _BaseClass::IsNull();
	}

	/**
	 * Destructor
	 *
	 * RATING( +-- )
	 */
	~ptr_weak()
	{
		_BaseClass::ReleaseWeak();
	}
};