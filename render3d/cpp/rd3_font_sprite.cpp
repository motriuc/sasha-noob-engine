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
#include "rd3_xml_def.h"
#include "rd3_utils.h"

using namespace System::d3Math;
using namespace System::d2Math;

namespace Rd3
{

/////////////////////////////////////////////////////////////////////
// FontSprite
/////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------	
FontSprite::FontSprite( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName )
{
	_effect = GetOwner()->UseEffect( _S("system.font.fx.1") );
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
void FontSprite::SetTexture( const sString& name )
{
	SetTexture( GetOwner()->UseTexture( name ) );
}

//-------------------------------------------------------------------	
void FontSprite::LoadFromXml( const System::Xml::BaseDomNode& node, const Def& def ) throws_error
{
	SetTexture( node.GetAttributes()[ATTR_TEXTURE] ); 

	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const System::Xml::BaseDomNode& child = node[i];
		if( child.GetName() == _S("c") )
		{
			sString ch = child.GetAttributes()[_S("c")];
			sString val = child.GetAttributes()[_S("r")];
			if( ch.Length() == 1 )
			{
				sInt from = 0;
				sInt v[4];
				for( sInt i = 0; i < 4; i++ )
				{
					sString split;
					if( val.Split( _S(','), from, split ) )
						v[i] = split.ToInt();
					else
						v[i] = 0;
				}

				SpriteChar sprite( ch[0], v[0], v[1], v[2], v[3] );
				AddSprite( sprite );
			}
		}
	}
}

//-------------------------------------------------------------------	
RenderString* FontSprite::CreateRenderString()
{
	return new SprireRenderString( this );
}

//-------------------------------------------------------------------	
d3Float FontSprite::RenderText( RenderState& rstate, const sString& text, const d2Vector& pos, sRGBColor color )
{
	if( !_vb )
		_vb = GetOwner()->UseDynamicVertexBuffer( Rd3::VertexBufferStream::E_XYZ | Rd3::VertexBufferStream::E_TX1 );

	d2Vector targetSize = rstate.GetRenderTarger_SizeInPixels();
	d3Float fontRenderHeight = 0.0f;
	d2Vector npos;

	npos.x = Utils::RoundToPixelSize( pos.x, targetSize.x );
	npos.y = Utils::RoundToPixelSize( pos.y, targetSize.y );

	d3Float tx = static_cast<d3Float>( GetTexture().GetWidth() );
	d3Float ty = static_cast<d3Float>( GetTexture().GetHeight() ); 

	d3Float x1 = npos.x;
	d3Float y1 = npos.y;

	_vb().BeginAdd( text.Length() * 6 );

	for( sInt i = 0; i < (sInt)text.Length(); ++i ) 
	{
		sChar ch = text[i];
		SpriteChar sprite;
		
		if( !GetSprite( ch, sprite ) )
			continue;

		d3Float dx = sprite.Width() / targetSize.x;
		d3Float dy = sprite.Height() / targetSize.y;
			
		fontRenderHeight = FMath::Max( fontRenderHeight, dy );

		d3Float x2 = x1 + dx;
		d3Float y2 = y1 + dy;

		d3Float tx0 = sprite.X1() / tx;
		d3Float ty0 = sprite.Y1() / ty;
		d3Float tx1 = sprite.X2() / tx;
		d3Float ty1 = sprite.Y2() / ty;

		_vb().AddVertex( d3Vector( x1, y1, 0.0f ), d2Vector( tx0, ty0 ) );
		_vb().AddVertex( d3Vector( x1, y2, 0.0f ), d2Vector( tx0, ty1 ) );
		_vb().AddVertex( d3Vector( x2, y2, 0.0f ), d2Vector( tx1, ty1 ) );

		_vb().AddVertex( d3Vector( x1, y1, 0.0f ), d2Vector( tx0, ty0 ) );
		_vb().AddVertex( d3Vector( x2, y2, 0.0f ), d2Vector( tx1, ty1 ) );
		_vb().AddVertex( d3Vector( x2, y1, 0.0f ), d2Vector( tx1, ty0 ) );

		x1 += dx;
	}
		
	_vb().EndAdd();

	rstate.BeginRenderObject();
	
	rstate.SetTexture( TextureParameter::E_TEX1, _texture );
	rstate.SetEffect( _effect );
	rstate.SetParam_Color1( color );

	rstate.RenderPrimitive( _vb, PrimitiveType::E_TRIANGLE_LIST );
		
	rstate.EndRenderObject(); 
	return fontRenderHeight;
}

/////////////////////////////////////////////////////////////////////
// SprireRenderString
/////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------	
SprireRenderString::SprireRenderString( Font* font ):
	_BaseClass( font )
{
	_effect = render().UseEffect( _S("system.font.fx.1") );
}

//-------------------------------------------------------------------	
void SprireRenderString::RenderText( RenderState& rstate, const sString& text, const d2Vector& pos, sRGBColor color )
{
	d2Vector targetSize = rstate.GetRenderTarger_SizeInPixels();
	
	d2Vector npos;

	npos.x = Utils::RoundToPixelSize( pos.x, targetSize.x );
	npos.y = Utils::RoundToPixelSize( pos.y, targetSize.y );

	if( text != _text || _pos != npos )
	{
		_vb.ResourceFree();
				
		_text = text;
		_pos  = npos;

		d3Float tx = static_cast<d3Float>( fontSprite().GetTexture().GetWidth() );
		d3Float ty = static_cast<d3Float>( fontSprite().GetTexture().GetHeight() ); 

		d3Float x1 = _pos.x;
		d3Float y1 = _pos.y;

		VertexPList vpoints;
		VertexTxCoord txpoints;

		for( sInt i = 0; i < (sInt)text.Length(); ++i ) 
		{
			sChar ch = text[i];
			SpriteChar sprite;
		
			if( !fontSprite().GetSprite( ch, sprite ) )
				continue;

			d3Float dx = sprite.Width() / targetSize.x;
			d3Float dy = sprite.Height() / targetSize.y;
			
			_fontRenderHeight = FMath::Max( _fontRenderHeight, dy );

			d3Float x2 = x1 + dx;
			d3Float y2 = y1 + dy;

			vpoints.Add( 
				d3Vector( x1, y1, 0.0f ),
				d3Vector( x1, y2, 0.0f ),
				d3Vector( x2, y2, 0.0f )
			);

			vpoints.Add( 
				d3Vector( x1, y1, 0.0f ),
				d3Vector( x2, y2, 0.0f ),
				d3Vector( x2, y1, 0.0f )
			);

			d3Float tx0 = sprite.X1() / tx;
			d3Float ty0 = sprite.Y1() / ty;
			d3Float tx1 = sprite.X2() / tx;
			d3Float ty1 = sprite.Y2() / ty;
			
			txpoints.Add( 
				d2Vector( tx0, ty0 ),
				d2Vector( tx0, ty1 ),
				d2Vector( tx1, ty1 )
			);

			txpoints.Add( 
				d2Vector( tx0, ty0 ),
				d2Vector( tx1, ty1 ),
				d2Vector( tx1, ty0 )
			);

			x1 += dx;
		}
		
		_vb.ResourceCreate( render().CreateVertexBuffer( _S(""), vpoints, txpoints ) );
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
