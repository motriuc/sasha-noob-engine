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
//------------------------------------------------------------------
const SBYTE* WChar::ConvertFrom_UTF8( SWCHAR* pChars, sInt charBufferCount, const SBYTE* pBuffer, sInt bufferLength, sInt& charAdded )
{
	sInt origCharBufferCount = charBufferCount;

	while( charBufferCount > 0 && bufferLength > 0 ) 
	{
		SBYTE v = *pBuffer;

		if( v <= 0x7f )
		{
			*pChars = v;

			++pBuffer;
			++pChars;
			--charBufferCount;
			--bufferLength;
		}
		else
		{
			*pChars = L'?'; // To do
			++pChars;
			pBuffer += 2;
			--charBufferCount;
			bufferLength -=2;
		}
	}

	charAdded = origCharBufferCount - charBufferCount;

	if( bufferLength <= 0 )
		return NULL;

	return pBuffer;
}


}
}
