/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_conf.h
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\include\dx9
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

#ifndef _DX9_CONF_H_
#define _DX9_CONF_H_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#define DIRECTINPUT_VERSION  0x0800

#include <d3dx9core.h>
#include <d3d9.h>
#include <dinput.h>

#define _DX9_ERROR( _HR ) error_throw_arg( System::Errors::HRESULTError ) _HR )

using namespace System;
using namespace System::Types;
using namespace System::d3Math;


#endif // _DX9_CONF_H_