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

#ifdef _SPL_MAC
#include <CoreFoundation/CFBundle.h>
#endif

namespace System
{
namespace Streams
{

using namespace System;
	
#ifdef _SPL_MAC
	
//---------------------------------------------------------------------------------------	
sString GetPathForResource( const sString& path ) throws_error
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

	CFBundleRef mainBundle = CFBundleGetMainBundle();
	
	CFStringRef cfsResName = resName.ToCfString();
	CFStringRef cfsResType = resType.ToCfString();
	
	CFURLRef url = CFBundleCopyResourceURL( mainBundle, cfsResName, cfsResType, NULL );
	
	if( url == NULL ) 
	{
		CFRelease( cfsResName );
		CFRelease( cfsResType );
		
		error_throw_arg( Errors::StringError )
			_S("Resource not found : ") + path
		);
	}
	
	CFStringRef cfsRetPath = CFURLCopyFileSystemPath( url, kCFURLPOSIXPathStyle );
	
	CFRelease( cfsResName );
	CFRelease( cfsResType );
		
	sString ret( cfsRetPath );
	
	CFRelease( url );
	CFRelease( cfsRetPath );
	
	return ret;
}

/**
 * ResourceArchiveStream
 */
class ResourceArchiveStream : public Streams::FileStream
{
private:
	typedef Streams::FileStream _BaseClass;
public:
	ResourceArchiveStream( const sString& path ) throws_error :
		_BaseClass( &_file )
	{
		sString resPath = GetPathForResource( path );
		_file.Open( resPath, Files::FileOpenMode::eOpen, Files::FileAccessMode::eRead );
	}
private:	
	Files::LFile	_file;
};
	
#endif // _SPL_MAC

#ifdef _SPL_WIN32

/**
 * ResourceArchiveStream
 */
class ResourceArchiveStream :public Streams::FileStream
{
private:
	typedef Streams::FileStream _BaseClass;
public:
	ResourceArchiveStream( const sString& path ) :
		_BaseClass( NULL )
	{
	}
};

#endif

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
#ifdef _SPL_MAC	
	sString resPath = GetPathForResource( path );
	
	Files::LFile file;
	
	try {
		file.Open( resPath, Files::FileOpenMode::eOpen, Files::FileAccessMode::eRead );
	}
	catch( System::Errors::Error* error ) 
	{ 
		delete error;
		return sFalse;
	}
	
	return sTrue;
#else
	return sFalse;
#endif
}

	
}
}
