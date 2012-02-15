/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_texture.h
//	Created                 : 31 1 2011   19:58
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

#ifndef _RD3_TEXTURE_H_
#define _RD3_TEXTURE_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"

namespace Rd3
{

	
/**
 * Texture
 */
class Texture : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	
	/**
	 *
	 */
	sInt GetWidth() const;

	/**
	 *
	 */
	sInt GetHeight() const;

	/**
	 *
	 */
	TextureType::TextureType GetTextureType() const;

	/**
	 *
	 */
	sBool ReadOnly() const;

	/**
	 *
	 */
	virtual void SaveAsBmp( const sString& fileName ) throws_error {}
protected:
	/**
	 *
	 */
	Texture( Render* owner, const sString& objectName, const TextureParams& params );
protected:
	sInt						_width;
	sInt						_height;
	sBool						_readOnly;
	TextureType::TextureType	_textureType;
	TextureParams				_params;
};

#include "rd3_texture.inl"

}

#endif // _RD3_TEXTURE_H_