/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mem.cpp
//  Created                 : 15 6 2007   22:18
//  File path               : SLibF\system\cpp
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
#include "s_system.h"

namespace System { namespace Memory {
	
using namespace Types;

//-------------------------------------------------------------------
SWORD GetWHashCode( const void* pBuf, sUInt nCount )
{
	const SBYTE* pPos = (const SBYTE*) pBuf;
	register SWORD ret = 0;
	while( nCount >= sizeof( SBYTE ) )
	{
		ret = ( ret << ( 2*sizeof( SWORD ) + 1 ) ) | 
			  ( ret >> ( 6*sizeof( SWORD ) - 1 ) );
		ret = ( ret & 0xFF00 ) | ( ret ^ (SWORD)(*pPos) );
		pPos++;
		nCount-= sizeof(SWORD);
	}

	return ret;
}

//-------------------------------------------------------------------
SDWORD GetDWHashCode( const void* pBuf, sUInt nCount )
{
	const SWORD* pPos = (const SWORD*) pBuf;
	register SDWORD ret = 0;
	while( nCount >= sizeof( SWORD ) )
	{
		ret = ( ret << ( 2*sizeof( SDWORD ) + 1 ) ) | 
			  ( ret >> ( 6*sizeof( SDWORD ) - 1 ) );
		ret = ( ret & 0xFFFF0000 ) | ( ret ^ (SDWORD)(*pPos) );
		pPos++;
		nCount-= sizeof(SDWORD);
	}

	return ret;
}

//-------------------------------------------------------------------
void Xor( void* pBuf, SBYTE val, sUInt uCount )
{
	SBYTE* pSrc = (SBYTE*)pBuf;
	while( uCount-- )
	{
		*pSrc ^= val;
		pSrc++;
	}
}

//-------------------------------------------------------------------
void XorW( void* pBuf, SWORD val, sUInt uCount )
{
	SWORD* pSrc = (SWORD*) pBuf;
	sUInt wCount = uCount / 2;

	while( wCount-- )
	{
		*pSrc ^= val;
		pSrc++;
	}

	if( uCount % 2 == 1 )
		*((SBYTE*)pSrc ) ^= (SBYTE) val;
}


}}
