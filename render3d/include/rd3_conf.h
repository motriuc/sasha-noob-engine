/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_conf.h
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\include
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


#ifndef _RD3_CONF_H_
#define _RD3_CONF_H_

///
//#define _D3_DEBUG_RENDER

// only for iOs
// #define _D3_ENABLE_RETINA_DISPLAY
#ifdef _DEBUG
	#define _D3_DEBUG_RENDER_COUNTERS
#endif
///
#define _D3_DEBUG_RENDER_ENABLE_COUNTERS

///
#define _D3_MAX_RENDER_LIGHTS		4


#endif // _RD3_CONF_H_