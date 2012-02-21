/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_aef_acolor.h
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

#ifndef _RD3_AEF_ACOLOR_INC_
#define _RD3_AEF_ACOLOR_INC_

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
 * AefAColor
 */
class AefAColor : public AfterEffectElement
{
public:
	AefAColor( Render& render );
	
	/**
	 *
	 */
	virtual void Apply( RenderState& rstate ) const;
	virtual void LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error;
	
	virtual sBool SetParam( const sString& name, d3Float value ); 
	
	/**
	 *
	 */
	void SetRLevel( d3Float r )		{ _rLum = r; }
	void SetGLevel( d3Float g )		{ _gLum = g; }
	void SetBLevel( d3Float b )		{ _bLum = b; }
	
	void SetContrast( d3Float c )	{ _contrast = c; }
private:
	use_resource<Effect>	_effect;
	Effect::Float			_rLum;
	Effect::Float			_gLum;
	Effect::Float			_bLum;
	Effect::Float			_contrast;
};

	
}



#endif // _RD3_AEF_ACOLOR_INC_
