/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_types_base.h
//  Created                 : 14 6 2007   1:01
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
#ifndef _S_SYSTEM_BASETYPES_INC_
#define _S_SYSTEM_BASETYPES_INC_

///////////////////////////////////////////////
// WIN 32 platform
#if defined( _SPL_WIN32 ) || defined ( _SPL_MAC )

	//////////////////////////////////////////////
	// Fixed size types

	// non signed types
	typedef unsigned char		SBYTE;
	typedef unsigned short		SWORD;
	typedef unsigned int		SDWORD;

#ifdef __GNUC__
	typedef unsigned long long	SDDWORD;
	typedef long long			SINT64;
	typedef unsigned long long	SUINT64;
#endif

#ifdef _MSC_VER
	typedef unsigned __int64	SDDWORD;
	typedef __int64				SINT64;
	typedef unsigned __int64	SUINT64;
#endif

	// Signed types
	typedef	char				SINT8;
	typedef short				SINT16;
	typedef int					SINT32;

	typedef unsigned char		SUINT8;
	typedef unsigned short		SUINT16;
	typedef unsigned int		SUINT32;

		// Len fixed char
	typedef char				SBCHAR;
	typedef wchar_t				SWCHAR;

	// float len fixed
	typedef float				sFloat;
	typedef double				sDouble;

	///////////////////////////////////
	// Not Fixed size types
	typedef SINT16				sShort;
	typedef SUINT16				sUShort;
	typedef SINT32				sInt;
	typedef SDWORD				sUInt;
	typedef	sInt				sBool;
	typedef sInt				sLong;
	typedef sUInt				sULong;
	typedef SINT64				sHuge;
	typedef SUINT64				sUHuge;
#endif

///////////////////////////////////////
// Char macros
#ifdef _SLIB_WCHAR
	typedef SWCHAR				sChar;
	typedef SBCHAR				sCharO;
	#define _S(X)				L ## X
#else
	typedef SBCHAR				sChar;
	typedef SWCHAR				sCharO;
	#define _S(X)				X
#endif

/**
 *	Bool True value
 */
const sBool sTrue = 1;

/**
 *	Bool False value
 */
const sBool sFalse = 0;

/**
 * Rgb Color used in the library
 */
typedef SDWORD	sRGBColor;	

/**
 *	Seek type
 */
namespace SeekType
{
	/**
	 *	Seek type
	 */
	enum SeekType
	{
		/**
		 *	Seek from begin
		 */
		eFromBegin		= 0,

		/**
		 *	Seek from current position
		 */
		eFromCurrent	,

		/**
		 *	Seek from end
		 */
		eFromEnd		,

		_PLATFORM COUNT
	};
}

/**
 * Char encoding type
 */
namespace Encoding
{
	enum Encoding
	{
		UTF_8		= 0,
		UTF_16,

		_PLATFORM COUNT
	};

	inline sInt MaxCharSize( Encoding encoding )
	{
		__S_ASSERT( encoding >= 0 );
		__S_ASSERT( encoding < COUNT );

		static sInt size[COUNT] = 
		{
			4,		// UTF_8
			4		// UTF_16
		};

		return size[encoding];
	}
}

#endif // _S_SYSTEM_BASETYPES_INC_
