/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_texture.cpp
//  Created                 : 31 1 2011   20:35
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
#include "dx9/dx9_texture.h"
#include "dx9/dx9_render.h"

//-------------------------------------------------------------------
D3DFORMAT GetTextureDx9Format( Rd3::TextureType::TextureType type )
{
	switch( type )
	{
	case Rd3::TextureType::E_IMAGE:
		return D3DFMT_A8R8G8B8;

	}

	return D3DFMT_A8R8G8B8;
}

//-------------------------------------------------------------------
Dx9Texture::Dx9Texture( Rd3::Render* owner, const sString& objectName,
		sInt width, sInt height, Rd3::TextureType::TextureType type, const Rd3::TextureParams& params 
	) :
	_BaseClass( owner, objectName, params ),
	_pTexture( NULL ),
	_pDepthStencil( NULL )
{
	__S_ASSERT( width > 0 );
	__S_ASSERT( height > 0 );

	_textureType = type;
	_readOnly = sFalse;
	_width = width;
	_height = height;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateTexture(
		_width,										//	[in]           UINT Width,
		_height,									//	[in]           UINT Height,
		1,											//	[in]           UINT Levels,
		D3DUSAGE_RENDERTARGET,						//  [in]           DWORD Usage,
		GetTextureDx9Format( _textureType ),		//	[in]           D3DFORMAT Format
		D3DPOOL_DEFAULT,							//	[in]           D3DPOOL Pool
		&_pTexture,									//	[out, retval]  IDirect3DTexture9 **ppTexture
		NULL										//	[in]           HANDLE *pSharedHandle
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );
}

//-------------------------------------------------------------------
Dx9Texture::Dx9Texture( Rd3::Render* owner, const sString& objectName,
		Rd3::TextureType::TextureType type,
		const Rd3::TextureParams& params
	):
	_BaseClass( owner, objectName, params ),
	_pTexture( NULL ),
	_pDepthStencil( NULL )
{
	_textureType = type;
}

//-------------------------------------------------------------------
void Dx9Texture::LoadFromPngStream( const Streams::IInputStream& stream ) throws_error
{
	sInt size = stream.GetSize();
	ptr_array_unique<char> buffer( new char[size] );
	
	stream.Read( buffer, size );

	HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( 
		Dx9Render::GetDX9Device( GetOwner() ),
		buffer,
		size,
		0,   // width
		0,   // height
		0,   // mipLevel
		0, 
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&_pTexture
	);

	if( FAILED( hr ) )
		_DX9_ERROR( hr );

	D3DSURFACE_DESC desc;
	hr = _pTexture->GetLevelDesc( 0, &desc );

	__S_ASSERT( SUCCEEDED( hr ) );

	_width = desc.Width;
	_height = desc.Height;
}

//-------------------------------------------------------------------
void Dx9Texture::LoadFromFile( const sString& path, const Streams::StreamArchive& arch ) throws_error
{	
	if( path.EndsWith( _S(".png") ) )
	{
		ptr_unique<const Streams::IInputStream> pStream( arch.Open( path ) );
		LoadFromPngStream( pStream() );
	}
	else 
	{
		error_throw_arg( Errors::StringError )
			Format( _S("Unknown texture type: {1}" ) ) % path
		);
	}
}

//-------------------------------------------------------------------
IDirect3DSurface9* Dx9Texture::GetDepthStencil()
{
	if( _pDepthStencil != NULL )
		return _pDepthStencil;

	const struct Rd3::Dx9RenderParams& params = ((Dx9Render*)GetOwner())->Params();

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateDepthStencilSurface(
		_width,
		_height,
		params._d3Options.AutoDepthStencilFormat,
		params._d3Options.MultiSampleType,
		params._d3Options.MultiSampleQuality,
		TRUE,
		&_pDepthStencil,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	return _pDepthStencil;
}

//-------------------------------------------------------------------
Dx9Texture::~Dx9Texture()
{
	if( _pTexture != NULL )
		_pTexture->Release();

	if( _pDepthStencil != NULL )
		_pDepthStencil->Release();
}

//-------------------------------------------------------------------
