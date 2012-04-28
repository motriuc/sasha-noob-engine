/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_w.cpp
//	Created                 : 23 6 2007   23:41
//	File path               : SLibF\system\Cpp
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

#include "s_system.h"

namespace System
{
namespace CharsTrait
{

using namespace Types; 

const SWCHAR* WChar::NewLine = L"\r\n";
const sInt WChar::NewLine_CharCount = 2;

//------------------------------------------------------------------
sInt WChar::FindReverse( const SWCHAR* pChars, const SWCHAR* chSet, sUInt from )
{
	__S_ASSERT( pChars != NULL );
	__S_ASSERT( chSet != NULL );
	__S_ASSERT( from > 0 );

	const SWCHAR* c = pChars + from;

	while( c >= pChars )
	{
		const SWCHAR* p = chSet;
    
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

}
}
