/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_aef_blur.cpp
//  Created                 : 20 2 2012 
//  File path               : SLibF\render3d\cpp\aftereffects
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

#include "rd3afx.h"
#include "rd3_aef_blur.h"
#include "rd3_render.h"
#include "rd3_rstate.h"

using namespace System::d2Math;

namespace Rd3
{
	
AUTO_REGISTER_AFTER_EFFECT_FACTORY( _S("blur"), AefBlur )	
	
//-------------------------------------------------------------------	
AefBlur::AefBlur( Render& render )
{
	d2Vector size = render.GetScreen_SizeInPixels();
	_pixelWidth = 1.0f/ size.x;
	_pixelHeight = 1.0f/ size.y;
	_effect = render.UseEffect("system.after.effect.blur");
}

//-------------------------------------------------------------------	
void AefBlur::LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
}
	
//-------------------------------------------------------------------	
void AefBlur::Apply( RenderState& rstate ) const
{
	_pixelWidth.Apply( _effect, _S("pixelW") );
	_pixelHeight.Apply( _effect, _S("pixelH") ); 
	
	rstate.SetEffect( _effect );
}
	
}
