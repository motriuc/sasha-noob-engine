/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_rstate.cpp
//  Created                 : 20 1 2011   0:05
//  File path               : SLibF\render3d\cpp
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
#include "rd3afx.h"

#include "dx9/dx9_conf.h"
#include "dx9/dx9_rstate.h"
#include "dx9/dx9_render.h"
#include "dx9/dx9_vertexbuffer.h"
#include "dx9/dx9_effect.h"
#include "dx9/dx9_indexbuffer.h"
#include "dx9/dx9_texture.h"

//--------------------------------------------------------------------
namespace PrimitiveType
{
	inline D3DPRIMITIVETYPE GetDX9Type( Rd3::PrimitiveType::PrimitiveType p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < Rd3::PrimitiveType::COUNT );

		return (D3DPRIMITIVETYPE)( p + 1 ); // same as Dx plus 1
	}
}

//--------------------------------------------------------------------
Dx9RenderState::Dx9RenderState( Rd3::Render* owner ) :
	_BaseClass( owner ),
	_pTmpSurface( NULL ),
	_pDepthStencil( NULL ),
	_pBackBuffer( NULL )
{
}

//--------------------------------------------------------------------
void Dx9RenderState::SetRenderTarget( Rd3::Texture* pRenderTarget )
{
	__S_ASSERT( !pRenderTarget->ReadOnly() );
	__S_ASSERT( pRenderTarget->GetOwner() == GetOwner() );
	__S_ASSERT( _pTmpSurface == NULL );
	__S_ASSERT( _pBackBuffer == NULL );
	__S_ASSERT( _pDepthStencil == NULL );

	LPDIRECT3DDEVICE9 pDevice = Dx9Render::GetDX9Device( GetOwner() );
	__S_ASSERT( pDevice != NULL );

	// Save the device state
	HRESULT hr = pDevice->GetRenderTarget( 0, &_pBackBuffer );
	__S_ASSERT( SUCCEEDED(hr) );
	hr = pDevice->GetDepthStencilSurface( &_pDepthStencil );
	__S_ASSERT( SUCCEEDED(hr) );

	hr = ((Dx9Texture*)pRenderTarget)->GetHandle()->GetSurfaceLevel( 0, &_pTmpSurface );
    __S_ASSERT( SUCCEEDED(hr) );

	// Set render target
	hr = pDevice->SetRenderTarget( 0, _pTmpSurface );
    __S_ASSERT( SUCCEEDED(hr) );

	// set depth stencil
	hr = pDevice->SetDepthStencilSurface( ((Dx9Texture*)pRenderTarget)->GetDepthStencil() );
    __S_ASSERT( SUCCEEDED(hr) );
}

//--------------------------------------------------------------------
void Dx9RenderState::UnsetRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = Dx9Render::GetDX9Device( GetOwner() );
    __S_ASSERT( pDevice != NULL );

	__S_ASSERT( _pBackBuffer != NULL );
	__S_ASSERT( _pDepthStencil != NULL );

	HRESULT hr = pDevice->SetRenderTarget( 0, _pBackBuffer );
	__S_ASSERT( SUCCEEDED(hr) );
	_pBackBuffer = NULL;


	hr = pDevice->SetDepthStencilSurface( _pDepthStencil );
	__S_ASSERT( SUCCEEDED(hr) );
	_pDepthStencil = NULL;

	__S_ASSERT( _pTmpSurface != NULL );
	_pTmpSurface->Release();
	_pTmpSurface = NULL;
}

//--------------------------------------------------------------------
void Dx9RenderState::Clear( System::Types::sRGBColor color )
{
	LPDIRECT3DDEVICE9 pDevice = Dx9Render::GetDX9Device( GetOwner() );

    HRESULT hr = pDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET ,
		color,
		1.0f,
		0L
	);

    __S_ASSERT( SUCCEEDED(hr) );
}

//--------------------------------------------------------------------
void Dx9RenderState::BeginWorldRender( const Rd3::EngineDataForRender& edata )
{
	_BaseClass::BeginWorldRender( edata );

	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = Dx9Render::GetDX9Device( GetOwner() );
    __S_ASSERT( pDevice != NULL );

	{
		Rd3::Texture* pRenderTarget = GetRenderTarget();
		
		if( pRenderTarget != NULL )
			SetRenderTarget( pRenderTarget );
	}

	hr = pDevice->BeginScene();
	__S_ASSERT( SUCCEEDED(hr) );

    hr = pDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		RGB( 128, 128, 128 ),
		1.0f,
		0L
	);

    __S_ASSERT( SUCCEEDED(hr) );

	if( !GetCommonData().RenderWireframe() )
		pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	else
		pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void Dx9RenderState::EndWorldRender()
{
	LPDIRECT3DDEVICE9 pDevice = Dx9Render::GetDX9Device( GetOwner() );
    __S_ASSERT( pDevice != NULL );

	HRESULT hr = pDevice->EndScene();
	__S_ASSERT( SUCCEEDED(hr) );

	hr = pDevice->Present( NULL, NULL, NULL, NULL );
	__S_ASSERT( SUCCEEDED(hr) );

	{
		Rd3::Texture* pRenderTarget = GetRenderTarget();

		if( pRenderTarget != NULL )
			UnsetRenderTarget();
	}

	_BaseClass::EndWorldRender();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void Dx9RenderState::RenderPrimitive( const Rd3::VertexBuffer* vb, Rd3::PrimitiveType::PrimitiveType type )
{
	__S_ASSERT( vb!= NULL );
	__S_ASSERT( GetOwner() == vb->GetOwner() );
	__S_ASSERT( GetEffect() != NULL );
	__S_ASSERT( GetOwner() ==  GetEffect()->GetOwner() );

	LPDIRECT3DDEVICE9 pDevice = Dx9Render::GetDX9Device( GetOwner() );

	__S_ASSERT( pDevice != NULL );

	// Set effect params
	GetEffect()->Apply( *this );

	DWORD dwFVF = ((const Dx9VertexBuffer*)vb)->GetFVF();
	LPDIRECT3DVERTEXBUFFER9 pVb = ((const Dx9VertexBuffer*)vb)->GetHandle();
	LPD3DXEFFECT pEffect = ((const Dx9Effect*)GetEffect())->GetHandle();

	__S_ASSERT( dwFVF != 0 );
	__S_ASSERT( pVb != NULL );
	__S_ASSERT( pEffect != NULL );

	// Set Vertex stream format
	HRESULT hr = pDevice->SetFVF( dwFVF );
	__S_ASSERT( SUCCEEDED( hr ) );

	// Set vertex stream
	hr = pDevice->SetStreamSource(
		0,
		pVb,
		0,
		vb->GetVertexSize()
		);
	__S_ASSERT( SUCCEEDED( hr ) );

	D3DPRIMITIVETYPE dxprimitiveType = PrimitiveType::GetDX9Type( type );

	sUInt primitiveCount = Rd3::PrimitiveType::GetNumberOfPrimitives( 
		vb->GetCount(),
		type
	);
	
	UINT numPasses;

	hr = pEffect->Begin( &numPasses , 0 );
	__S_ASSERT( SUCCEEDED( hr ) );
	
	for( UINT i = 0; i < numPasses; i++ )
	{
		hr = pEffect->BeginPass( i );
		__S_ASSERT( SUCCEEDED( hr ) );

#ifdef _D3_DEBUG_RENDER
		if( GetCommonData().RenderWireframe() )
			pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

		if( GetCommonData().debug_RenderCulling() )
			pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		else
			pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
#endif

		hr = pDevice->DrawPrimitive(
			dxprimitiveType,
			0,
			primitiveCount
		);
		__S_ASSERT( SUCCEEDED( hr ) );

		hr = pEffect->EndPass();
		__S_ASSERT( SUCCEEDED( hr ) );
	}
	
	hr = pEffect->End();
	__S_ASSERT( SUCCEEDED( hr ) );
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void Dx9RenderState::RenderPrimitive( const Rd3::VertexBuffer* vb, const Rd3::IndexBuffer* ib, Rd3::PrimitiveType::PrimitiveType type )
{
	__S_ASSERT( vb!= NULL );
	__S_ASSERT( GetOwner() == vb->GetOwner() );
	__S_ASSERT( GetEffect() != NULL );
	__S_ASSERT( GetOwner() ==  GetEffect()->GetOwner() );
	__S_ASSERT( ib != NULL );
	__S_ASSERT( GetOwner() == ib->GetOwner() );

	LPDIRECT3DDEVICE9 pDevice = Dx9Render::GetDX9Device( GetOwner() );

	__S_ASSERT( pDevice != NULL );

	// Set effect params
	GetEffect()->Apply( *this );

	DWORD dwFVF = ((const Dx9VertexBuffer*)vb)->GetFVF();
	LPDIRECT3DVERTEXBUFFER9 pVb = ((const Dx9VertexBuffer*)vb)->GetHandle();
	LPD3DXEFFECT pEffect = ((const Dx9Effect*)GetEffect())->GetHandle();
	LPDIRECT3DINDEXBUFFER9 pIb = ((const Dx9IndexBuffer*)ib)->GetHandle();

	__S_ASSERT( dwFVF != 0 );
	__S_ASSERT( pVb != NULL );
	__S_ASSERT( pEffect != NULL );
	__S_ASSERT( pIb != NULL );

	// Set Vertex stream format
	HRESULT hr = pDevice->SetFVF( dwFVF );
	__S_ASSERT( SUCCEEDED( hr ) );

	// Set vertex stream
	hr = pDevice->SetStreamSource(
		0,
		pVb,
		0,
		vb->GetVertexSize()
		);
	__S_ASSERT( SUCCEEDED( hr ) );

	hr = pDevice->SetIndices( pIb );

	D3DPRIMITIVETYPE dxprimitiveType = PrimitiveType::GetDX9Type( type );

	sUInt primitiveCount = Rd3::PrimitiveType::GetNumberOfPrimitives( 
		ib->GetCount(),
		type
	);
	
	UINT numPasses;

	hr = pEffect->Begin( &numPasses , 0 );
	__S_ASSERT( SUCCEEDED( hr ) );
	
	for( UINT i = 0; i < numPasses; i++ )
	{
		hr = pEffect->BeginPass( i );
		__S_ASSERT( SUCCEEDED( hr ) );

#ifdef _D3_DEBUG_RENDER
		if( GetCommonData().RenderWireframe() )
			pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

		if( GetCommonData().debug_RenderCulling() )
			pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
		else
			pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
#endif

		hr = pDevice->DrawIndexedPrimitive(
			dxprimitiveType,
			0,
			0,
			vb->GetCount(),
			0,
			primitiveCount
		);
		__S_ASSERT( SUCCEEDED( hr ) );

		hr = pEffect->EndPass();
		__S_ASSERT( SUCCEEDED( hr ) );
	}
	
	hr = pEffect->End();
	__S_ASSERT( SUCCEEDED( hr ) );
}
