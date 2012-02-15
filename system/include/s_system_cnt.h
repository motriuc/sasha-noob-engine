/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_cnt.h
//	Created                 : 25 6 2007   0:59
//	File path               : SLibF\system\include
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
#ifndef _SYSTEM_CNT_INC_
#define _SYSTEM_CNT_INC_

namespace Cnt
{
	using namespace System::Types;
	
#ifdef _use_sVector_	
	#include "s_system_cnt_vector.h"
#endif

#ifdef _use_sMap_
	#include "s_system_cnt_map.h"
#endif

#ifdef _use_Cont_Utils_	
	#include "s_system_cnt_sort.h"
	#include "s_system_cnt_find.h"
	#include "s_system_cnt_sorted.h"
#endif
	
}

#endif // _SYSTEM_CNT_INC_
