/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_conf_inc.h
//	Created                 : 14 6 2007   0:54
//	File path               : SLibF\system\include
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
#ifndef _S_SYSTEM_CONF_INC_INC_
#define _S_SYSTEM_CONF_INC_INC_

// Include windows headers
#ifdef _SPL_WIN32
	#include <windows.h>
	#include <stdlib.h>
	#include <math.h>
	#include <ctype.h>
#endif


#ifdef _SPL_MAC
	#include <stdlib.h>
	#include <math.h>
	#include <string.h>
	#include <assert.h>
	#include <wchar.h>
	#include <new>

	#include <CoreFoundation/CFString.h>
	#include <CoreGraphics/CGDataProvider.h>

	#include <mach/mach.h>
	#include <mach/mach_time.h>
#endif

#endif // _S_SYSTEM_CONF_INC_INC_
