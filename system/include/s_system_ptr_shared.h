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

template< typename _Type >
class ptr_shared : public ptr_base_ref< _Type >
{
private:
	typedef ptr_base_ref< _Type > _BaseClass;
public:
	ptr_shared() :
		_BaseClass()
	{
	}

	ptr_shared( _Type* p ) :
		_BaseClass( p )
	{
		__S_ASSERT( p != NULL );
	}

	ptr_shared( const ptr_shared< _Type >& src )
	{
		_BaseClass::AssignStrong( src );
	}

	void operator = ( const ptr_shared< _Type >& src )
	{
		if( _BaseClass::ReleaseStrong() )
			_BaseClass::Reset();

		_BaseClass::AssignStrong( src );
	}

	~ptr_shared()
	{
		_BaseClass::ReleaseStrong();
	}
};


