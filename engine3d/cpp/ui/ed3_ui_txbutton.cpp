/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_button.cpp
//  Created             : 20 3 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\cpp\ui
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////

#include "ed3afx.h"
#include "ed3_ui_txbutton.h"

#include "rd3_render.h"

namespace Ed3
{
//-------------------------------------------------------------------
uiTxButton::uiTxButton( const sString& name ) :
	_BaseClass( name )
{
}

//-------------------------------------------------------------------
uiTxButton::~uiTxButton()
{
}

//-------------------------------------------------------------------
sBool uiTxButton::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( _BaseClass::LoadFromXMLSubnode( element, loadParams ) )
		return sTrue;

	if( element.GetName() == _S("up") )
	{
		_txUp = loadParams.render.UseTexture( element.GetAttributes()[ATTR_TEXTURE] );

		_txUp1.x = element.GetAttributeValue( ATTR_X1, 0.0f );
		_txUp1.y = element.GetAttributeValue( ATTR_Y1, 0.0f );
		_txUp2.x = element.GetAttributeValue( ATTR_X2, 0.0f );
		_txUp2.y = element.GetAttributeValue( ATTR_Y2, 0.0f );

		return sTrue;
	}

	if( element.GetName() == _S("down") )
	{
		_txDown = loadParams.render.UseTexture( element.GetAttributes()[ATTR_TEXTURE] );

		_txDown1.x = element.GetAttributeValue( ATTR_X1, 0.0f );
		_txDown1.y = element.GetAttributeValue( ATTR_Y1, 0.0f );
		_txDown2.x = element.GetAttributeValue( ATTR_X2, 0.0f );
		_txDown2.y = element.GetAttributeValue( ATTR_Y2, 0.0f );

		return sTrue;
	}

	return sFalse;
}

//-------------------------------------------------------------------
void uiTxButton::Render2D( const d3RenderData& renderData )
{	
	if( IsUp() )
	{
		RenderTexture( GetRectangle().Min(), GetRectangle().Max(), _txUp, _txUp1, _txUp2 );
	}
	else
	{
		RenderTexture( GetRectangle().Min(), GetRectangle().Max(), _txDown, _txDown1, _txDown2 );
	}
}

}