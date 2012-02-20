/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_aef_blur.h
//  Created                 : 20 2 2012 
//  File path               : SLibF\render3d\include\aftereffects
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

#ifndef _RD3_AEF_BLUR_INC_
#define _RD3_AEF_BLUR_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_after_effect.h"
#include "rd3_effect.h"

namespace  Rd3
{
	
/**
 * AefBlur
 */
class AefBlur : public AfterEffectElement
{
public:
	AefBlur( Render& render );
	
	/**
	 *
	 */
	virtual void Apply( RenderState& rstate ) const;
private:
	use_resource<Effect>	_effect;
	Effect::Float			_pixelWidth;
	Effect::Float			_pixelHeight;
};

	
}

#endif // _RD3_AEF_BLUR_INC_
