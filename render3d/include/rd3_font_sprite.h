/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_font_sprite.h
//  Created                 : 22 1 2012   19:58
//  File path               : SLibF\render3d\include
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
#include "rd3_dvertexbuffer.h"
#include "rd3_texture.h"

namespace Rd3
{

using namespace System;
	
/**
 * SpriteChar
 */
class SpriteChar
{
public:
	SpriteChar()
	{
	}
	
	SpriteChar( sChar ch, sInt x1, sInt y1, sInt x2, sInt y2 ) :
		_ch( ch ),
		_x1( x1 ),
		_y1( y1 ),
		_x2( x2 ),
		_y2( y2 )
	{
	}
	
	sChar GetChar() const { return _ch; }
	
	sInt Width() const { return System::FMath::Abs( _x1 - _x2 ); }
	sInt Height() const { return System::FMath::Abs( _y1 - _y2 ); }
	
	sInt X1() const { return _x1; }
	sInt Y1() const { return _y1; }
	sInt X2() const { return _x2; }
	sInt Y2() const { return _y2; }
private:
	sChar	_ch;
	sInt	_x1;
	sInt	_y1;
	sInt	_x2;
	sInt	_y2;
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
	const Texture& GetTexture() const { return _texture(); }

	/**
	 * 
	 */
	void SetTexture( Texture* pTexture ) { _texture = pTexture; }
	void SetTexture( const sString& name );

	/**
	 *
	 */
	virtual void LoadFromXml( const Xml::BaseDomNode& node, const Def& def ) throws_error;

	/**
	 *
	 */
	void LoadFromFntFile( const sString& fileName, const Def& def, const Streams::StreamArchive& archive ) throws_error;
	void LoadFromFntStream( const Streams::IInputStream& stream ) throws_error;
	
	
	/**
	 *
	 */
	virtual RenderString* CreateRenderString();

	/**
	 *
	 */
	virtual d3Float ScreenRenderText( RenderState& rstate, const sString& text, const d2Vector& pos, sRGBColor color );

	/**
	 *
	 */
	virtual void RenderText( Rd3::RenderState& rstate, const sString& text, const d2Vector& pos, d3Float height, sRGBColor color );

	/**
	 *
	 */
	d2Vector GetTextSize( const sString& text ) const;

protected:	
	/**
	 *
	 */
	void AddSprite( const SpriteChar& sp );
private:
	sMap<sChar, SpriteChar>	_charMap;
protected:
	use_resource<Rd3::Texture> _texture;
	use_resource<Rd3::DynamicVertexBuffer> _vb;
	use_resource<Rd3::Effect> _effectScreen;
	use_resource<Rd3::Effect> _effect;

private:	
	void AddSpriteFromFntString( const sString& str );
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
	virtual void ScreenRenderText( RenderState& rstate, const sString& text, const d2Vector& pos, sRGBColor color );
	~SprireRenderString();
protected:
	const FontSprite& fontSprite()	{ return reinterpret_cast<const FontSprite&> (font()) ; }
	
private:
	sString				_text;
	d2Vector			_pos;
	
	use_resource<Rd3::VertexBuffer>	_vb;
	use_resource<Rd3::Effect> _effectScreen;

	friend class FontSprite;
};
	
}

#endif // _RD3_FONT_SPRITE_H_