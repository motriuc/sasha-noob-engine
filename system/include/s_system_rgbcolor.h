/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_rgbcolor.h
//  Created                 : 27 1 2011   20:16
//  File path               : SLibF\system\include
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
#ifndef _SYSTEM_RGBCOLOR_INC_
#define _SYSTEM_RGBCOLOR_INC_

/**
 * RGB color utils
 */
namespace RGBColor
{

using namespace System::Types;	

/**
 * From RGB
 */
sRGBColor FromRGB( SBYTE r, SBYTE g, SBYTE b );
sRGBColor FromRGBA( SBYTE r, SBYTE g, SBYTE b, SBYTE a );
sRGBColor FromFloatRGBA( sFloat r, sFloat g, sFloat b, sFloat a );
sRGBColor FromFloatRGBA( sFloat r, sFloat g, sFloat b );

/**
 * to RGB
 */
SBYTE GetByteR( sRGBColor c );
SBYTE GetByteG( sRGBColor c );
SBYTE GetByteB( sRGBColor c );
SBYTE GetByteA( sRGBColor c );

/**
 * to RGB
 */
sFloat GetFloatR( sRGBColor c );
sFloat GetFloatG( sRGBColor c );
sFloat GetFloatB( sRGBColor c );
sFloat GetFloatA( sRGBColor c );

/**
 * Some basic color
 */
const sRGBColor White	= FromRGB( 255, 255, 255 );
const sRGBColor Black	= FromRGB( 0, 0, 0 );
const sRGBColor Green	= FromRGB( 0, 255, 0 );
const sRGBColor Blue	= FromRGB( 0, 0, 255 );
const sRGBColor Red		= FromRGB( 255, 0, 0 );

#include "s_system_rgbcolor.inl"

}

#endif // _SYSTEM_RGBCOLOR_INC_