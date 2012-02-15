/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_types.h
//	Created                 : 23 6 2007   22:40
//	File path               : C:\Sasha\C++\SLibF\system\Include
//	Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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
#ifndef _SYSTEM_TYPES_INC_
#define _SYSTEM_TYPES_INC_

/**
 *	System types
 */
namespace Types
{
	#include "s_system_types_base.h"
	#include "s_system_string.h"

#ifdef _use_d3Math_
	#include "s_system_types_d3math.h"
#endif

#ifdef _use_d2Math_
	#include "s_system_types_d2math.h"
#endif

}

/**
 * no copy class
 */
class class_nocopy
{
public:
	class_nocopy() {}
private:
	class_nocopy( const class_nocopy& ) {}
	void operator = ( const class_nocopy& ) {}
};

#endif // _SYSTEM_TYPES_INC_
