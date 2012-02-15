/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_font_sprite.h
//	Created                 : 22 1 2012   19:58
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

#ifndef _EAGL_FONT_SPRITE_H_
#define _EAGL_FONT_SPRITE_H_

#ifndef _EAGL_CONF_H_
	#error eagl_conf.h must be included
#endif

#include <CoreGraphics/CGContext.h>s
#include "rd3_font_sprite.h"

namespace Rd3
{
	class Texture;
}

class MeasureTextWithFont;

/**
 * EAGLFontSprite
 */
class EAGLFontSprite : public Rd3::FontSprite
{
private:
	typedef Rd3::FontSprite _BaseClass;
public:
	/**
	 *
	 */
	EAGLFontSprite( Rd3::Render* owner, const sString& objectName );
	
	/**
	 *
	 */
	void CreateFont( const sString& fontName, sInt fontSize ) throws_error;
	
	/**
	 *
	 */
	virtual Rd3::RenderString* CreateRenderString();
private:
	/**
	 *
	 */
	void DrawTheSprites( CGContextRef context, MeasureTextWithFont& measure, sInt textureW, sInt textureH );
};


/**
 * EAGLSprireRenderString
 */
class EAGLSprireRenderString : public Rd3::SprireRenderString
{
private:
	typedef SprireRenderString _BaseClass;
	
public:
	EAGLSprireRenderString( Rd3::Font* font );
};
	
#endif // _EAGL_FONT_SPRITE_H_