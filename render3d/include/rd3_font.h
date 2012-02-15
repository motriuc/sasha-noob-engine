/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_font.h
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

#ifndef _RD3_FONT_H_
#define _RD3_FONT_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
#error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"

namespace Rd3
{
	
using namespace System::d2Math;
	
/**
 *
 */
class RenderString;
class RenderState;
class Render;
	
/**
 * Font
 */
class Font : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	
	/**
	 *
	 */
	virtual RenderString* CreateRenderString() = 0;
protected:
	
	/**
	 *
	 */
	Font( Render* owner, const sString& objectName ); 
private:	
};

/**
 * RenderString
 */
class RenderString 
{
protected:
	
	/**
	 *
	 */
	RenderString( Font* font ) :
		_font( font ),
		_fontRenderHeight( 0.0f )
	{
	}
public:
	/**
	 *
	 */
	virtual void RenderText( RenderState& rstate, const sString& text, const d2Vector& pos, sRGBColor color ) = 0;
	
	/**
	 * returns font render height
	 */
	d3Float RenderHeight() const { return _fontRenderHeight; }
protected:	
	Render& render()	{ return *(_font().GetOwner()); }
	const Font& font()	{ return _font(); }
private:
	use_resource<Font>	_font;
protected:	
	d3Float				_fontRenderHeight;
};
	
}

#endif // _RD3_CONF_H_