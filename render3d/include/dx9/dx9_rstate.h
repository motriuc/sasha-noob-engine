/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_rstate.h
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

#ifndef _DX9_RSTATE_H_
#define _DX9_RSTATE_H_

#include "rd3_rstate.h"

class Dx9RenderState : public Rd3::WorldRenderState
{
private:
	typedef Rd3::WorldRenderState _BaseClass;
public:
	Dx9RenderState( Rd3::Render* owner );

	/**
	 *
	 */
	virtual void BeginWorldRender( const Rd3::EngineDataForRender& edata );
	virtual void BeginRenderObject();

	/**
	 *
	 */
	virtual void EndWorldRender();


	/**
	 *
	 */
	virtual void RenderPrimitive( const Rd3::VertexBuffer* vb, Rd3::PrimitiveType::PrimitiveType type );
	virtual void RenderPrimitive( const Rd3::VertexBuffer* vb, const Rd3::IndexBuffer* ib, Rd3::PrimitiveType::PrimitiveType type );
	virtual void RenderPrimitive( const Rd3::DynamicVertexBuffer* vb, Rd3::PrimitiveType::PrimitiveType type );

	virtual void Clear( System::Types::sRGBColor color );

private:
	IDirect3DSurface9*	_pTmpSurface;

	IDirect3DSurface9*	_pBackBuffer;
	IDirect3DSurface9*	_pDepthStencil;

	void SetRenderTarget( Rd3::Texture* pRenderTarget );
	void UnsetRenderTarget();

	void RenderPrimitive( 
		LPDIRECT3DVERTEXBUFFER9 pVb,
		UINT offset, 
		UINT vertexSize, 
		UINT vertexCount,
		DWORD dwFVF,
		Rd3::PrimitiveType::PrimitiveType type
	);
};


#endif // _DX9_RSTATE_H_
