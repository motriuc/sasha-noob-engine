/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_font_sprite.cpp
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

#include "rd3afx.h"
#include "rd3_font_sprite.h"
#include "rd3_render.h"
#include "rd3_rstate.h"
#include "rd3_texture.h"
#include "rd3_vertexbuffer.h"
#include "rd3_effect.h"

using namespace System::d3Math;
using namespace System::d2Math;

namespace Rd3
{

//-------------------------------------------------------------------	
FontSprite::FontSprite( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName )
{
}
	
//-------------------------------------------------------------------	
void FontSprite::AddSprite( const SpriteChar& sp )
{
	_charMap.Add( sp.GetChar(), sp );
}
	
//-------------------------------------------------------------------	
sBool FontSprite::GetSprite( sChar ch, SpriteChar& sprite ) const
{
	return _charMap.Lookup( ch, sprite );
}

//-------------------------------------------------------------------	
SprireRenderString::SprireRenderString( Font* font ):
	_BaseClass( font )
{
	_effect = render().UseEffect( _S("system.font.fx.1") );
}

//-------------------------------------------------------------------	
void SprireRenderString::RenderText( RenderState& rstate, const sString& text, const d2Vector& pos, sRGBColor color )
{
	if( text != _text || _pos != pos )
	{
		_vb.ResourceFree();
		
		_text = text;
		_pos  = pos;
	
		d3Float x = -1.0f + 2.0f * _pos.x;
		d3Float y = 1.0f - 2.0f *_pos.y;
	
		d2Vector rdSize = render().GetRenderTarger_SizeInPixels();
	
		VertexPList vpoints;
		VertexTxCoord txpoints;
		
		_fontRenderHeight = 0.0f;
		
		d3Float cx = static_cast<d3Float>( fontSprite().GetTexture().GetWidth() );
		d3Float cy = static_cast<d3Float>( fontSprite().GetTexture().GetHeight() ); 
	
		for( sInt i = 0; i < (sInt)text.Length(); ++i ) 
		{
			sChar ch = text[i];
			SpriteChar sprite;
		
			if( !fontSprite().GetSprite( ch, sprite ) )
				continue;

			d3Float dx = sprite.GetW() / rdSize.x;
			d3Float dy = sprite.GetH() / rdSize.y;
			
			_fontRenderHeight = FMath::Max( _fontRenderHeight, dy );
		
			vpoints.Add( 
				d3Vector( x, y, 0.0f ),
				d3Vector( x + dx, y, 0.0f ),
				d3Vector( x, y - dy, 0.0f )
			);

			vpoints.Add( 
				d3Vector( x, y - dy, 0.0f ),
				d3Vector( x + dx, y, 0.0f ),
				d3Vector( x + dx, y - dy, 0.0f )
			);
		
			d3Float tx0 = sprite.GetX() / cx;
			d3Float ty0 = sprite.GetY() / cy;
			d3Float tx1 = tx0 + sprite.GetW() / cx;
			d3Float ty1 = ty0 + sprite.GetH() / cy;

			txpoints.Add( 
				d2Vector( tx0, ty0 ),
				d2Vector( tx1, ty0 ),
				d2Vector( tx0, ty1 )
			);

			txpoints.Add( 
				d2Vector( tx0, ty1 ),
				d2Vector( tx1, ty0 ),
				d2Vector( tx1, ty1 )
			);
			
			x += dx;
		}
		
		_fontRenderHeight *= 0.5f;
		
		_vb.ResourceCreate( 
			render().CreateVertexBuffer( _S(""), vpoints, txpoints )
		);
	}

	rstate.BeginRenderObject();
	
	rstate.SetTexture( TextureParameter::E_TEX1, &fontSprite().GetTexture() );
	rstate.SetEffect( _effect );
	rstate.SetParam_Color1( color );

	rstate.RenderPrimitive( _vb, PrimitiveType::E_TRIANGLE_LIST );
		
	rstate.EndRenderObject();

}

//-------------------------------------------------------------------		
SprireRenderString::~SprireRenderString()
{
}
	
}