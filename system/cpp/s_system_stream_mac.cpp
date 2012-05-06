/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_mac.cpp
//  Created                 : 21 1 2012   13:01
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

#define _use_Streams_
#define _use_Errors_

#include "s_system.h"

#ifdef _SPL_MAC

using namespace System::Types;

namespace System
{
namespace Streams 
{

//--------------------------------------------------------------------------------
/* This callback is called to copy `count' bytes from the sequential data
 stream to `buffer'. */

static size_t Stream_GetBytesCallback( void *info, void *buffer, size_t count )
{
	const IInputStream* pStream = reinterpret_cast<const IInputStream*> ( info );
	
	sInt bytesRead = 0;
	
	try
	{
		bytesRead = pStream->Read( buffer, count );
	}
	catch( Errors::Error* error ) 
	{
		delete error;
	}
	
	return bytesRead;
}

//--------------------------------------------------------------------------------
/* This callback is called to skip `count' bytes forward in the sequential
 data stream. It should return the number of bytes that were actually
 skipped. */

static off_t Stream_SkipForwardCallback( void *info, off_t count )
{
	const IInputStream* pStream = reinterpret_cast<const IInputStream*> ( info );
	
	sInt pos = pStream->GetPosition();
	sInt newPos = pStream->Seek( count, SeekType::eFromCurrent );
	
	return newPos - pos;
}

//--------------------------------------------------------------------------------
/* This callback is called to rewind to the beginning of sequential data
 stream. */

static void Stream_RewindCallback( void *info )
{
	const IInputStream* pStream = reinterpret_cast<const IInputStream*> ( info );
	pStream->Seek( 0, SeekType::eFromBegin );
}

//--------------------------------------------------------------------------------
/* This callback is called to release the `info' pointer when the data
 provider is freed. */

//--------------------------------------------------------------------------------
void Stream_ReleaseInfoCallback( void *info )
{
	
}

//--------------------------------------------------------------------------------
CGDataProviderSequentialCallbacks callBacks = 
{
		0,
		&Stream_GetBytesCallback,
		&Stream_SkipForwardCallback,
		&Stream_RewindCallback,
		&Stream_ReleaseInfoCallback
};


//--------------------------------------------------------------------------------
CGDataProviderRef IInputStream_To_CGDataProviderRef( const IInputStream* stream )
{
	return CGDataProviderCreateSequential( const_cast<Streams::IInputStream*>( stream ), &callBacks );
}
	
}		
}

#endif
