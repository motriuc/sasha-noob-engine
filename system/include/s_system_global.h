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
	void DebugWarning( const sChar* pMessage );
	void DebugWarning( const sString& message );

	/**
	 * Shows a Warning message
	 */
	void ShowWarning( const sChar* pMessage );
	void ShowWarning( const sString& message );
   
	/**
	 * Shows the Error message
	 */
	void ShowError( const sChar* pMessage );
	void ShowError( const sString& message );

	/**
	 *	Shows a message Message
	 */
	void ShowMessage( const sChar* pMessage );
	void ShowMessage( const sString& message );
	/**
	 *	Exit from process
	 */
	void Exit( sInt returnCode );

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
