/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_conf.cpp
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

#include "dx9/dx9_conf.h"
#include "dx9/dx9_render.h"

#include "rd3_create_rparam.h"
#include "rd3_def.h"

#include "dx9/dx9_defs.h"
#include "dx9/dx9_types.h"
#include "dx9/dx9_vertexbuffer.h"
#include "dx9/dx9_effect.h"
#include "dx9/dx9_rstate.h"
#include "dx9/dx9_indexbuffer.h"
#include "dx9/dx9_texture.h"

////////////////////////////////////////////////////////////////////
// Direct3D Initializer
////////////////////////////////////////////////////////////////////
class D3D9
{
public:
	D3D9() : 
	  _pD3D( NULL )
	{
		::CoInitialize(NULL);
	}

	~D3D9()
	{
		if( _pD3D )
		{
			_pD3D->Release();
		}
		::CoUninitialize();
	}

	LPDIRECT3D9 GetHandle() const
	{
		if( _pD3D == NULL ) 
		{
			_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
			
			if( _pD3D == NULL )
			{
				System::Platform::ShowError( _S("Wrong DX Version") );
				System::Platform::Exit(1);
			}
		}
		return _pD3D;
	}

 
	LPDIRECT3D9 operator->() const
	{
		return GetHandle(); 
	}
  
	static D3D9& Instance()
	{
		static D3D9 gl_D3D;
		return gl_D3D;
	}
private:
	mutable LPDIRECT3D9           _pD3D;
};

////////////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------
Rd3::Render* Dx9Render::Create( const Rd3::DX9RenderCreateParams& param ) throws_error
{
	LPDIRECT3DDEVICE9 pD3DDevice = NULL;

	D3DPRESENT_PARAMETERS d3Options = param.GetParams()._d3Options;

	HRESULT hr = D3D9::Instance()->CreateDevice(
		param.GetParams()._d3Adapter,
		param.GetParams()._d3DeviceType,
		param.GetParams()._d3hFocusWindow,
		param.GetParams()._d3BehaviorFlags,
		&d3Options,
		&pD3DDevice
	);
  
	if( FAILED( hr ) && ( param.GetParams()._d3BehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING ) > 0 )
	{
		SDWORD d3Behavior = 
			( param.GetParams()._d3BehaviorFlags & ( ~D3DCREATE_HARDWARE_VERTEXPROCESSING ) ) |
			D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		hr = D3D9::Instance()->CreateDevice(
			param.GetParams()._d3Adapter,
			param.GetParams()._d3DeviceType,
			param.GetParams()._d3hFocusWindow,
			d3Behavior,
			&d3Options,
			&pD3DDevice
		);
	}

	if( FAILED( hr ) )
	{
		_DX9_ERROR( hr );
	}

	Dx9Render* pRender = new Dx9Render( pD3DDevice );

	pRender->_params    = param.GetParams();

	return pRender;
}

//------------------------------------------------------------------ 
Dx9Render::Dx9Render( LPDIRECT3DDEVICE9 pD3DDevice ) :
	_BaseClass( Rd3::RenderType::E_DX9 ),
	_pD3DDevice( pD3DDevice )
{
	__S_ASSERT( _pD3DDevice != NULL );
	_pRenderState = new Dx9RenderState( this );
}

//------------------------------------------------------------------ 
Dx9Render::~Dx9Render()
{
	delete _pRenderState;

	__S_ASSERT( _pD3DDevice != NULL );
	_pD3DDevice->Release();
}

//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBufferFromFile(
		const sString& objectName,
		const sString& path,
		const Rd3::StreamArchive& archive
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}
	
//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points 
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexTxCoord& txCoord
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexNList& normals
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}
	
//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexNList& normals,
		const Rd3::VertexTxCoord& txCoord
	) throws_error
{
	if( objectName.Length() > 0 && _vertexBufferPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	Dx9VertexBuffer* vb = NULL;
	try
	{
		vb = new Dx9VertexBuffer( this, objectName, points, normals, txCoord );
		
		if( objectName.Length() > 0 )
			_vertexBufferPool.Add( vb );
	}
	catch(...)
	{
		if (vb)
			vb->UnuseResource();
	
		throw;
	}
	
	return vb;
}
	
//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexTxCoord& txCoord1,
		const Rd3::VertexTxCoord& txCoord2
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexCList& diffuseColor,
		const Rd3::VertexTxCoord& txCoord1,
		const Rd3::VertexTxCoord& txCoord2
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexCList& diffuseColor
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexNList& normals,
		const Rd3::VertexCList& diffuseColor
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::IndexBuffer* Dx9Render::CreateIndexBuffer(
		const sString& objectName,
		const Rd3::IndexList& indexList
	) throws_error
{
	if( objectName.Length() > 0 && _indexBufferPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	Dx9IndexBuffer* pIndexBuffer = NULL;
	
	try 
	{
		pIndexBuffer = new Dx9IndexBuffer( this, objectName, indexList );
		
		if( objectName.Length() > 0 )
			_indexBufferPool.Add( pIndexBuffer );
	}
	catch (...)
	{
		if( pIndexBuffer )
			pIndexBuffer->UnuseResource();
		throw;
	}
	
	return pIndexBuffer;
}

//------------------------------------------------------------------ 
Rd3::Texture* Dx9Render::CreateTexture(
		const sString& objectName,
		sInt width, sInt height,
		Rd3::TextureType::TextureType type,
		const Rd3::TextureParams& params
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::Texture* Dx9Render::CreateTextureFromFile(
		const sString& objectName,
		const sString& fileName,
		const Rd3::StreamArchive& archive,
		Rd3::TextureType::TextureType type,
		const Rd3::TextureParams& params
	) throws_error
{

	if( objectName.Length() > 0 && _textureResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);

	
	Dx9Texture* pTexture = NULL;
	try
	{
		pTexture = new Dx9Texture( this, objectName, type, params );
		pTexture->LoadFromFile( fileName, archive );

		if( objectName.Length() > 0 )
			_textureResPool.Add( pTexture );
	}
	catch (...)
	{
		if( pTexture )
			pTexture->UnuseResource();
		throw;
	}
	
	return pTexture;
}

//------------------------------------------------------------------ 
Rd3::Effect* Dx9Render::CreateEffectFromString(
		const sString& objectName,
		const Rd3::Def& def,
		const sString& effectCode,
		const Rd3::StreamArchive& archive
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::Effect* Dx9Render::CreateEffectFromFile(
		const sString& objectName,
		const Rd3::Def& def,
		const sString& fileName,
		const Rd3::StreamArchive& archive
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
Rd3::Font* Dx9Render::CreateFontSystem(
		const sString& objectName,
		const sString& systemFontName,
		sInt fontSize
	) throws_error
{
	__S_ASSERT( sFalse );
	return NULL;
}

//------------------------------------------------------------------ 
void Dx9Render::FillDeviceDef( Rd3::Def& def )
{
	D3DCAPS9 caps;
	HRESULT hr = D3D9::Instance()->GetDeviceCaps( _params._d3Adapter, _params._d3DeviceType, &caps );
	if( FAILED( hr ) )
	{
		_DX9_ERROR( hr );
	}

	// Set max vertex shader versin
	if( caps.VertexShaderVersion >= D3DVS_VERSION( 3, 0 ) )
	{
		def.Define( _S_VS_VERSION, _S("vs_3_0") );
		def.Define( _S_VS_1_0 );
		def.Define( _S_VS_1_1 );
		def.Define( _S_VS_2_0 );
		def.Define( _S_VS_3_0 );
	}
	else if( caps.VertexShaderVersion >= D3DVS_VERSION( 2, 0 ) )
	{
		def.Define( _S_VS_VERSION, _S("vs_2_0") );
		def.Define( _S_VS_1_0 );
		def.Define( _S_VS_1_1 );
		def.Define( _S_VS_2_0 );
	}
	else if( caps.VertexShaderVersion >= D3DVS_VERSION( 1, 1 ) )
	{
		def.Define( _S_VS_VERSION, _S("vs_1_1") );
		def.Define( _S_VS_1_0 );
		def.Define( _S_VS_1_1 );
	}
	else if( caps.VertexShaderVersion >= D3DVS_VERSION( 1, 0 ) )
	{
		def.Define( _S_VS_VERSION, _S("vs_1_0") );
		def.Define( _S_VS_1_0 );
	}
	else
	{
	}

	// Set Maxim pixel shader version
	if( caps.PixelShaderVersion >= D3DPS_VERSION( 3, 0 ) )
	{
		def.Define( _S_PS_VERSION, _S("ps_3_0") );
		def.Define( _S_PS_1_0 );
		def.Define( _S_PS_1_1 );
		def.Define( _S_PS_2_0 );
		def.Define( _S_PS_3_0 );
	}
	else if( caps.PixelShaderVersion >= D3DPS_VERSION( 2, 0 ) )
	{
		def.Define( _S_PS_VERSION, _S("ps_2_0") );
		def.Define( _S_PS_1_0 );
		def.Define( _S_PS_1_1 );
		def.Define( _S_PS_2_0 );
	}
	else if( caps.PixelShaderVersion >= D3DPS_VERSION( 1, 1 ) )
	{
		def.Define( _S_PS_VERSION, _S("ps_1_1") );
		def.Define( _S_PS_1_0 );
		def.Define( _S_PS_1_1 );
	}
	else if( caps.PixelShaderVersion >= D3DPS_VERSION( 1, 0 ) )
	{
		def.Define( _S_PS_VERSION, _S("ps_1_0") );
		def.Define( _S_PS_1_0 );
	}
	else
	{
	}
}

namespace efx
{

#include "dx9/embeded_fx/debug_Solid_Color.inl"	// _debug_SolidColor
#include "dx9/embeded_fx/debug_Normals_Render.inl" // _debug_Render_Normals

}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void Dx9Render::Initialize( Rd3::Def& def, const Rd3::StreamArchive& archive ) throws_error
{
	FillDeviceDef( def );
#ifdef _D3_DEBUG_RENDER
/**
	CreateEffectFromString(
		_S("System.Debug.Fx.SolidVertexDiffuzeColor"),
		def,
		efx::_debug_SolidColor
	);

	CreateEffectFromString(
		_S("System.Debug.Fx.RenderNormals"),
		def,
		efx::_debug_Render_Normals
	);
*/
#endif

}

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexTxCoord& txCoord
	) throws_error
{
	return new Dx9VertexBuffer( this, objectName, points, txCoord );
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexTxCoord& txCoord1,
		const Rd3::VertexTxCoord& txCoord2
	) throws_error
{
	return new Dx9VertexBuffer( this, objectName, points, txCoord1, txCoord2 );
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexCList& diffuseColor,
		const Rd3::VertexTxCoord& txCoord1,
		const Rd3::VertexTxCoord& txCoord2
	) throws_error
{
	return new Dx9VertexBuffer( this, objectName, points, diffuseColor, txCoord1, txCoord2 );
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points 
	) throws_error
{
	return new Dx9VertexBuffer( this, objectName, points );
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points, 
		const Rd3::VertexCList& diffuseColor
	) throws_error
{

	return new Dx9VertexBuffer( this, objectName, points, diffuseColor );
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::VertexBuffer* Dx9Render::CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexNList& normals,
		const Rd3::VertexCList& diffuseColor
	) throws_error
{
	return new Dx9VertexBuffer( this, objectName, points, normals, diffuseColor );
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::Effect* Dx9Render::CreateEffectFromString(
		const sString& objectName,
		const Rd3::Def& def,
		const sString& effectCode
	) throws_error
{
	if( _effectResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);

	Dx9Effect* effect = NULL;
	try
	{
		effect = new Dx9Effect( this, objectName );
		effect->LoadFromString( effectCode, def );
		_effectResPool.Add( effect );
	}
	error_catch( System::Errors::Error )
	{
		if( effect )
			delete effect;

		throw error;
	}

	return effect;
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::Effect* Dx9Render::CreateEffectFromFile(
		const sString& objectName,
		const Rd3::Def& def,
		const sString& fileName
	) throws_error
{
	if( _effectResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);

	Dx9Effect* effect = NULL;
	try
	{
		effect = new Dx9Effect( this, objectName );
		effect->LoadFromFile( fileName, def );
		_effectResPool.Add( effect );
	}
	error_catch( System::Errors::Error )
	{
		if( effect )
			delete effect;

		throw error;
	}

	return effect;
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::IndexBuffer* Dx9Render::CreateIndexBuffer(
	const sString& objectName,
	const Rd3::IndexList& indexList
) throws_error
{
	return new Dx9IndexBuffer( this, objectName, indexList );
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Rd3::Texture* Dx9Render::CreateTexture(
		const sString& objectName,
		sInt width, sInt height,
		Rd3::TextureType::TextureType type
	) throws_error
{
	if( _textureResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);

	Dx9Texture* pTexture = new Dx9Texture( this, objectName, width, height, type );

	_textureResPool.Add( pTexture );

	return pTexture;
}
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
