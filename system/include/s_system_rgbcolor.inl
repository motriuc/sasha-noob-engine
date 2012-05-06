/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_rgbcolor.inl
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

inline sRGBColor FromRGB( SBYTE r, SBYTE g, SBYTE b )
{
	return FromRGBA( r, g, b, 255 );
}

inline sRGBColor FromRGBA( SBYTE r, SBYTE g, SBYTE b, SBYTE a )
{
	return
		(
			(sRGBColor)(
				((SBYTE)(b) | 
				((SWORD)((SBYTE)(g)) << 8)) |
				(((SDWORD)(SBYTE)(r)) << 16) |
				(((SDWORD)(SBYTE)(a)) << 24)
			)
	);
}

inline sRGBColor FromFloatRGBA( sFloat r, sFloat g, sFloat b, sFloat a )
{
	return FromRGBA( (SBYTE)(r*255.0f), (SBYTE)(g*255.0f), (SBYTE)(b*255.0f), (SBYTE)(a*255.0f) );
}

inline sRGBColor FromFloatRGBA( sFloat r, sFloat g, sFloat b )
{
	return FromRGBA( (SBYTE)(r*255.0f), (SBYTE)(g*255.0f), (SBYTE)(b*255.0f), 255 );
}

inline SBYTE GetByteR( sRGBColor c )
{
	return (SBYTE)( (c >> 16) & 0xFF );
}

inline SBYTE GetByteG( sRGBColor c )
{
	return (SBYTE)( (c >> 8) & 0xFF );
}

inline SBYTE GetByteB( sRGBColor c )
{
	return (SBYTE)( (c) & 0xFF );
}

inline SBYTE GetByteA( sRGBColor c )
{
	return (SBYTE)( (c >> 24) & 0xFF );
}

inline sFloat GetFloatR( sRGBColor c )
{
	return (sFloat)GetByteR(c) / 255.0f;
}

inline sFloat GetFloatG( sRGBColor c )
{
	return (sFloat)GetByteG(c) / 255.0f;
}

inline sFloat GetFloatB( sRGBColor c )
{
	return (sFloat)GetByteB(c) / 255.0f;
}

inline sFloat GetFloatA( sRGBColor c )
{
	return (sFloat)GetByteA(c) / 255.0f;
}
