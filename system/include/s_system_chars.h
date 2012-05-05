/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars.h
//  Created                 : 23 6 2007   23:12
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
#ifndef _SYSTEM_CHARS_INC_
#define _SYSTEM_CHARS_INC_

namespace CharsTrait
{
	using namespace Types;
	
	#include "s_system_chars_b.h"
	#include "s_system_chars_w.h"

}

#ifdef _SLIB_WCHAR
	typedef CharsTrait::WChar Chars;
	typedef CharsTrait::BChar CharsO;
#else
	typedef CharsTrait::BChar Chars;
	typedef CharsTrait::WChar CharsO;
#endif

#endif // _SYSTEM_CHARS_INC_
