/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_at.h
//  Created                 : 23 6 2007   23:03
//  File path               : SLibF\system\include
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

/**
 * Thread safe increment
 * @param nNumber to increment
 */
sInt Inc( Atomic& nNumber );

/**
 * Thread safe decrement
 * @param nNumber number to decrement
 */
sInt Dec( Atomic& nNumber );

/**
 * If nNumber == i set nNumber = v returns true if swap did occured
 */
sBool SetIf( Atomic& nNumber, sInt i, sInt v );

/**
 * Thread safe increment
 * @param nNumber number to increment
 */
sUInt Inc( volatile sUInt& nNumber );

/**
 * Thread safe decrement
 * @param nNumber number to decrement
 */
sUInt Dec( volatile sUInt& nNumber );


// Platfom code
#ifdef _SPL_WIN32
	#include "s_system_mt_at_win32.inl"
#endif

#ifdef _SPL_MAC
	#include "s_system_mt_at_mac.inl"
#endif

