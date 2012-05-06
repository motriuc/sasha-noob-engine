/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_debug.cpp
//  Created                 : 15 6 2007   1:41
//  File path               : SLibF\system\Cpp
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
#include "s_system.h"

#ifdef _SPL_WIN32

#include <stdio.h>

bool __slib_AssertMessage( const char* message, const char* file, int line )
{
	int len = strlen( message ) + strlen( file ) + 128;
	char* pBuf = new char[len];

	sprintf( pBuf, "%s(%d) : Assertion : %s\n", file, line, message );
	OutputDebugStringA( pBuf );

	sprintf( pBuf, "Assertion: %s\nfile: %s\nline: %d", message, file, line );

	INT ret = MessageBoxA( NULL, pBuf, "Assertion", MB_ABORTRETRYIGNORE | MB_ICONERROR );
	delete[] pBuf;
	switch( ret ) 
	{ 
		case IDABORT:
			::ExitProcess(1);
			break;

		case IDIGNORE:
			break;

		case IDRETRY: 
			return true;
	}

	return false;
}


#endif // _SPL_WIN32