/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_b.cpp
//  Created                 : 23 6 2007   23:24
//  File path               : SLibF\system\Cpp
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

namespace System
{
namespace CharsTrait
{
using namespace Types;

const SBCHAR* BChar::NewLine = "\r\n";

//------------------------------------------------------------------
sInt BChar::FindReverse( const SBCHAR* pChars, const SBCHAR* chSet, sUInt from )
{
	__S_ASSERT( pChars != NULL );
	__S_ASSERT( chSet != NULL );
	__S_ASSERT( from > 0 );

	const SBCHAR* c = pChars + from;

	while( c >= pChars )
	{
		const SBCHAR* p = chSet;
    
		while( *p )
		{
			if( *p == *c )
				return (sInt)(c - pChars);
			p++;
		}   
		c--;
	}

	return -1;
}

}}
