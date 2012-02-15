/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_at.h
//	Created                 : 23 6 2007   23:03
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

#ifndef _SYSTEM_MT_AT_INC_
#define _SYSTEM_MT_AT_INC_

/**
 * Thread safe increment
 * @param nNumber to increment
 */
static sInt Inc( volatile sInt& nNumber );

/**
 * Thread safe decrement
 * @param nNumber number to decrement
 */
static sInt Dec( volatile sInt& nNumber );

/**
 * Thread safe increment
 * @param nNumber number to increment
 */
static sUInt Inc( volatile sUInt& nNumber );

/**
 * Thread safe decrement
 * @param nNumber number to decrement
 */
static sUInt Dec( volatile sUInt& nNumber );


// Platfom code
#ifdef _SPL_WIN32
	#include "s_system_mt_at_win32.inl"
#endif

#ifdef _SPL_MAC
	#include "s_system_mt_at_mac.inl"
#endif

#endif // _SYSTEM_MT_AT_INC_
