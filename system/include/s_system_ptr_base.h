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
protected:
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

	System::Types::sBool operator == ( const ptr_base<_Type>& src )
	{
		return _p == src._p;
	}

	/**
	 * Release the pointer data
	 */
	void Release( )
	{
		delete _p;
	}

	void Reset() const
	{
		_p = NULL;
	}

private:
	mutable _Type* _p;
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
	/**
	 * returns reference count
	 */
	System::Types::sUInt RefCount() const
	{
		if( _refInfo == NULL )
			return 1;

		return _refInfo->RefCount();
	}

	/**
	 * returns weak reference count
	 */
	System::Types::sUInt WeakRefCount() const
	{
		if( _refInfo == NULL )
			return 0;

		return _refInfo->WeakRefCount();
	}

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

	void Reset() const
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

		if( src._refInfo == NULL )
			src._refInfo = new RefInfo( 2, 0 );
		else
			src._refInfo->AddStrongRef();

		_refInfo = src._refInfo;
	
		_BaseClass::operator=( src );
	}


	void AssignFromWeak( const ptr_base_ref<_Type>& src )
	{
		if( src.IsNull() )
			return;

		__S_ASSERT( src._refInfo != NULL );

		for(;;)
		{
			if( src._refInfo->HasNoStrongRef() )
				return;

			if( src._refInfo->AddSafeStrongRef() )
				break;
		}

		_refInfo = src._refInfo;

		_BaseClass::operator=( src );
	}


	/**
	 *
	 */
	void AssignWeak( const ptr_base_ref<_Type>& src )
	{
		if( src.IsNull() )
			return;

		if( src._refInfo == NULL )
			src._refInfo = new RefInfo( 1, 1 );
		else
			src._refInfo->AddWeakRef();

		_refInfo = src._refInfo;

		_BaseClass::operator=( src );
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

	/**
	 *
	 */
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

	/**
	 *
	 */
	void CheckWeakRef() const
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

		void AddStrongRef() const
		{
			System::Mt::Inc( _refCount );
		}

		System::Types::sBool AddSafeStrongRef() const
		{
			sUInt incResult = _refCount + 1;
			return System::Mt::SetIf( _refCount, incResult - 1, incResult ); 
		}

		System::Types::sBool ReleaseStrongRef() const
		{
			return System::Mt::Dec( _refCount ) == 0;
		}
		
		void AddWeakRef() const
		{
			System::Mt::Inc( _weakRefCount );
		}

		System::Types::sBool ReleaseWeakRef() const
		{
			return System::Mt::Dec( _weakRefCount ) == 0 && _refCount == 0;
		}

		System::Types::sBool HasNoStrongRef() const
		{
			return _refCount == 0;
		}

		System::Types::sBool HasNoRef() const
		{
			return _refCount == 0 && _weakRefCount == 0;
		}

		System::Types::sUInt RefCount() const
		{
			return _refCount;
		}

		System::Types::sUInt WeakRefCount() const
		{
			return _weakRefCount;
		}

	private:
		mutable System::Mt::sUAtomic	_refCount;
		mutable System::Mt::sUAtomic	_weakRefCount;
	};

private:
	mutable RefInfo*	_refInfo;

	void operator = ( const ptr_base_ref<_Type>& );
	ptr_base_ref( const ptr_base_ref<_Type>& );
};