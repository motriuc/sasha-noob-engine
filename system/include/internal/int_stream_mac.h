/////////////////////////////////////////////////////////////////////
//  File Name               : int_stream_mac.h
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

#include <CoreFoundation/CFBundle.h>

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

//---------------------------------------------------------------------------------------	
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

	static sBool IsAvailable( const sString& path )
	{
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
	}
private:	
	Files::LFile	_file;
};
