/////////////////////////////////////////////////////////////////////
//  File Name               : int_stream_win32.h
//  Created                 : 2 3 2012   13:01
//  File path               : SLibF\system\Include\internal
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

/**
 * ResourceArchiveStream
 */
class  HRSRCResourceArchiveStream : public Streams::ReadMemStream
{
private:
	typedef Streams::ReadMemStream _BaseClass;
public:
	 HRSRCResourceArchiveStream( HRSRC hRc, const sString& path ) :
		_BaseClass( GetMemoryResource( hRc, path ), ::SizeofResource( NULL, hRc ) ),
		_hRc( hRc )
	{
	}
private:
	static const void* GetMemoryResource( HRSRC hRc, const sString& path )
	{
		HGLOBAL hGlobal = ::LoadResource( NULL, hRc );

		if( hGlobal == NULL )
		{
			error_throw_arg( Errors::StringError )
				_S("Resource not found : ") + path
			);
		}

		const void* pBuffer = ::LockResource( hGlobal );
		if( pBuffer == NULL )
		{
			error_throw_arg( Errors::StringError )
				_S("Resource not found : ") + path
			);
		}

		return pBuffer;
	}

private:
	HRSRC	_hRc;
};

/**
 * ResourceArchiveStream
 */
class ResourceArchiveStream : public HRSRCResourceArchiveStream
{
private:
	typedef HRSRCResourceArchiveStream _BaseClass;
public:
	ResourceArchiveStream( const sString& path ) throws_error :
		_BaseClass( GetResource( path ), path )
	{
	}

	static sBool IsAvailable( const sString& path )
	{
		return TryFindResource( path ) != NULL;
	}
private:
	static HRSRC TryFindResource( const sString& path )
	{
		sString resName;
		sString resType;
	
		sInt pos = path.FindReverse( _S('.') );
	
		if( pos >= 0 ) 
		{
			resName = path.SubString( 0, pos );
			resType = path.SubString( pos + 1 );
		}
		else
		{
			resName = path;
		}

		return ::FindResource( NULL, resName, resType );
	}

	static HRSRC GetResource( const sString& path ) throws_error
	{
		HRSRC hRc = TryFindResource( path );

		if( hRc == NULL )
		{
			error_throw_arg( Errors::StringError )
				_S("Resource not found : ") + path
			);
		}

		return hRc;
	}
};
