/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_dep.h
//	Created                 : 19 01 2011   22:33
//	File path               : SLibF\system\Include
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      SLib header depependensy
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

// Xml -> Vector, Map, Error
#ifdef _use_Xml_
	#ifndef _use_sVector_
		#define _use_sVector_
	#endif

	#ifndef _use_sMap_
		#define _use_sMap_
	#endif

	#ifndef _use_sError_
		#define _use_sError_
	#endif
#endif

// Stream - > Files, Vector, Error, Map
#ifdef _use_Streams_
	#ifndef _use_Files_
		#define _use_Files_
	#endif

	#ifndef _use_sVector_
		#define _use_sVector_
	#endif

	#ifndef _use_sMap_
		#define _use_sMap_
	#endif

	#ifndef _use_sError_
		#define _use_sError_
	#endif

#endif 

// Thread - > Events
#ifdef _use_Thread_
	#ifndef _use_sEvent_
		#define _use_sEvent_
	#endif
#endif 

// Files - > sError
#ifdef _use_Files_
	#ifndef _use_sError_
		#define _use_sError_
	#endif
#endif

// sError - > sObject
#ifdef _use_sError_
	// 
	#ifndef _use_sObject_
		#define _use_sObject_
	#endif
	
#endif

// d3Math - > sVector;
#ifdef _use_d3Math_
	#ifndef _use_sVector_
		#define _use_sVector_
	#endif
#endif

// ContUtils - > sVector
#ifdef _use_Cont_Utils_	
	#ifndef _use_sVector_
		#define _use_sVector_
	#endif
#endif

