/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_image.cpp
//  Created             : 1 4 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\include\ui
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
#include "ed3_ui_image.h"

#include "rd3_render.h"

namespace Ed3
{
//------------------------------------------------------------------
uiImage::uiImage( const sString& name ) :
	_BaseClass( name )
{
}

//------------------------------------------------------------------
uiImage::~uiImage()
{

}

//------------------------------------------------------------------
void uiImage::Render2D( const d3RenderData& renderData )
{
	RenderTexture( GetRectangle().Min(), GetRectangle().Max(), _texture, _tx1, _tx2 );
}

//------------------------------------------------------------------
sBool uiImage::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( _BaseClass::LoadFromXMLSubnode( element, loadParams ) )
		return sTrue;

	if( element.GetName() == _S("texture") )
	{
		_texture = loadParams.render.UseTexture( element.GetAttributes()[ATTR_TEXTURE] );

		_tx1.x = element.GetAttributeValue( ATTR_X1, 0.0f );
		_tx1.y = element.GetAttributeValue( ATTR_Y1, 0.0f );
		_tx2.x = element.GetAttributeValue( ATTR_X2, 0.0f );
		_tx2.y = element.GetAttributeValue( ATTR_Y2, 0.0f );

		return sTrue;
	}

	return sFalse;
}
}
