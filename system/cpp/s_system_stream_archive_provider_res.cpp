/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_archive_provider_res.cpp
//  Created                 : 16 1 2012   13:01
//  File path               : SLibF\system\Cpp
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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

#define _use_Streams_

#include "s_system.h"

using namespace System;
using namespace System::Types;

#ifdef _SPL_MAC
	#include "int_stream_mac.h"
#endif // _SPL_MAC

#ifdef _SPL_WIN32
	#include "int_stream_win32.h"
#endif

namespace System
{
namespace Streams
{

//---------------------------------------------------------------------------------------	
IInputStream* ResourceArchiveProvider::Open( const sString& path ) throws_error
{
	return new ResourceArchiveStream( path );
}

//---------------------------------------------------------------------------------------	
const IInputStream* ResourceArchiveProvider::Open( const sString& path ) const throws_error
{
	return new ResourceArchiveStream( path );
}
	
//---------------------------------------------------------------------------------------	
sBool ResourceArchiveProvider::IsAvailable( const sString& path ) const
{
	return ResourceArchiveStream::IsAvailable( path );
}

//---------------------------------------------------------------------------------------
class FileArchiveStream : public Streams::FileStream
{
private:
	typedef Streams::FileStream _BaseClass;
public:
	FileArchiveStream( const sString& path ) throws_error :
		_BaseClass( &_file )
	{
		_file.Open( path, Files::FileOpenMode::eOpen, Files::FileAccessMode::eRead );
	}

	static sBool IsAvailable( const sString& path )
	{		
		Files::LFile file;
	
		try {
			file.Open( path, Files::FileOpenMode::eOpen, Files::FileAccessMode::eRead );
		}
		catch( System::Errors::Error* error ) 
		{ 
			delete error;
			return sFalse;
		}
	
		return sTrue;
	}
private:	
	Files::LFile	_file;
};

//---------------------------------------------------------------------------------------	
FolderArchiveProvider::FolderArchiveProvider( const sString& prefix, const sString& path ) :
	_prefix( prefix ),
	_path( path )
{
}

//---------------------------------------------------------------------------------------	
IInputStream* FolderArchiveProvider::Open( const sString& path ) throws_error
{
	return new FileArchiveStream( Files::Name::GetPath( _path, path ) ); 
}

//---------------------------------------------------------------------------------------	
const IInputStream* FolderArchiveProvider::Open( const sString& path ) const throws_error
{
	return new FileArchiveStream( Files::Name::GetPath( _path, path ) ); 
}

//---------------------------------------------------------------------------------------	
sBool FolderArchiveProvider::IsAvailable( const sString& path ) const
{
	return FileArchiveStream::IsAvailable( Files::Name::GetPath( _path, path ) );
}

}
}
