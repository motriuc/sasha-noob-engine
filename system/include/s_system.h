/////////////////////////////////////////////////////////////////////
//  File Name               : s_system.h
//  Created                 : 14 6 2007   11:43
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

#ifndef _S_SYS_INC_
#define _S_SYS_INC_
//////////////////////////////////////////////////////////
// Use library modules defines

// **** RTTI
//
//  _use_sObject_       - use Objects
//  _use_sError_        - use Errors
//  _use_sEvent_        - use sEvent
//  _use_Thread_        - use Thread

// **** Continers
// _use_sVector_        - to use sVector
// _use_sMap_           - to use sMap
// _use_Cont_Utils_     - continer utils

// **** Math
// _use_d3Math_         - d3 math system base library 
// _use_d2Math_         - d2 math system base library 

// Files 
// _use_Files_          - file utils

// Streams 
// _use_Streams_        - stream utils

// Xml
// _use_Xml_            - xml utils


// Object entity rating description
// RATING( ++- )
// 1. Single thread Unit tested
// 2. Multi thread Unit tested
// 3. Teste in production

/**
 *	Configuration and platform detect headers
 */
#include "s_system_conf_def.h"
#include "s_system_conf_detect.h"
#include "s_system_conf_inc.h"
#include "s_system_macro.h"
#include "s_system_debug.h"
#include "s_system_dep.h"

namespace System
{
	// forward declarations
	namespace Streams
	{
		class IInputStream;
		class IOutputStream;
		class IIOStream;
	}
	
	namespace Xml {
		class BaseDomNode;
	}

	// requared headers
	#include "s_system_types.h"

#ifdef _use_sEvent_
	#include "s_system_evn.h"
#endif
	
	#include "s_system_mt.h"
	#include "s_system_mem.h"
	#include "s_system_chars.h"
	#include "s_system_rgbcolor.h"
	#include "s_system_t.h"

	#include "s_system_cnt.h"

	#include "s_system_string.inl"
	#include "s_system_formaters.h"
	#include "s_system_string_format.h"

	#include "s_system_global.h"

	#include "s_system_limit.h"
	#include "s_system_math.h"

	#include "s_system_ptr.h"
	#include "s_system_appenv.h"
	

#ifdef _use_sObject_
	#include "s_system_object.h"
#endif

#ifdef _use_sError_
	#include "s_system_error.h"
#endif

#ifdef _use_d3Math_
	#include "s_system_d3math.h"
#endif

#ifdef _use_d2Math_
	#include "s_system_d2math.h"
#endif

#ifdef _use_Files_
	#include "s_system_files.h"
#endif

#ifdef _use_Streams_
	#include "s_system_stream.h"
#endif

#ifdef _use_Xml_
	#include "s_system_xml.h"
#endif

} // System

#endif // _S_SYS_INC_
