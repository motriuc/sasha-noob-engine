/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_render_str.h
//	Created                 : 3 3 2012   19:58
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
#ifndef _RD3_RENDER_STR_INC_
#define _RD3_RENDER_STR_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"
#include "rd3_font.h"

namespace Rd3
{
	
using namespace System::d2Math;

/**
 * RenderString
 */
class RenderString 
{
protected:
	/**
	 *
	 */
	RenderString( Font* font );
public:
	virtual ~RenderString() {}
	/**
	 * render the text
	 */
	virtual void RenderText( RenderState& rstate, const sString& text, const d2Vector& pos, sRGBColor color ) = 0;
	
	/**
	 * returns font render height
	 */
	d3Float RenderHeight() const;

protected:	
	Render& render();
	const Font& font();
private:
	use_resource<Font>	_font;
protected:	
	d3Float				_fontRenderHeight;
};

#include "rd3_render_str.inl"

}

#endif // _RD3_RENDER_STR_INC_
