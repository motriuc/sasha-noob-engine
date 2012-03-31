/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mem.h
//  Created                 : 15 6 2007   21:54
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
#ifndef _S_SYSTEM_MEM_INC_
#define _S_SYSTEM_MEM_INC_

/**
 *	Memory functions
 */
namespace Memory
{
using namespace Types;

/**
 * Copy a chunk of memory
 * @param pDestination destination ptr
 * @param pSource source ptr
 * @param uCount size in bytes to copy
 */
void Copy( void* pDestination, const void* pSource, const sUInt uCount );

/**
 * Set memory bytes
 * @param pDestinatin destination ptr
 * @param ch byte to be set
 * @param nCount bytes count
 */
void Set( void* pDestination, SBYTE ch, sUInt nCount );

/**
 * Compare 2 chunk of memory
 * @param pA first block
 * @param pB second block
 * @param uCount bytes count
 * @return > 0 if pA > pB, =0 if pA = pB, < 0 if pA < pB
 */
sInt Compare( const void* pA, const void* pB, sUInt uCount );

/**
 * Returns a 32 bit hash code of an memory block
 * @param pBuf memory block
 * @param nCount size in bytes of memory block
 * @return Hash code
 */
SDWORD GetDWHashCode(  const void* pBuf, sUInt nCount );

/**
 * Returns a 16 bit hash code of an memory block
 * @param pBuf memory block
 * @param nCount size in bytes of memory block
 * @return Hash code
 */

SWORD GetWHashCode( const void* pBuf, sUInt nCount );
/**
 * Returns a hash code of an memory block
 * @param pBuf memory block
 * @param nCount size in bytes of memory block
 * @return Hash code
 */
sUInt GetHashCode( const void* pBuf, sUInt nCount );

/**
 * XOR a buffer
 * @param pBuf memory block
 * @param val value to xor
 * @param nCount size in bytes of memory block
 */
void Xor( void* pBuf, SBYTE val, sUInt uCount );

/**
 * XOR a buffer
 * @param pBuf memory block
 * @param val value to xor
 * @param nCount size in bytes of memory block
 */
void XorW( void* pBuf, SWORD val, sUInt uCount );

#include "s_system_mem.inl"

}


#endif // _S_SYSTEM_MEM_INC_
