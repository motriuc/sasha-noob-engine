/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_error.h
//	Created                 : 26 6 2007   21:57
//	File path               : system\include
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
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

// _use_sError_

#ifndef _SYSTEM_ERROR_INC_
#define _SYSTEM_ERROR_INC_


namespace Errors
{
	using namespace Types;

	#include "s_system_error_error.h"
	#include "s_system_error_strerr.h"

#ifdef _SPL_WIN32
	#include "s_system_error_win32err.h"
	#include "s_system_error_win32hresult.h"
#endif

}

#endif // _SYSTEM_ERROR_INC_
