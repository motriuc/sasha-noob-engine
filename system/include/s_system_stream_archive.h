/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_archive.h
//  Created                 : 16 1 2012   13:01
//  File path               : SLibF\system\Include
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
 * IStreamArchiveProvider
 */
class IStreamArchiveProvider
{
public:
	/**
	 * returns provider prefix
	 */
	virtual sString GetProviderPrefix() const = 0;

	/**
	 * opens the stream
	 */
	virtual IInputStream* Open( const sString& path ) = 0 throws_error;
	
	/**
	 * opens the stream
	 */
	virtual const IInputStream* Open( const sString& path ) const = 0 throws_error;
	
	/**
	 *
	 */
	virtual sBool IsAvailable( const sString& path ) const = 0;
};

/**
 * StreamArchive
 */
class StreamArchive
{
public:
	/**
	 * Adds a stream provider
	 */
	void AddProvider( IStreamArchiveProvider* provider );

	/**
	 * opens a stream
	 */
	virtual const IInputStream* Open( const sString& path ) const throws_error;
	virtual IInputStream* Open( const sString& path ) throws_error;
	
	/**
	 *
	 */
	~StreamArchive();

	/**
	 * returns true if path is a path from root of the StreamArchive
	 */
	static sBool IsPathFromRoot( const sString& path );

	/**
	 * Add alias name
	 */
	void SetNameAlias( const sString& alias, const sString& name );
	
private:
	sStrings							_paths;
	sVector<IStreamArchiveProvider*>	_providers;
	sMap<sString,sString>				_nameAlias;

private:
	const IStreamArchiveProvider* FindProviderFor( const sString& path ) const;
	const IInputStream* OpenFromFullPath( const sString& path ) const throws_error;
	
	static sString PathRemoveProvider( const sString& path, const sString& providerName );
	sString ParseNameAliases( const sString& path ) const; 
};


/**
 * StreamNotFoundError
 */
class StreamNotFoundError : public System::Errors::Error
{
	_SLIB_RUNTIME( System::Streams, StreamNotFoundError, System::Errors::Error )
public:
	StreamNotFoundError(  Error* pPrevError = NULL, const sString& path = _S("") ) : 
		_BaseClass( pPrevError ),
		_path( path ) {}

#ifdef _DEBUG
	StreamNotFoundError( const sChar* file, sInt line,  Error* pPrevError, const sString& path ) :
		_BaseClass( file, line, pPrevError ),
		_path( path ) {}
#endif

	virtual sString Description() const
	{
		return Format( _S("Can't find the stream: {1}\n{2}") ) % _path % _BaseClass::Description();
	}

private:
	sString		_path;
};