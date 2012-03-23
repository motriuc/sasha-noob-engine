/////////////////////////////////////////////////////////////////////
//  File Name           : ed2_ui_label.cpp
//  Created             : 23 3 2012
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
#include "ed3_ui_label.h"

#include "rd3_render.h"

namespace Ed3
{
//-------------------------------------------------------------------
uiLabel::uiLabel( const sString& name ) :
	_BaseClass( name ),
	_text( _S("<Label>") )
{
}

//-------------------------------------------------------------------
uiLabel::~uiLabel()
{
}

//-------------------------------------------------------------------
sBool uiLabel::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( _BaseClass::LoadFromXMLSubnode( element, loadParams ) )
		return sTrue;

	return sFalse;
}

//-------------------------------------------------------------------
void uiLabel::Render2D( const d3RenderData& renderData )
{
	d2Vector textSize = _uiFont().GetTextSize( _text );

	d2Vector pos( - textSize.x / textSize.y, 1.0f );
	RenderText( _text, pos, 2.0f, _uiFontColor );
}

}