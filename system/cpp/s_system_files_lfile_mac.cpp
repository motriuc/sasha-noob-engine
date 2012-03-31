/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_files_lfile_mac.cpp
//	Created                 : 16 01 2012   17:53
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

#ifdef _SPL_MAC


namespace System
{
namespace Files
{
using namespace Types;

//------------------------------------------------------------------------------------------	
int g_SeekMode[SeekType::COUNT] = 
{
	SEEK_SET,	// eFromBegin
	SEEK_CUR,	// eFromCurrent
	SEEK_END	// eFromEnd
};
	
//------------------------------------------------------------------------------------------	
LFile::LFile() :
	_hFile( NULL )
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
	const char* openFlags;
	
	__S_ASSERT( _hFile == NULL );
	
	switch( openMode ) {
			
			/**
			 *	Specifies that the operating system should create a new file.
			 *	If the file already exists, it will be overwritten
			 */
	case FileOpenMode::eCreate:
		{
			switch (accessMode) {
				case FileAccessMode::eRead:
				case FileAccessMode::eWrite:
					openFlags = "wb";
					break;
				case FileAccessMode::eReadWrite:
					openFlags = "w+b";
					break;
			}
		}
		break;
			
			/**
			 *	Specifies that the operating system should create a new file.
			 *	If the file already exists, an Error is generated.
			 */
	case FileOpenMode::eCreateNew:
		{
			__S_ASSERT( false );
			switch (accessMode) {
				case FileAccessMode::eRead:
				case FileAccessMode::eWrite:
					openFlags = "wb";
					break;
				case FileAccessMode::eReadWrite:
					openFlags = "w+b";
					break;
			}
		}
		break;
			
			/**
			 *	Specifies that the operating system should open an existing file.
			 *	The ability to open the file is dependent on the the value specified 
			 *	by FileAccess. A Error is thrown if the file does not exist.
			 */
	case FileOpenMode::eOpen:				
		{
			switch (accessMode) {
				case FileAccessMode::eRead:
					openFlags = "rb";
					break;

				case FileAccessMode::eWrite:
				case FileAccessMode::eReadWrite:
					openFlags = "r+b";
					break;
			}
		}
		break;
			
			/**
			 *	Specifies that the operating system should open a file if it exists; 
			 *	otherwise, a new file should be created.
			 */
	case FileOpenMode::eOpenOrCreate:		
		{
			__S_ASSERT( false );
			switch (accessMode) {
				case FileAccessMode::eRead:
				case FileAccessMode::eWrite:
				case FileAccessMode::eReadWrite:
					openFlags = "ab";
					break;
			}
		}
		break;
			
			/**
			 *	Opens the file if it exists and seeks to the end of the file, 
			 *	or creates a new file.
			 */
	case FileOpenMode::eAppend:
		{
			switch (accessMode) {
				case FileAccessMode::eRead:
				case FileAccessMode::eWrite:
				case FileAccessMode::eReadWrite:
					openFlags = "ab";
					break;
			}
		}
		break;
			
			/**
			 *	Specifies that the operating system should open an existing file. 
			 *	Once opened, the file should be truncated so that its size is zero bytes.
			 */
	case FileOpenMode::eTruncate:
		{
			__S_ASSERT( false );
			switch (accessMode) {
				case FileAccessMode::eRead:
					break;
				case FileAccessMode::eWrite:
					break;
				case FileAccessMode::eReadWrite:
					break;
			}
		}
		break;
	}
	
	_hFile = fopen( pFileName, openFlags );
	
	if( _hFile == NULL )
	{
		error_throw_arg( FileOpenError )
			pFileName
		);
	}
}

//------------------------------------------------------------------------------------------	
void LFile::Close()
{
	if( _hFile != NULL )
	{
		fclose( _hFile );
		_hFile = NULL;
	}
}
	
//------------------------------------------------------------------------------------------	
sUInt LFile::Read( void* pBuf, sUInt uLength ) const throws_error
{
	__S_ASSERT( _hFile != NULL );
	return fread(pBuf, 1, uLength, _hFile );
}		
	
//------------------------------------------------------------------------------------------	
sUInt LFile::Write( const void* pBuf, sUInt uLength ) throws_error
{
	__S_ASSERT( _hFile != NULL );
	return fwrite(pBuf, 1, uLength, _hFile );
}
	
//------------------------------------------------------------------------------------------	
sUInt LFile::Size() const
{
	__S_ASSERT( _hFile != NULL );
	
	long cpos = ftell( _hFile );
	fseek( _hFile, 0, SEEK_END );
	long len = ftell( _hFile );	
	fseek(_hFile, cpos, SEEK_SET );
	
	return len;
}
	
//------------------------------------------------------------------------------------------	
sUInt LFile::Position() const
{
	__S_ASSERT( _hFile != NULL );
	return ftell( _hFile );
}
	
//------------------------------------------------------------------------------------------	
sUInt LFile::Seek( sInt uPos, SeekType::SeekType ePosType )
{
	fseek( _hFile, uPos, g_SeekMode[ePosType] );
	return ftell( _hFile );
}	
	
//------------------------------------------------------------------------------------------	
LFile::~LFile()
{
	Close();
}
	
	
}
}

#endif // _SPL_MAC