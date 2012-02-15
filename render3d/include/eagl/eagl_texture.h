/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_texture.h
//	Created                 : 18 1 2012   0:05
//	File path               : SLibF\render3d\include\eagl
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

#ifndef _EAGL_TEXTURE_H_
#define _EAGL_TEXTURE_H_

#ifndef _EAGL_CONF_H_	
	#error eagl_conf.h must be included
#endif

#include "rd3_texture.h"

#include <CoreGraphics/CGImage.h>

/**
 * EAGLTexture
 */
class EAGLTexture : public Rd3::Texture
{
private:
	typedef Rd3::Texture _BaseClass;
public:
	/**
	 *
	 */
	EAGLTexture( Rd3::Render* owner, const sString& objectName, Rd3::TextureType::TextureType type, const Rd3::TextureParams& params );

	/**
	 *
	 */
	EAGLTexture( Rd3::Render* owner, const sString& objectName, Rd3::TextureType::TextureType type, sInt width, sInt height, const Rd3::TextureParams& params );
 	
	/**
	 *
	 */
	~EAGLTexture();
	
	/**
	 *
	 */
	void LoadFromPngStream( const Streams::IInputStream& stream ) throws_error;
	
	/**
	 *
	 */
	void LoadFromFile( const sString& path, const Streams::StreamArchive& arch ) throws_error;
	
	/**
	 *
	 */
	void SetHandle( GLuint textId, sInt width, sInt height );
	
	/**
	 *
	 */
	GLuint GetHandle() const { return _texture; }
private:
	GLuint	_texture;
	
private:
	void LoadFromImage( CGImageRef image ) throws_error;
};


#endif // _EAGL_TEXTURE_H_