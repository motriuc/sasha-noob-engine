/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_files_lfile_win32.cpp
//	Created                 : 28 6 2007   17:53
//	File path               : SLibF\system\Cpp
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

#define _use_Files_
#include "s_system.h"

#ifdef _SPL_WIN32

namespace System
{
namespace Files
{
using namespace Types;

//------------------------------------------------------------------------------------------	
/**
 *	file open mode conversion table
 */
DWORD g_fopenMode[] = 
{
	CREATE_ALWAYS,		// eCreate
	CREATE_NEW,			// eCreateNew
	OPEN_EXISTING,		// eOpen
	OPEN_ALWAYS,		// eOpenOrCreate
	OPEN_ALWAYS,		// eAppend
	TRUNCATE_EXISTING	// eTruncate
};

//------------------------------------------------------------------------------------------	
DWORD g_accessMode[] = 
{
	GENERIC_READ,					// eRead
	GENERIC_WRITE,					// eWrite
	GENERIC_READ | GENERIC_WRITE	// eReadWrite
};
//------------------------------------------------------------------------------------------	
DWORD g_shareMode[] = 
{
	0,									// eNone
	FILE_SHARE_READ,					// eRead
	FILE_SHARE_WRITE,					// eWrite
	FILE_SHARE_READ | FILE_SHARE_WRITE	// eReadWrite
};

//------------------------------------------------------------------------------------------	
DWORD g_SeekMode[SeekType::COUNT] = 
{
	FILE_BEGIN,		// eFromBegin
	FILE_CURRENT,	// eFromCurrent
	FILE_END		// eFromEnd
};
//------------------------------------------------------------------------------------------
LFile::LFile() :
	_hFile( INVALID_HANDLE_VALUE )
{

}
	
//------------------------------------------------------------------------------------------
void LFile::Open(
	const sChar* pFileName,
	FileOpenMode::FileOpenMode openMode,
	FileAccessMode::FileAccessMode accessMode,
	FileShareMode::FileShareMode shareMode
)
{
	__S_ASSERT( _hFile == INVALID_HANDLE_VALUE );

	_hFile = CreateFile(
		pFileName,
		g_accessMode[accessMode],
		g_shareMode[shareMode],
		NULL,
		g_fopenMode[openMode],
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if( _hFile == INVALID_HANDLE_VALUE )
	{
		error_throw_arg( FileOpenError )
			pFileName
		);
	}
}

//------------------------------------------------------------------------------------------
sUInt LFile::Read( void* pBuf, sUInt uLength ) const
{
	__S_ASSERT( _hFile != INVALID_HANDLE_VALUE );

	DWORD bytesRead = 0;
	if( ! ReadFile( _hFile, pBuf, uLength, &bytesRead, NULL ) )
		error_throw( FileReadError );

	return (sUInt)bytesRead;
}

//------------------------------------------------------------------------------------------
sUInt LFile::Write( const void* pBuf, sUInt uLength )
{
	__S_ASSERT( _hFile != INVALID_HANDLE_VALUE );

	DWORD bytesWrite = 0;
	if( ! WriteFile( _hFile, pBuf, uLength, &bytesWrite, NULL ) )
		error_throw( FileWriteError );

	return (sUInt)bytesWrite;
}

//------------------------------------------------------------------------------------------
void LFile::Close()
{
	if( _hFile != INVALID_HANDLE_VALUE )
	{
		::CloseHandle( _hFile );
		_hFile = INVALID_HANDLE_VALUE;
	}
}

//------------------------------------------------------------------------------------------
sUInt LFile::Position() const
{
	__S_ASSERT( _hFile != INVALID_HANDLE_VALUE );
	
	return (sUInt)SetFilePointer( _hFile, 0, NULL, FILE_CURRENT );
}

//------------------------------------------------------------------------------------------
LFile::~LFile()
{
	Close();
}

//------------------------------------------------------------------------------------------
sUInt LFile::Size() const
{
	__S_ASSERT( _hFile != INVALID_HANDLE_VALUE );

	return (sUInt)GetFileSize( _hFile, NULL );
}

//------------------------------------------------------------------------------------------
sUInt LFile::Seek( sInt uPos, SeekType::SeekType ePosType )
{
	__S_ASSERT( _hFile != INVALID_HANDLE_VALUE );

	return (sUInt)SetFilePointer( _hFile, (LONG)uPos, NULL, g_SeekMode[ePosType] );
}

}
}


#endif // _SPL_WIN32
