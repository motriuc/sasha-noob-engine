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
 */
template< typename _Type >
class ptr_shared : public ptr_base_ref< _Type >
{
private:
	typedef ptr_base_ref< _Type > _BaseClass;
public:
	/**
	 * Default constructor
	 */
	ptr_shared() :
		_BaseClass()
	{
	}

	/**
	 * Constructor
	 */
	explicit ptr_shared( _Type* p ) :
		_BaseClass( p )
	{
		__S_ASSERT( p != NULL );
	}

	/**
	 * copy constructor from shared ptr
	 */
	ptr_shared( const ptr_shared< _Type >& src )
	{
		_BaseClass::AssignStrong( src );
	}

	/**
	 * copy constructor from waek ptr
	 */
	ptr_shared( const ptr_weak< _Type >& src )
	{
		_BaseClass::AssignFromWeak( src );
	}

	/**
	 * compare the shared ptr with another shared pointer
	 */
	System::Types::sBool operator == ( const ptr_shared<_Type>& src )
	{
		return _BaseClass::operator == ( src );
	}

	/**
	 * compare the shared ptr with another weak pointer
	 */
	System::Types::sBool operator == ( const ptr_weak<_Type>& src )
	{
		src.CheckWeakRef();
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

	~ptr_shared()
	{
		_BaseClass::ReleaseStrong();
	}

	using _BaseClass::operator->;
	using _BaseClass::operator*;
	using _BaseClass::operator();
	using _BaseClass::IsNull;
};


