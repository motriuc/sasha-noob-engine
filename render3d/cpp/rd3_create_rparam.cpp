/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_create_rparam.cpp
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\cpp
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
#include "rd3afx.h"
#include "rd3_create_rparam.h"

#ifdef _SPL_WIN32
	#include "dx9/dx9_conf.h"
	#include "dx9/dx9_types.h"
#endif

#ifdef _SPL_MAC
	#include "eagl_conf.h"
	#include "eagl_types.h"
#endif


namespace Rd3
{

//-------------------------------------------------------------------
RenderCreateParams::RenderCreateParams( RenderType::RenderType renderType ) :
  _renderType( renderType )
{

}

//-------------------------------------------------------------------
RenderCreateParams::~RenderCreateParams()
{
}

//-------------------------------------------------------------------
RenderCreateParams::RenderCreateParams( const RenderCreateParams& src )
{
  _renderType = src._renderType;
}

//-------------------------------------------------------------------
void RenderCreateParams::operator = ( const RenderCreateParams& src )
{
  _renderType = src._renderType;
}

#ifdef _SPL_MAC
	
//-------------------------------------------------------------------
EAGLRenderCreateParams::EAGLRenderCreateParams() :
	_BaseClass( RenderType::E_EAGL )
{
	_pRenderParams = new EAGLRenderParams();
	_pRenderParams->SetDefault();	
}

//-------------------------------------------------------------------	
EAGLRenderCreateParams::EAGLRenderCreateParams( MACOSView* view ) :
	_BaseClass( RenderType::E_EAGL )
{
	_pRenderParams = new EAGLRenderParams();
	
	_pRenderParams->SetDefault();
	_pRenderParams->_view = view;
}

//-------------------------------------------------------------------	
EAGLRenderCreateParams::EAGLRenderCreateParams( const EAGLRenderCreateParams& src ) :
	_BaseClass( src )
{
	_pRenderParams = new EAGLRenderParams();
	*_pRenderParams = *src._pRenderParams;
}
	
//-------------------------------------------------------------------
void EAGLRenderCreateParams::operator = ( const EAGLRenderCreateParams& src )
{
	*_pRenderParams = *src._pRenderParams;
}

//-------------------------------------------------------------------	
EAGLRenderCreateParams::~EAGLRenderCreateParams()
{
	delete _pRenderParams;
}
	
	
#endif
	
#ifdef _SPL_WIN32

//-------------------------------------------------------------------
DX9RenderCreateParams::DX9RenderCreateParams() :
  _BaseClass( RenderType::E_DX9 )
{
	_pRenderParams = new Dx9RenderParams();
	_pRenderParams->SetDefault();
}

//-------------------------------------------------------------------
DX9RenderCreateParams::DX9RenderCreateParams( HWND hWnd ) :
  _BaseClass( RenderType::E_DX9 )
{
	_pRenderParams = new Dx9RenderParams();
	_pRenderParams->SetDefault();

	_pRenderParams->_d3hFocusWindow = hWnd;
}

//-------------------------------------------------------------------
void DX9RenderCreateParams::SetFromCommandLine()
{
	_pRenderParams->SetFromCommandLine();
}

//-------------------------------------------------------------------
DX9RenderCreateParams::DX9RenderCreateParams( const DX9RenderCreateParams& src ) :
  _BaseClass( src )
{
	_pRenderParams = new Dx9RenderParams();
	*_pRenderParams = *src._pRenderParams;
}
	
//-------------------------------------------------------------------
DX9RenderCreateParams::~DX9RenderCreateParams()
{
	delete _pRenderParams;
}

#endif // _SPL_WIN32


}