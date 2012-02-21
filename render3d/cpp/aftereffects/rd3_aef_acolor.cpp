/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_aef_acolor.cpp
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
#include "rd3_aef_acolor.h"
#include "rd3_render.h"
#include "rd3_rstate.h"

using namespace System::d2Math;

namespace Rd3
{
	
AUTO_REGISTER_AFTER_EFFECT_FACTORY( _S("color"), AefAColor )	
//-------------------------------------------------------------------	
AefAColor::AefAColor( Render& render ) :
	_rLum( 1.0f ),
	_gLum( 1.0f ),
	_bLum( 1.0f ),
	_contrast( 1.0f )
{
	_effect = render.UseEffect("system.after.effect.color");
}

//-------------------------------------------------------------------	
void AefAColor::Apply( RenderState& rstate ) const
{	
	_rLum			.Apply( _effect, _S("lumR") );
	_gLum			.Apply( _effect, _S("lumG") );
	_bLum			.Apply( _effect, _S("lumB") );
	_contrast		.Apply( _effect, _S("contrast") );
	
	rstate.SetEffect( _effect );
}

//-------------------------------------------------------------------	
sBool AefAColor::SetParam( const sString& name, d3Float value )
{
	if( name == _S("level.rgb") )
	{
		_rLum = value;
		_gLum = value;
		_bLum = value;
	}
	else if( name == _S("level.r") )
		_rLum = value;
	else if( name == _S("level.g") )
		_gLum = value;
	else if( name == _S("level.b") )
		_bLum = value;	
	else if( name == _S("contrast") )
		_contrast = value;
	else
		return sFalse;
	
	return sTrue;
}	

//-------------------------------------------------------------------	
void AefAColor::LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	_rLum = node.GetAttributeValue( _S("level.r"), 1.0f );
	_gLum = node.GetAttributeValue( _S("level.g"), 1.0f );
	_bLum = node.GetAttributeValue( _S("level.b"), 1.0f );
	_contrast = node.GetAttributeValue( _S("contrast"), 1.0f );
}
	
}
