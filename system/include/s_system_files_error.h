/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_files_error.h
//  Created                 : 28 6 2007   19:13
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
 * Generic File error
 */
class FileError : 
#ifdef _SPL_WIN32
					public  System::Errors::Win32Error
{
	_SLIB_RUNTIME( System::Files, FileError, System::Errors::Win32Error )
#else
					public System::Errors::Error
{
	_SLIB_RUNTIME( System::Files, FileError, System::Errors::Error )	
#endif

public:
	FileError( Error* pPrevError = NULL ) : _BaseClass( pPrevError ) {}

#ifdef _DEBUG
	FileError( const sChar* file, sInt line, Error* pPrevError = NULL ) :
		_BaseClass( file, line, pPrevError ) {}
#endif
};

/**
 *	FileOpenError
 */
class FileOpenError : public FileError
{
	_SLIB_RUNTIME( System::Files, FileOpenError, FileError )
public:
	FileOpenError(  Error* pPrevError = NULL, const sString& fileName = _S("") ) : 
		_BaseClass( pPrevError ),
		_fileName( fileName ) {}

#ifdef _DEBUG
	FileOpenError( const sChar* file, sInt line,  Error* pPrevError, const sString& fileName ) :
		_BaseClass( file, line, pPrevError ),
		_fileName( fileName ) {}
#endif

	virtual sString Description() const
	{
		return Format( _S("Can't open file: {1}\n{2}") ) % _fileName % _BaseClass::Description();
	}

private:
	sString		_fileName;
};

/**
 *	FileReadError
 */
class FileReadError : public FileError
{
	_SLIB_RUNTIME( System::Files, FileReadError, FileError )
public:
	FileReadError(  Error* pPrevError = NULL ) : _BaseClass( pPrevError ) {}

#ifdef _DEBUG
	FileReadError( const sChar* file, sInt line,  Error* pPrevError = NULL ) :
		_BaseClass( file, line, pPrevError ) {}
#endif

	virtual sString Description() const
	{
		return Format( _S("Can't read from file\n{1}" ) ) % _BaseClass::Description();
	}

};

/**
 *	FileWriteError
 */
class FileWriteError : public FileError
{
	_SLIB_RUNTIME( System::Files, FileWriteError, FileError )
public:
	FileWriteError(  Error* pPrevError = NULL ) : _BaseClass( pPrevError ) {}

#ifdef _DEBUG
	FileWriteError( const sChar* file, sInt line,  Error* pPrevError = NULL ) :
		_BaseClass( file, line, pPrevError ) {}
#endif

	virtual sString Description() const
	{
		return Format( _S("Can't write to file\n{1}") ) % _BaseClass::Description();
	}
};