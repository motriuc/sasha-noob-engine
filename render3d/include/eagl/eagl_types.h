/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_types.h
//	Created                 : 11 1 2012   13:05
//	File path               : SLibF\render3d\include\eagl
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
#ifndef _EAGL_TYPES_H_
#define _EAGL_TYPES_H_

#ifndef _EAGL_CONF_H_
	#error eagl_conf.h must be included
#endif


namespace Rd3
{

using namespace System::Types;

/**
 * EAGLRenderParams
 */
struct EAGLRenderParams
{
	MACOSView* _view;
	
	void SetDefault()
	{
		_view = NULL;
	}
};

}

#endif // _DX9_TYPES_H_