/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_b_utf8.cpp
//  Created                 : 28 4 2012   9:22
//  File path               : SLibF\system\Cpp
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
#include "s_system.h"

namespace System { namespace CharsTrait {


//------------------------------------------------------------------
// UTF8
//------------------------------------------------------------------
const sInt _system_utf_8_charMap[256] = 
{
	/* 00 */	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
	/* 10 */	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
	/* 20 */	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 
	/* 30 */	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 
	/* 40 */	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 
	/* 50 */	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 
	/* 60 */	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 
	/* 70 */	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 
	/* 80 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
	/* 90 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
	/* a0 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
	/* b0 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
	/* c0 */	  -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2, 
	/* d0 */	  -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2, 
	/* e0 */	  -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3, 
	/* f0 */	  -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -5,   -5,   -5,   -5,   -6,   -6,   -1,   -1, 
};

//------------------------------------------------------------------
inline sBool isLegal( const SBYTE *bytes, sInt length )
{	
	if( 0 == bytes || 0 == length )
		return sFalse;

	SBYTE a;
	const SBYTE* srcptr = bytes + length;

	switch( length )
	{
	default:
		return sFalse;
		// Everything else falls through when true.
	case 4:
		if( (a = (*--srcptr)) < 0x80 || a > 0xBF ) 
			return sFalse;
	case 3: 
		if( (a = (*--srcptr)) < 0x80 || a > 0xBF )
			return sFalse;
	case 2:
		if( (a = (*--srcptr)) > 0xBF )
			return sFalse;

		switch( *bytes ) 
		{
		case 0xE0:
			if( a < 0xA0 ) return sFalse; 
			break;
		case 0xED:
			if( a > 0x9F ) return sFalse; 
			break;
		case 0xF0:
			if( a < 0x90 ) return sFalse; 
			break;
		case 0xF4:
			if( a > 0x8F ) return sFalse; 
			break;
		default:
			if( a < 0x80 ) return sFalse;
		}
	case 1:
		if( *bytes >= 0x80 && *bytes < 0xC2 ) return sFalse;
    }

	return *bytes <= 0xF4;
}

//------------------------------------------------------------------
// return -1 - invalid UTF8 stream, -2 - need more data
inline sInt _From_UTF8( const SBYTE* bytes, sInt length, sInt& bytesReaded )
{
	sInt n = _system_utf_8_charMap[*bytes];
	sInt uc;

	bytesReaded = 0;
	
	switch( n )
	{
	case -6:
	case -5:
	case -1:
		return -1;
	case -4: 
	case -3: 
	case -2:
		if( length < -n )
			return -2;

		if( !isLegal( bytes, -n ) ) return -1;

		uc = *bytes & ((0x07 << (n + 4)) | 0x03);
		break;
	default:
		bytesReaded = 1;
		return n;
	}

	bytesReaded = -n;

	while (n++ < -1) 
	{	
		uc <<= 6;
		uc |= (*++bytes & 0x3F);
	}

	return uc;
}

//------------------------------------------------------------------
inline sInt _To_UTF8( sInt ch, SBYTE* bytes, sInt length )
{
	if( ch <= 0x7F )
	{
		if( bytes && length >= 1 )
			*bytes = (SBYTE) ch;
		return 1;
	}
	else if( ch <= 0x7FF )
	{
		if( bytes && length >= 2 )
		{
			*bytes++ = (SBYTE) (((ch >> 6) & 0x1F) | 0xC0);
			*bytes   = (SBYTE) ((ch & 0x3F) | 0x80);
		}
		return 2;
	}
	else if( ch <= 0xFFFF )
	{
		if( bytes && length >= 3 )
		{
			*bytes++ = (SBYTE) (((ch >> 12) & 0x0F) | 0xE0);
			*bytes++ = (SBYTE) (((ch >> 6) & 0x3F) | 0x80);
			*bytes   = (SBYTE) ((ch & 0x3F) | 0x80);
		}
		return 3;
	}
	else if( ch <= 0x10FFFF )
	{
		if( bytes && length >= 4 )
		{
			*bytes++ = (SBYTE) (((ch >> 18) & 0x07) | 0xF0);
			*bytes++ = (SBYTE) (((ch >> 12) & 0x3F) | 0x80);
			*bytes++ = (SBYTE) (((ch >> 6) & 0x3F) | 0x80);
			*bytes   = (SBYTE) ((ch & 0x3F) | 0x80);
		}
		return 4;
	}
	else 
		return 0;
}

//------------------------------------------------------------------
SBCHAR BChar::From_UTF8( const SBYTE* bytes, sInt length, sInt& bytesReaded )
{
	sInt ch = _From_UTF8( bytes, length, bytesReaded );

	if( ch == -1 )
	{
		bytesReaded = 0;
		return 0;
	}

	if( ch == -2 )
	{
		bytesReaded = -1;
		return 0;
	}

	if( ch <= 0x7f )
	{
		return ch;
	}

	return '?';
}

//------------------------------------------------------------------
sInt BChar::To_UTF8( SBCHAR ch, SBYTE* bytes, sInt length )
{
	if( ch > 0x7f )
		ch = '?';

	return _To_UTF8( ch, bytes, length );
}

//------------------------------------------------------------------
sInt WChar::To_UTF8( SWCHAR ch, SBYTE* bytes, sInt length )
{
	if( ch > 0x7f )
		ch = '?';

	return _To_UTF8( ch, bytes, length );
}

//------------------------------------------------------------------
SWCHAR WChar::From_UTF8( const SBYTE* bytes, sInt length, sInt& bytesReaded )
{
	sInt ch = _From_UTF8( bytes, length, bytesReaded );

	if( ch == -1 )
	{
		bytesReaded = 0;
		return 0;
	}

	if( ch == -2 )
	{
		bytesReaded = -1;
		return 0;
	}

	return ch;
}


} }