/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_conf_detect.h
//  Created                 : 14 6 2007   0:36
//  File path               : SLibF\system\include
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

#ifndef _S_SYSTEM_CONF_DETECT_INC_
#define _S_SYSTEM_CONF_DETECT_INC_

/////////////////////////////////////////////////////////////////////
// Must be a C++ compiler
#ifndef __cplusplus
	#error SLIB requires C++ compilation (use a .cpp suffix)
#endif

///////////////////////////////////////////////
// Compiler version
#if defined( _MSC_VER )
	#if _MSC_VER >= 1600
		#define _SLIB_CPP11
	#endif
#endif

///////////////////////////////////////////////
// detect debug option
#if defined(DEBUG) && !defined(_DEBUG)
	#define _DEBUG
#endif

///////////////////////////////////////////////
// Detect IOS platform
#if defined ( __APPLE__ )
		
	#define _SPL_MAC

	/////////////////////////////////////////////////
	// detect unicode platform
	#if  defined( _UNICODE ) || defined( UNICODE )
		#define _SLIB_WCHAR
	#else
	#endif

	/////////////////////////////////////////////////
	// detect multithreaded platform
	#ifdef _MT
		#define _SLIB_MT
	#endif

	/////////////////////////////////////////////////
	// prefered computer word size in bytes
	#define _SLIB_CONF__WORD_SIZE					4

	/////////////////////////////////////////////////
	// string allocation step
	#define _SLIB_CONF__MIN_STEP_STRING_ALLOC		2
#endif

///////////////////////////////////////////////
// Detect WIN32 platform
#if defined( _WIN32 ) || defined( WIN32 )

	#ifdef _DEBUG
		#define _SLIB_DEBUG_ALLOCATION
	#endif

	// disable Security Enhancements warnings
	#pragma warning(disable : 4996)

    // warning C4355: 'this' : used in base member initializer list
	#pragma warning(disable : 4355)

	// set win32 platform
	#define _SPL_WIN32

	/////////////////////////////////////////////////
	// detect unicode platform
	#if  defined( _UNICODE ) || defined( UNICODE )
  		#define _SLIB_WCHAR
	#else
	#endif

	/////////////////////////////////////////////////
	// detect multithreaded platform
	#ifdef _MT
		#define _SLIB_MT
	#endif

	/////////////////////////////////////////////////
	// prefered computer word size in bytes
	#define _SLIB_CONF__WORD_SIZE					4

	/////////////////////////////////////////////////
	// string allocation step
	#define _SLIB_CONF__MIN_STEP_STRING_ALLOC		2

#endif // WIN32


#endif // _S_SYSTEM_CONF_DETECT_INC_
