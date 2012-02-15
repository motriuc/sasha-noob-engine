/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_font_sprite.h
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

#ifndef _EAGL_FONT_UTILS_H_
#define _EAGL_FONT_UTILS_H_

#ifndef _EAGL_CONF_H_
#error eagl_conf.h must be included
#endif

/**
 * forward declarations
 */
struct UIFont;

/**
 * MeasureTextWithFont
 */
class MeasureTextWithFont : private class_nocopy
{
public:
	MeasureTextWithFont( const sString& fontName, const sInt fontSize );
	~MeasureTextWithFont();
	
	/**
	 *
	 */
	void Measure( const sString& text, sInt& w, sInt&h ) const;
	
	/**
	 *
	 */
	void Measure( sChar ch, sInt& w, sInt&h ) const { Measure( sString( &ch, 1 ), w, h ); }
	
	sInt GetFontDescend() const;
	sInt GetFontAscend() const;
	
	void EvaluateTextureSize( const sString& text, sInt& w, sInt&h ); 
private:
	sString _fontName;
	sInt	_fontSize;
	
	UIFont*	_uiFont;
};

#endif // _EAGL_FONT_UTILS_H_

