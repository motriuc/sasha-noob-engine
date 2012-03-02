/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_files_name.h
//  Created                 : 2 3 2012   20:28
//  File path               : SLibF\system\Include
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
 * File Name utilities
 */
class Name
{
public:
	/**
	 * Return path separator char
	 */
	static sChar GetPathChar();

	/**
	 * Return extension separator char
	 */
	static sChar GetExtensionChar();

	/**
	 * Return file Name from the path
	 */
	static sString GetFileName( const sString& path );

	/**
	 * Return file path without file name
	 */
	static sString GetFilePath( const sString& path );

	/**
	 * returns file extension from path
	 */
	static sString GetFileExtension( const sString& path );

	/**
	 * returns file name without ext
	 */
	static sString GetFileNameNoExtension( const sString& path );

	/**
	 * combines file name and ext
	 */
	static sString GetFileName( const sString& name, const sString& ext );

	/**
	 * Combines path and file name
	 */
	static sString GetPath( const sString& path, const sString name );
	
	/**
	 *	Combines path filename and extension
	 */
	static sString GetPath( const sString& path, const sString name, const sString& ext );

	/**
	 * Merges the name of the current drive and directory with a specified file name 
	 * to determine the full path and file name of a specified file
	 */
	static sString GetFullPath( const sString& path );

	/**
	 *
	 */
	static sBool IsPathChar( sChar ch );

	/**
	 *
	 */
	static sBool IsExtensionChar( sChar ch ); 
};

inline sChar Name::GetExtensionChar()
{
	return _S('.');
}

inline sChar Name::GetPathChar()
{
	return _S('/');
}

inline sBool Name::IsPathChar( sChar ch )
{
	return ch == _S('/') || ch == _S('\\');
}

inline sBool Name::IsExtensionChar( sChar ch )
{
	return ch == _S('.');
}


