/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_font_sprite.h
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

#ifndef _RD3_FONT_SPRITE_H_
#define _RD3_FONT_SPRITE_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_font.h"
#include "rd3_render_str.h"

namespace Rd3
{
	
/**
 * SpriteChar
 */
class SpriteChar
{
public:
	SpriteChar()
	{
	}
	
	SpriteChar( sChar ch, sInt x, sInt y, sInt w, sInt h ) :
		_ch( ch ),
		_x( x ),
		_y( y ),
		_w( w ),
		_h( h )
	{
	}
	
	/**
	 *
	 */
	sChar GetChar() const { return _ch; }
	
	sInt GetW() const { return _w; }
	sInt GetH() const { return _h; }
	
	sInt GetX() const { return _x; }
	sInt GetY() const { return _y; }
private:
	sChar	_ch;
	sInt	_x;
	sInt	_y;
	sInt	_w;
	sInt	_h;
};
				   
/**
 * FontSprite
 */
class FontSprite : public Font
{
private:
	typedef Font _BaseClass;
public:
	/**
	 *
	 */
	FontSprite( Render* owner, const sString& objectName );

	/**
	 *
	 */
	sBool GetSprite( sChar ch, SpriteChar& sprite ) const;
	
	/**
	 *
	 */
	const Rd3::Texture& GetTexture() const { return _texture(); }

	/**
	 *
	 */
	virtual void LoadFromXml( const System::Xml::BaseDomNode& node, const Def& def ) throws_error;

	/**
	 *
	 */
	virtual RenderString* CreateRenderString();

protected:	
	/**
	 *
	 */
	void AddSprite( const SpriteChar& sp );
private:
	sMap<sChar, SpriteChar>	_charMap;
protected:
	use_resource<Rd3::Texture> _texture;
};

/**
 * SprireRenderString
 */
class SprireRenderString : public RenderString
{
private:
	typedef RenderString _BaseClass;
protected:
	SprireRenderString( Font* font );
	
public:	
	virtual void RenderText( RenderState& rstate, const sString& text, const d2Vector& pos, sRGBColor color );
	~SprireRenderString();
protected:
	const FontSprite& fontSprite()	{ return reinterpret_cast<const FontSprite&> (font()) ; }
	
private:
	sString				_text;
	d2Vector			_pos;
	
	use_resource<Rd3::VertexBuffer>	_vb;
	use_resource<Rd3::Effect>		_effect;

	friend class FontSprite;
};
	
}

#endif // _RD3_FONT_SPRITE_H_