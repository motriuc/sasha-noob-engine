/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_files_name.cpp
//  Created                 : 2 3 2012
//  File path               : SLibF\system\Cpp
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

#define _use_Files_
#include "s_system.h"

namespace System
{
namespace Files
{
using namespace Types;

//------------------------------------------------------------------
sString Name::GetFileName( const sString& path )
{
	for( sInt i = path.Length() - 1; i >= 0; --i )
	{
		if( IsPathChar( path[i] ) )
		{
			return path.SubString( i + 1 );
		}
	}

	return path;
}

//------------------------------------------------------------------
sString Name::GetFilePath( const sString& path )
{
	for( sInt i = path.Length() - 1; i >= 0; --i )
	{
		if( IsPathChar( path[i] ) )
		{
			while( i >= 0 && IsPathChar( path[i] ) )
				--i;

			return path.SubString( 0, i + 1 );
		}
	}

	return sString();
}

//------------------------------------------------------------------
sString Name::GetFileExtension( const sString& path )
{
	for( sInt i = path.Length() - 1; i >= 0; --i )
	{
		sChar ch = path[i];

		if( IsPathChar( ch ) )
			return sString();

		if( IsExtensionChar( ch ) )
			return path.SubString( i + 1 );
	}
	return sString();
}

//------------------------------------------------------------------
sString Name::GetFileNameNoExtension( const sString& path )
{
	sInt end = -1;
	sInt start = -1;

	for( sInt i = path.Length() - 1; i >= 0; --i )
	{
		sChar ch = path[i];

		if( IsPathChar( ch ) )
		{
			start = i + 1;
			break;
		}

		if( end == -1 && IsExtensionChar( ch ) )
			end = i;
	}

	if( start == -1 )
		start = 0;

	if( end == -1 )
		end = path.Length();

	return path.SubString( start, end - start );
}

//------------------------------------------------------------------
sString Name::GetFileName( const sString& name, const sString& ext )
{
	sString result( name.Length() + ext.Length() + 1 );

	result += name;

	if( result.Length() > 0 )
	{
		if( !IsExtensionChar( result[result.Length()-1] ) )
			result += GetExtensionChar();
	}

	result += ext;

	return result;
}

//------------------------------------------------------------------
sString Name::GetPath( const sString& path, const sString name )
{
	sString result( path.Length() + name.Length() + 1 );
	
	result += path;

	if( result.Length() > 0 )
	{
		if( !IsPathChar( result[result.Length()-1] ) )
			result += GetPathChar();
	}

	result += name;

	return result;
}

//------------------------------------------------------------------
sString Name::GetPath( const sString& path, const sString name, const sString& ext )
{
	sString result( path.Length() + name.Length() + ext.Length() + 2 );

	result += path;

	if( result.Length() > 0 )
	{
		if( !IsPathChar( result[result.Length()-1] ) )
			result += GetPathChar();
	}

	result += name;

	if( result.Length() > 0 )
	{
		if( !IsExtensionChar( result[result.Length()-1] ) )
			result += GetExtensionChar();
	}

	result += ext;

	return result;
}

//------------------------------------------------------------------
sString Name::GetFullPath( const sString& path )
{
#ifdef _SPL_WIN32
	sString result( MAX_PATH );
	::GetFullPathName( path, MAX_PATH, result.GetCharBuffer(), NULL );
	result.UpdateLength();
	return result;
#else
	return path;
#endif

}



}
}