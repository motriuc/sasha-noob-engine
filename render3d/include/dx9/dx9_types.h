/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_types.h
//  Created                 : 21 1 2011   13:05
//  File path               : SLibF\render3d\include\dx9
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
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

	void SetFromCommandLine()
	{
		AppEnviroment& env = AppEnviroment::Instance();
	
		// parse arg parameters
		sInt i = 0;
		while( i < env.GetCommandLineArgumentCount() )
		{
			sString param = env.GetCommandLineArgument( i );

			if( param == _S("-sync") )
			{
				_d3Options.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			}
			

			// 2 parameters flags
			if( i + 1 < env.GetCommandLineArgumentCount() )
			{

			}

			++i;
		}
	}
};

namespace VertexBufferStream
{
	/**
	 * converts vertex stream set to directX FVF
	 */
	inline DWORD GetDirectX_FVF( Set set )
	{
		DWORD dwFVF = 0;

		if( set & E_XYZ )
			dwFVF |= D3DFVF_XYZ;
		if( set & E_NORMAL )
			dwFVF |= D3DFVF_NORMAL;
		if( set & E_COLOR_DIF )
			dwFVF |= D3DFVF_DIFFUSE;
		if( set & E_TX1 )
			dwFVF |= D3DFVF_TEX1;
		if( set & E_TX2 )
			dwFVF |= D3DFVF_TEX2;
	
		return dwFVF;
	}

	inline DWORD GetDirectX_VertexSize( Set set )
	{
		DWORD dwSize = 0;

		if( set & E_XYZ )
			dwSize += sizeof( float ) * 3;
		if( set & E_NORMAL )
			dwSize += sizeof( float ) * 3;
		if( set & E_COLOR_DIF )
			dwSize += sizeof( char ) * 4;
		if( set & E_TX1 )
			dwSize += sizeof( float ) * 2;
		if( set & E_TX2 )
			dwSize += sizeof( float ) * 3;
	
		return dwSize;
	}

	/**
	 * Offsets
	 */
	class Offsets
	{
	public:
		Offsets( Set set )
		{
			_offPoint = -1;
			_offNormal = -1;
			_offDiffuseColor = -1;
			_offTx1 = -1;
			_offTx2 = -1;

			sInt offset = 0;

			if( set & Rd3::VertexBufferStream::E_XYZ )
			{
				_offPoint = offset;
				offset += sizeof(float) * 3;
			}

			if( set & Rd3::VertexBufferStream::E_NORMAL )
			{
				_offNormal = offset;
				offset += sizeof(float) * 3;
			}

			if( set & Rd3::VertexBufferStream::E_COLOR_DIF )
			{
				_offDiffuseColor = offset;
				offset += sizeof(char) * 4;
			}

			if( set & Rd3::VertexBufferStream::E_TX1 )
			{
				_offTx1 = offset;
				offset += sizeof(float) * 2;
			}

			if( set & Rd3::VertexBufferStream::E_TX2 )
			{
				_offTx2 = offset;
				offset += sizeof(float) * 2;
			}
		}

	public:
		sInt	_offPoint;
		sInt	_offNormal;
		sInt	_offDiffuseColor;
		sInt	_offTx1;
		sInt	_offTx2;
	};
}

}

#endif // _DX9_TYPES_H_