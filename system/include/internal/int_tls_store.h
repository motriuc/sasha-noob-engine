/////////////////////////////////////////////////////////////////////
//  File Name               : int_tls_store.h
//	Created                 : 28 6 2007   16:03
//	File path               : SLibF\system\include\internal\
//	Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//	Library                 : 
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
namespace Internal
{

#ifdef _SPL_WIN32

template< typename _TYPE >
class TlsValueStorage
{
public:
	inline TlsValueStorage()
	{
		_hId = TlsAlloc();
		__S_ASSERT( _hId != TLS_OUT_OF_INDEXES );
	}

	inline _TYPE* Set( _TYPE* data )
	{
		_TYPE* prev = static_cast<_TYPE*>( TlsGetValue( _hId ) );
		__S_VERIFY( TlsSetValue( _hId, data ) );
		return prev;
	}
	
	inline _TYPE* Get()
	{
		return static_cast<_TYPE*>( TlsGetValue( _hId ) );
	}

	inline ~TlsValueStorage()
	{
		TlsFree( _hId );
	}
private:
	DWORD _hId;
};

#else // _SPL_WIN32

template< typename _TYPE >
class TlsValueStorage
{
};
	
#endif // _SPL_WIN32

template< typename _TYPE >
class StaticValueStorage
{
public:

	inline StaticValueStorage(): _data( NULL )
	{ 
	}

	inline _TYPE* Set( _TYPE* data )
	{
		_TYPE* prev = _data;
		_data = data; 
		return prev;
	}

	inline _TYPE* Get()
	{
		return _data;
	}

private:
	_TYPE*	_data;
};

/// Value storage
template< typename _TYPE >
class ValueStorage : public 
	#ifdef _SLIB_MT
		TlsValueStorage<_TYPE>
	#else
		StaticValueStorage<_TYPE>
	#endif
{

};

}