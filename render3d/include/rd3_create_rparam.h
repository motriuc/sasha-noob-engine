/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_create_rparam.h
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
#ifndef _RD3_CREATE_RPARAM_H_
#define _RD3_CREATE_RPARAM_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

namespace Rd3
{

using namespace System::Types;

/**
 * forward declarations
 */

_PLATFORM struct Dx9RenderParams;
_PLATFORM struct EAGLRenderParams;

/**
 * RenderCreateParams
 */ 
class RenderCreateParams
{
public:
	/**
	 *
	 */
	~RenderCreateParams();

	/**
	 * Returns render type
	 */
	RenderType::RenderType GetRenderType() const { return _renderType; }

protected:
	/**
	 *
	 */
	RenderCreateParams( RenderType::RenderType renderType );

	/**
	 *
	 */
	RenderCreateParams( const RenderCreateParams& src );

	/**
	 *
	 */
	void operator = ( const RenderCreateParams& src );

private:
	RenderType::RenderType    _renderType;
};

#ifdef _SPL_MAC
	
/**
 * EAGL render params
 */
class EAGLRenderCreateParams : public RenderCreateParams
{
private:
	typedef RenderCreateParams _BaseClass;
public:
	EAGLRenderCreateParams();
	EAGLRenderCreateParams( MACOSView* view );
	
	EAGLRenderCreateParams( const EAGLRenderCreateParams& src );
	
	void operator = ( const EAGLRenderCreateParams& src );
	
	~EAGLRenderCreateParams();

	_PLATFORM const struct EAGLRenderParams& GetParams() const { return *_pRenderParams; }
private:
	struct EAGLRenderParams* _pRenderParams;
};
	
#endif
	
#ifdef _SPL_WIN32
	
/**
 * DX9 Create render params
 */
class DX9RenderCreateParams : public RenderCreateParams
{
private:
	typedef RenderCreateParams _BaseClass;
public:
	/**
	 *
	 */
	DX9RenderCreateParams();
	
	/**
	 *
	 */
	DX9RenderCreateParams( HWND hWnd );
	
	/**
	 *
	 */
	DX9RenderCreateParams( const DX9RenderCreateParams& src );

	/**
	 *
	 */
	~DX9RenderCreateParams();

	/**
	 *
	 */
	void operator = ( const DX9RenderCreateParams& src );

	/**
	 *
	 */
	_PLATFORM const struct Dx9RenderParams& GetParams() const { return *_pRenderParams; }
private:
	struct Dx9RenderParams*			_pRenderParams;
};
	
#endif

}

#endif // _RD3_CREATE_RPARAM_H_