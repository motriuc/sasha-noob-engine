/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_font_sprite.cpp
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
#include "eagl_conf.h"
#include "eagl_font_sprite.h"
#include "eagl_font_utils.h"
#include "eagl_render.h"
#include "rd3_resobj.h"
#include "rd3_texture.h"
#include "rd3_effect.h"

#include <CoreGraphics/CGBitmapContext.h>

//-----------------------------------------------------------------------------
static const sChar* stdCharSet = 
{
	_S(" ")
	_S(	"0123456789")
	_S(	";:,.?!@#$%^&*")
	_S( "/\\|'\"")
	_S( "()<>{}[]")
	_S( "abcdefghijklmnopqrstuvwxyz")
	_S( "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
};

//-----------------------------------------------------------------------------
EAGLFontSprite::EAGLFontSprite( Rd3::Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName )
{	
}

//-----------------------------------------------------------------------------
Rd3::RenderString* EAGLFontSprite::CreateRenderString()
{
	return new EAGLSprireRenderString( this );
}

//-----------------------------------------------------------------------------
void EAGLFontSprite::DrawTheSprites( CGContextRef context, MeasureTextWithFont& measure, sInt textureW, sInt textureH )
{
	sInt x = 0;
	sInt y = textureH - measure.GetFontAscend();
	sInt ry = 0;
	
	const sChar* chars = stdCharSet;
	
	while( *chars )
	{		
		sInt tw = 0;
		sInt th = 0;
		
		measure.Measure( *chars, tw, th );
		
		if( x + tw > textureW )
		{
			y -= th;
			ry += th;
			x = 0;
		}
		
		CGContextShowTextAtPoint( context, x, y, chars, 1 );
		
		AddSprite( Rd3::SpriteChar( *chars, x, ry, tw, th ) );
		
		x+= tw;
		++chars;
	}
}

//-----------------------------------------------------------------------------
void EAGLFontSprite::CreateFont( const sString& fontName, sInt fontSize ) throws_error
{	
	
	MeasureTextWithFont fontMeasureUtils( fontName, fontSize );
	
	sInt textureW = 0;
	sInt textureH = 0;
	
	fontMeasureUtils.EvaluateTextureSize( stdCharSet, textureW, textureH );
	
	if( textureH == 0 || textureW == 0 ) 
	{
		error_throw_arg( Errors::StringError )
			_S("Unable to create the font: ") + fontName
		);
	}
	
	char *imageData = new char[textureW * textureH * 4];

	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	
    CGContextRef context = CGBitmapContextCreate(
		imageData, 
		textureW, textureH, 
		8, 4 * textureW,
		colorSpace,
		kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big
	);
	
    CGColorSpaceRelease( colorSpace );
	
    CGContextClearRect( context, CGRectMake( 0, 0, textureW, textureH ) );
	
	CGContextSelectFont( context, fontName.c_str(), fontSize, kCGEncodingMacRoman );
	
    CGContextSetTextDrawingMode( context, kCGTextFillStroke );
    CGContextSetRGBFillColor( context, 1, 1, 1, 1 );
    CGContextSetRGBStrokeColor( context, 1, 1, 1, 1);
	
	DrawTheSprites( context, fontMeasureUtils, textureW, textureH );
	
	GLuint texture;
	
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D,GL_GENERATE_MIPMAP, GL_FALSE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	{
		char* lumData = new char[textureW * textureH];
		for( sInt i = 0; i < textureW * textureH; ++i )
			lumData[i] = imageData[4*i];
		
		glTexImage2D( GL_TEXTURE_2D, 0, GL_LUMINANCE, textureW, textureH, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, lumData );
		
		delete[] lumData;
	}
	
    CGContextRelease( context );
	
	delete[] imageData;
	
	_texture.ResourceCreate( 
		((EAGLRender*)GetOwner())->EAGLCreateTexture( 
			_S("system.font.tx.") + fontName + _S(".") + sString::IntToString(fontSize),
			texture,
			textureW,
			textureH,
			Rd3::TextureType::E_ALPHA,
			Rd3::TextureParams()
		)
	);
}

//-----------------------------------------------------------------------------
EAGLSprireRenderString::EAGLSprireRenderString( Rd3::Font* font ):
	_BaseClass( font )
{
}
