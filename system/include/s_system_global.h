/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_global.h
//  Created                 : 28 6 2007   17:01
//  File path               : SLibF\system\Include
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
#ifndef _SYSTEM_GLOBAL_INC_
#define _SYSTEM_GLOBAL_INC_

/**
 *	Platform namespace
 */
namespace Platform
{
	using namespace Types;
	
	/**
	 * logs debug level warning
	 */
	static void DebugWarning( const sChar* pMessage );

	/**
	 * Shows a Warning message
	 */
	static void ShowWarning( const sChar* pMessage );
   
	/**
	 * Shows the Error message
	 */
	static void ShowError( const sChar* pMessage );

	/**
	 *	Shows a message Message
	 */
	static void ShowMessage( const sChar* pMessage );
	
	/**
	 *	Exit from process
	 */
	static void Exit( sInt returnCode );

	/**
	 *	Tic count in msec
	 */
	sUInt GetTick();

	/**
	 * High precizion tick in sec
	 */
	sDouble GetTickD();
	
#ifdef _SPL_WIN32
	#include "s_system_global_win32.inl"
#endif

#ifdef _SPL_MAC
	#include "s_system_global_mac.inl"
#endif

}

#endif // _SYSTEM_GLOBAL_INC_
