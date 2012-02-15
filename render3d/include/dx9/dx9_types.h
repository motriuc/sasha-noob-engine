/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_types.h
//	Created                 : 21 1 2011   13:05
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
#ifndef _DX9_TYPES_H_
#define _DX9_TYPES_H_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

namespace Rd3
{

using namespace System::Types;

struct Dx9RenderParams
{
	D3DPRESENT_PARAMETERS   _d3Options;

	sUInt                   _d3Adapter;
	D3DDEVTYPE              _d3DeviceType;
	HWND                    _d3hFocusWindow;
	sUInt                   _d3BehaviorFlags;

	void SetDefault()
	{
		System::Memory::Set( &_d3Options, 0, sizeof( D3DPRESENT_PARAMETERS ) );

		_d3Options.BackBufferCount              = 1;
		_d3Options.BackBufferWidth              = 0;
		_d3Options.BackBufferHeight             = 0;
		_d3Options.BackBufferFormat             = D3DFMT_A8R8G8B8;

		// Multisample
		_d3Options.MultiSampleType              = D3DMULTISAMPLE_NONE;
		_d3Options.MultiSampleQuality           = 0;

		_d3Options.SwapEffect                   = D3DSWAPEFFECT_FLIP;
		_d3Options.hDeviceWindow                = NULL;
		_d3Options.Windowed                     = TRUE;
		_d3Options.FullScreen_RefreshRateInHz   = D3DPRESENT_RATE_DEFAULT;

		_d3Options.EnableAutoDepthStencil       = TRUE;
		_d3Options.AutoDepthStencilFormat       = D3DFMT_D24S8;
		_d3Options.PresentationInterval         = D3DPRESENT_INTERVAL_IMMEDIATE;
		_d3Options.Flags                        = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;


		// other
		_d3Adapter          = D3DADAPTER_DEFAULT;
		_d3DeviceType       = D3DDEVTYPE_HAL;
		_d3hFocusWindow     = NULL;
		_d3BehaviorFlags    = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
};

}

#endif // _DX9_TYPES_H_