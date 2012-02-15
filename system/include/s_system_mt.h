/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt.h
//	Created                 : 14 6 2007   1:24
//	File path               : SLibF\system\include
//	Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      Utils for multithreaded computing
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////
#ifndef _S_SYSTEM_MT_INC_
#define _S_SYSTEM_MT_INC_

/**
 *	
 */
namespace Mt
{
	using namespace Types;

	#include "s_system_mt_at.h"
	#include "s_system_mt_cs.h"
	#include "s_system_mt_ev.h"	
	
}

#include "internal/int_tls_store.h"

#endif // _S_SYSTEM_MT_INC_

