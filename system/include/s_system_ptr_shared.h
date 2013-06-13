/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_ptr_shared.h
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

template< typename _Type> class ptr_weak;

/**
 * Shared pointer
 * RATING( %%- )
 */
template< typename _Type >
class ptr_shared : public ptr_base_ref< _Type >
{
private:
	typedef ptr_base_ref< _Type > _BaseClass;
public:
	/**
	 * Default constructor
	 *
	 * RATING( +-- )
	 */
	ptr_shared() :
		_BaseClass()
	{
	}

	/**
	 * Constructor
	 *
	 * RATING( +-- )
	 */
	explicit ptr_shared( _Type* p ) :
		_BaseClass( p )
	{
		__S_ASSERT( p != NULL );
	}

	/**
	 * copy constructor from shared ptr
	 *
	 * RATING( +-- )
	 */
	ptr_shared( const ptr_shared< _Type >& src )
	{
		_BaseClass::AssignStrong( src );
	}

	/**
	 * copy constructor from waek ptr
	 *
	 * RATING( +-- )
	 */
	ptr_shared( const ptr_weak< _Type >& src )
	{
		_BaseClass::AssignFromWeak( src );
	}

#ifdef _SLIB_CPP11
	/**
	 * move constructor
	 */
	ptr_shared( ptr_shared< _Type >&& src )
	{
		_BaseClass::operator = ( src );
		src.Reset();
	}

	/**
	 * move operator
	 */
	void operator = ( ptr_shared< _Type >&& src )
	{
		_BaseClass::ReleaseStrong();
		_BaseClass::operator = ( src );
		src.Reset();
	}

#endif

	/**
	 * compare the shared ptr with another shared pointer
	 *
	 * RATING( +-- )
	 */
	System::Types::sBool operator == ( const ptr_shared<_Type>& src ) const
	{
		return _BaseClass::operator == ( src );
	}

	/**
	 * compare the shared ptr with another weak pointer
	 *
	 * RATING( +-- )
	 */
	System::Types::sBool operator == ( const ptr_weak<_Type>& src ) const
	{
		src.IsNull(); // will update the null value for weak ref
		return _BaseClass::operator == ( src );
	}

	void operator = ( const ptr_shared< _Type >& src )
	{
		if( _BaseClass::operator == ( src ) )
			return;

		if( _BaseClass::ReleaseStrong() )
			_BaseClass::Reset();

		_BaseClass::AssignStrong( src );
	}

	void operator = ( const ptr_weak< _Type >& src )
	{
		if( BaseClass::operator == ( src ) )
			return;

		if( _BaseClass::ReleaseStrong() )
			_BaseClass::Reset();

		_BaseClass::AssignFromWeak( src );
	}

	/**
	 * destructor
	 *
	 * RATING( +-- )
	 */
	~ptr_shared()
	{
		_BaseClass::ReleaseStrong();
	}

	using _BaseClass::operator->;
	using _BaseClass::operator*;
	using _BaseClass::operator();

	/**
	 * returns sTrue of pointrt is a null pointer
	 *
	 * Rating: +--
	 */
	using _BaseClass::IsNull;
};
