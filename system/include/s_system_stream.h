/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream.h
//  Created                 : 30 6 2007   13:01
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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

/**
 *	Streams
 */
namespace Streams
{
	using namespace System;
	using namespace System::Types;
	using namespace System::Cnt;

	#include "s_system_stream_int.h"
	#include "s_system_stream_file.h"
	#include "s_system_stream_fmem.h"
	#include "s_system_stream_archive.h"
	#include "s_system_stream_archive_provider_res.h"
	#include "s_system_stream_mac.h"
	#include "s_system_stream_rstr.h"
}