/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_texture.h
//	Created                 : 31 1 2011   20:25
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


#ifndef _DX9_TEXTURE_H_
#define _DX9_TEXTURE_H_

#include "rd3_texture.h"

/**
 * forward declarations
 */
namespace Rd3
{
	class Render;
}

/**
 *
 */
class Dx9Texture : public Rd3::Texture
{
private:
	typedef Rd3::Texture _BaseClass;
public:
	/**
	 *
	 */
	Dx9Texture( 
		Rd3::Render* owner, const sString& objectName, 
		sInt width, sInt height, Rd3::TextureType::TextureType type,
		const Rd3::TextureParams& params
	);

	/**
	 *
	 */
	virtual ~Dx9Texture();

public:
	/**
	 *
	 */
	LPDIRECT3DTEXTURE9 GetHandle() { return _pTexture; }

	/**
	 *
	 */
	IDirect3DSurface9* GetDepthStencil();
private:
	LPDIRECT3DTEXTURE9		_pTexture;
	IDirect3DSurface9*		_pDepthStencil;
};

#endif // _DX9_TEXTURE_H_