/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_font_sprite.mm
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

#define _INC_OBJ_C_

#include "rd3afx.h"
#include "eagl_conf.h"
#include "eagl_font_utils.h"

//-----------------------------------------------------------------------------------------
NSString* ToNSString( const sString& str )
{
	NSString* nsFontName = [[NSString alloc]
#ifdef _SLIB_WCHAR
		#error not implemented
#else	
		initWithUTF8String: str.c_str()];
#endif
	
	return nsFontName;
}

//-----------------------------------------------------------------------------------------
void MeasureTextWithFont::MeasureTextWithFont::Measure( const sString& text, sInt& w, sInt&h ) const
{
	NSString* nsText = ToNSString( text );
	
	CGSize size = [nsText sizeWithFont: _uiFont];
	
	[nsText release];
	
	w = FMath::Round( size.width );
	h = FMath::Round( size.height );
}

//-----------------------------------------------------------------------------------------
sInt MeasureTextWithFont::GetFontDescend() const
{
	return FMath::Round( _uiFont.descender );
}

//-----------------------------------------------------------------------------------------
sInt MeasureTextWithFont::GetFontAscend() const
{
	return FMath::Round( _uiFont.ascender );	
}

//-----------------------------------------------------------------------------------------
MeasureTextWithFont::MeasureTextWithFont( const sString& fontName, const sInt fontSize ) :
	_fontName( fontName ),
	_fontSize( fontSize ),
	_uiFont( NULL )
{
	NSString* nsFontName = ToNSString( fontName );
	
	_uiFont = [UIFont fontWithName: nsFontName size:(CGFloat) fontSize];
	
	[nsFontName release];
	
	if (_uiFont == NULL) {
		error_throw_arg( Errors::StringError )
			_S("Can't open font:") + fontName
		);
	}
}

//-----------------------------------------------------------------------------------------
MeasureTextWithFont::~MeasureTextWithFont()
{
	[_uiFont release];
}

//-----------------------------------------------------------------------------------------
void MeasureTextWithFont::EvaluateTextureSize( const sString& text, sInt& w, sInt&h )
{
	sInt mw;
	sInt mh;
	
	Measure( text, mw, mh );
		
	sInt area = mw*mh;
	
	sInt newArea = FMath::UpperPowOf2Number( area );
	sInt arePower = FMath::Log2( newArea );
	w = FMath::PowOf2( arePower / 2 );
	
	if( w > 2048 )
		w = 2048;
	
	h = newArea / w;
		
	if( newArea - area < h * mh / 2  )
		h *= 2;

	if( h > 2048 )
		h = 2048;
	
}

