/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_ptr_base.h
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
 * ptr storage class
 */
template< typename _Type >
class ptr_base
{
public:
	/**
	 * returns True is pointer is NULL
	 */
	System::Types::sBool IsNull() const
	{
		return _p == NULL;
	}

	_Type& operator()() const
	{
		__S_ASSERT( _p != NULL );
		return *_p;
	}

	_Type& operator*() const
	{
		__S_ASSERT( _p != NULL );
		return *_p;
	}

	_Type* operator->() const
	{
		__S_ASSERT( _p != NULL );
		return _p;
	}

protected:
	ptr_base() :
		_p( NULL )
	{
	}

	ptr_base( _Type* p ) :
		_p( p )
	{
	}

	/**
	 * default copy constructor does nothing
	 */
	ptr_base( const ptr_base<_Type>& ) :
	{
	}

	/**
	 * default copy operator does nothint
	 */
	void operator = ( const ptr_base<_Type>& src )
	{
		_p = src._p;
	}

	/**
	 * Release the pointer data
	 */
	void Release( )
	{
		delete _p;
	}

	void Reset()
	{
		_p = NULL;
	}

private:
	_Type* _p;
};

/**
 * ptr reference storage class
 */
template< typename _Type >
class ptr_base_ref : public ptr_base< _Type >
{
private:
	typedef  ptr_base< _Type > _BaseClass;
public:

protected:
	ptr_base_ref() :
		_BaseClass(),
		_refInfo( NULL )
	{
	}
	
	ptr_base_ref( _Type* p ) :
		_BaseClass( p ),
		_refInfo( NULL )
	{
	}

	void Reset()
	{
		_BaseClass::Reset();
		_refInfo = NULL;
	}

	/**
	 * 
	 */
	void AssignStrong( const ptr_base_ref<_Type>& src )
	{
		if( src.IsNull() )
			return;

		_BaseClass::operator=( src );

		if( src._refInfo == NULL )
			src._refInfo = new RefInfo( 2, 0 );
		else
			src._refInfo->AddStrongRef();

		_refInfo = src._refInfo;
	
	}

	/**
	 *
	 */
	void AssignWeak( const ptr_base_ref<_Type>& src )
	{
		if( src.IsNull() )
			return;

		_BaseClass::operator=( src );

		if( src._refInfo == NULL )
			src._refInfo = new RefInfo( 1, 1 );
		else
			src._refInfo->AddWeakRef();

		_refInfo = src._refInfo;
	}

	/**
	 *
	 */
	System::Types::sBool ReleaseStrong()
	{
		if( IsNull() )
			return System::Types::sFalse;

		if( _refInfo == NULL || _refInfo->ReleaseStrongRef() )
		{
			_BaseClass::Release();
		}

		if( _refInfo != NULL && _refInfo->HasNoRef() )
		{
			delete _refInfo;
		}

		return System::Types::sTrue;
	}

	System::Types::sBool ReleaseWeak()
	{
		if( IsNull() )
			return System::Types::sFalse;

		if( _refInfo != NULL && _refInfo->ReleaseWeakRef() )
		{
			delete _refInfo;
		}

		return System::Types::sTrue;
	}

	void CheckWeakRef()
	{
		if( IsNull() )
			return;

		__S_ASSERT( _refInfo != NULL );

		if( _refInfo->HasNoStrongRef() )
			Reset();
	}

	/**
	 * reference info class
	 */
	class RefInfo 
	{
	public:
		RefInfo( System::Types::sUInt count, System::Types::sUInt weakCount ) :
			_refCount( count ),
			_weakRefCount( weakCount )
		{
		}

		void AddStrongRef()
		{
			System::Mt::Inc( _refCount );
		}

		System::Types::sBool ReleaseStrongRef( )
		{
			return System::Mt::Dec( _refCount ) == 0;
		}

		void AddWeakRef()
		{
			System::Mt::Inc( _weakRefCount );
		}

		System::Types::sBool ReleaseWeakRef( )
		{
			return System::Mt::Dec( _weakRefCount ) == 0;
		}

		System::Types::sBool HasNoStrongRef()
		{
			return _refCount == 0;
		}

		System::Types::sBool HasNoRef()
		{
			return _refCount == 0 && _weakRefCount == 0;
		}

	private:
		System::Mt::sUAtomic	_refCount;
		System::Mt::sUAtomic	_weakRefCount;
	};

private:
	mutable RefInfo*	_refInfo;

	void operator = ( const ptr_base_ref<_Type>& );
	ptr_base_ref( const ptr_base_ref<_Type>& );
};