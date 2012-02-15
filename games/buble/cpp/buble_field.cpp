/////////////////////////////////////////////////////////////////////
//  File Name               : buble_field.cpp
//	Created                 : 30 1 2012   0:05
//	File path               : games/buble/cpp
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

#include "bubleafx.h"
#include "buble_field.h"
#include "ed3_obj_factory.h"
#include "ed3_rdata.h"

#include "rd3_texture.h"
#include "rd3_vertexbuffer.h"
#include "rd3_effect.h"
#include "rd3_render.h"
#include "rd3_rstate.h"

#define MAX_FIELD_SIZE 128

AUTO_REGISTER_D3OBJECT_FACTORY( _S("game.buble.field") , BubleField )

using namespace Streams;

//-------------------------------------------------------------------
BubleField::BubleField():
	_tileWidth( 0 ),
	_tileHeight( 0 ),
	_fieldWidth( 0 ),
	_fieldHeight( 0 )
{
	
}
//-------------------------------------------------------------------
void BubleField::LoadFromXML( const Xml::BaseDomNode& element, Ed3::LoadDataParams& loadParams ) throws_error
{
	_BaseClass::LoadFromXML( element, loadParams );
	
	sString textureName = element.GetAttributes()[_S("tileset")];
	sString effectName = element.GetAttributes()[_S("effect")];
	
	_tileWidth = element.GetAttributes()[_S("tileset.width")].ToInt();
	_tileHeight = element.GetAttributes()[_S("tileset.height")].ToInt();
	
	_tileCountW = element.GetAttributes()[_S("tileset.width.count")].ToInt();
	_tileCountH = element.GetAttributes()[_S("tileset.height.count")].ToInt();
	
	_tileTexture = loadParams.render.UseTexture( textureName );
	_effect = loadParams.render.UseEffect( effectName );
	
	LoadFieldFromFile( element.GetAttributes()[_S("field")], loadParams );
}

//-------------------------------------------------------------------
void BubleField::LoadFieldFromFile( const sString& path, Ed3::LoadDataParams& loadParams ) throws_error
{
	ptr_unique<const IInputStream> pStream( loadParams.archive.Open( path ) ); 
	
	TextReader textReader( &pStream() );
	
	_fieldWidth = 0;
	_fieldHeight = 0;
	
	textReader.Read( _fieldWidth );
	textReader.Read( _fieldHeight );
	
	if( _fieldWidth <= 0 || _fieldWidth > MAX_FIELD_SIZE || _fieldHeight <= 0 || _fieldHeight > MAX_FIELD_SIZE )
	{
		error_throw_arg( Errors::StringError )
			_S("Invalid field sizez")
		);
	}
	
	for( sInt i = 0; i < _fieldWidth * _fieldHeight; ++i )
	{
		sInt v;
		textReader.Read( v );
		_fieldTiles.Add( v );
	}
}

//-------------------------------------------------------------------
void BubleField::Render( const Ed3::d3RenderData& renderData )
{
	Rd3::RenderState& render = renderData.rstate();
	
	render.BeginRenderObject();
	
	render.SetEffect( _effect );
	render.SetTexture( Rd3::TextureParameter::E_TEX1, _tileTexture );
	render.RenderPrimitive( _vb, Rd3::PrimitiveType::E_TRIANGLE_LIST );
	
	render.EndRenderObject();
}

//-------------------------------------------------------------------
void BubleField::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );
	
	Rd3::VertexPList pointList;
	Rd3::VertexTxCoord txCoord;
			
	sFloat dw = 1.2*_tileWidth * 1.0f/320.0f;
	sFloat dh = 1.2*_tileHeight * 1.0f/480.0f;
	
	sInt tId = 0;
	
	for( sInt ih = 0; ih < _fieldHeight; ++ih )
	{
		for( sInt iw = 0; iw < _fieldHeight; ++iw )
		{
			sFloat x1 = iw * dw;
			sFloat y1 = ih * dh;
			
			sFloat x2 = x1 + dw;
			sFloat y2 = y1 + dh;
						
			pointList.Add( d3Vector( x1, y1, 0.0f ) );
			pointList.Add( d3Vector( x2, y2, 0.0f ) );
			pointList.Add( d3Vector( x1, y2, 0.0f ) );
			
			pointList.Add( d3Vector( x1, y1, 0.0f ) );
			pointList.Add( d3Vector( x2, y1, 0.0f ) );
			pointList.Add( d3Vector( x2, y2, 0.0f ) );

			sInt vTile = _fieldTiles[tId];
			sInt ix = vTile % _tileCountW;
			sInt iy = vTile / _tileCountW;
			
			sFloat tx1 = (sFloat)( _tileWidth * ix ) / (sFloat)_tileTexture().GetWidth();
			sFloat ty1 = (sFloat)( _tileHeight * iy ) / (sFloat)_tileTexture().GetHeight(); 
			sFloat tx2 = (sFloat)( _tileWidth * ix + _tileWidth ) / (sFloat)_tileTexture().GetWidth();
			sFloat ty2 = (sFloat)( _tileHeight * iy + _tileHeight ) / (sFloat)_tileTexture().GetHeight(); 
			
			txCoord.Add( d2Vector( tx1, ty1 ) );
			txCoord.Add( d2Vector( tx2, ty2 ) );
			txCoord.Add( d2Vector( tx1, ty2 ) );
			
			txCoord.Add( d2Vector( tx1, ty1 ) );
			txCoord.Add( d2Vector( tx2, ty1 ) );
			txCoord.Add( d2Vector( tx2, ty2 ) );
			
			tId++;
		}
	}
	
	_vb.ResourceCreate( render.CreateVertexBuffer( _S(""), pointList, txCoord ) );
}
