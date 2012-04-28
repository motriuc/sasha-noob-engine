/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_w.h
//	Created                 : 23 6 2007   23:36
//	File path               : SLibF\system\include
//	Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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

#ifndef _S_SYSTEM_WCHAR_INC_
#define _S_SYSTEM_WCHAR_INC_

/**
 *	SWCHAR implementation
 */
class WChar
{
public:
	/**
	 *	New line string
	 */
	static const SWCHAR* NewLine;
	static const sInt NewLine_CharCount;

	/**
	 * Length of string
	 * @param pChars string
	 * @return Length of string
	 */
	static sInt Length( const SWCHAR* pChars );

	/**
	 * Copy strings
	 * @param pDestination destination
	 * @param pSource source
	 */
	static void Copy( SWCHAR* pDestination, const SWCHAR* pSource );
	
	/**
	 * Copy strings
	 * @param pDestination destination
	 * @param pSource source
	 * @count strings
	 */
	static void Copy( SWCHAR* pDestination, const SWCHAR* pSource, sInt count );

	/**
	 * Concatination strings
	 * @param pDestination destination
	 * @param pSource source
	 */
	static void Concat( SWCHAR* pDestination, const SWCHAR* pSource );

	/**
	 * Compare 2 strings
	 * @param pA string 1
	 * @param pB string 2
	 * @return > 0 if pA > pB, =0 if pA = pB, < 0 if pA < pB
	 */
	static sInt Compare( const SWCHAR* pA, const SWCHAR* pB );

	/**
	 * Compare No Case 2 strings
	 * @param pA string 1
	 * @param pB string 2
	 * @return > 0 if pA > pB, =0 if pA = pB, < 0 if pA < pB
	 */
	static sInt CompareNoCase( const SWCHAR* pA, const SWCHAR* pB );
	
	/**
	 * Convert integer string to Int
	 * @param pChars [in] string
	 * @return [out] int value if pChar is not an integer the result is 0
	 */
	static sInt ToInt( const SWCHAR* pChars );

	/**
	 * Convert int to char, the string must be big enough
	 * @param pChars [out] result string
	 * @param uInt [In] number to convert
	 */
	static void FromInt( SWCHAR* pChars, sInt uInt );

	/**
	 * Convert double to char, the string must be big enough
	 * @param pChars [out] result string
	 * @param number [In] number to convert
	 */
	static void FromDouble( SWCHAR* pChars, sDouble number );

	/**
	 * Convert float to char, the string must be big enough
	 * @param pChars [out] result string
	 * @param number [In] number to convert
	 */
	static void FromFloat( SWCHAR* pChars, sFloat number );

	/**
	 * Convert string to Float
	 * @param pChars [in] String
	 * @return [out] double value
	 */
	static sDouble ToDouble( const SWCHAR* pChars );

	/**
	 * Convert string to lower case
	 * @param pChars [in/out] String
	 * @param len [int] length
	 */
	static void LowerCase( SWCHAR* pChars, sInt len = -1 );

	/**
	 * Convert string to upper case
	 * @param pChars [in/out] String
	 * @param len [int] length
	 */
	static void UpperCase( SWCHAR* pChars, sInt len = -1 );

	/**
	 * Convert ch to lower case
	 * @param ch [in]
	 * @return [out] lowercase ch
	 */
	static SWCHAR LowerCase( SWCHAR ch );

	/**
	 * Convert ch to upper case
	 * @param ch [in]
	 * @return [out] upper ch
	 */
	static SWCHAR UpperCase( SWCHAR ch );

	/**
	 * Lower Test
	 * @param ch [in]
	 * @return [out]
	 */
	static sBool IsLower( SWCHAR ch );

	/**
	 * Upper Test
	 * @param ch [in]
	 * @return [out] 
	 */
	static sBool IsUpper( SWCHAR ch );

	/**
	 * Find char in the string
	 * @param pChars [in] string
	 * @param ch [in] char
	 * @return -1 if not
	 */
	static sInt Find( const SWCHAR* pChars, SWCHAR ch );

	/**
	 * Scan strings for characters in specified character sets
	 * @param pChars [in] string
	 * @param pChset [in] 
	 * @return -1 if not
	 */
	static sInt Find( const SWCHAR* pChars, SWCHAR* pChset );

	/**
	 * Find char in the string starting from end
	 * @param pChars [in] string
	 * @param ch [in] char
	 * @return -1 if not
	 */
	static sInt FindReverse( const SWCHAR* pChars, SWCHAR ch );

	/**
	 * Find first occurence of the any char from chSet in pChar
	 * @param pChars [in] string
	 * @param chSet [in] char set
	 * @param from [in] from to find
	 * @return position if not -1
	 */
	static sInt FindReverse( const SWCHAR* pChars, const SWCHAR* chSet, sUInt from );

	/**
	 * Find char in the string
	 * @param pChars [in] string
	 * @param ch [in] char set
	 * @return NULL if not 
	 */
	static SWCHAR* FindPtr( const SWCHAR* pChars, SWCHAR ch );

	/**
	 * Scan strings for characters in specified character sets
	 * @param pChars [in] string
	 * @param pChset [in] char set 
	 * @return NULL if not
	 */
	static SWCHAR* FindPtr( const SWCHAR* pChars, SWCHAR* pChset );

	/**
	 * Return true if char is digit
	 * @param ch [in] char
	 * @return true if is digit
	 */
	static sBool IsDigit( SWCHAR ch );

	/**
	 * Return true if char is space
	 * @param ch [in] char
	 * @return true if is space
	 */
	static sBool IsSpace( SWCHAR ch );

	/**
	 *	Convert char to wchar
	 *
	 * @param pDestination [out]
	 * @param destLen [in]
	 * @param pSource [in]
	 * @param srcLen [in]
	 */
	static sInt Convert( SBCHAR* pDestination, sInt destLen, const SWCHAR* pSource, sInt srcLen );
	
	/**
	 * Converts a byte UTF8 stream to a char
	 *
	 * @param bytes [in] bytes
	 * @param length [in] buffer length
	 * @param bytesReaded [out] return 0 if input is invalid return < 0 when more data are needed
	 * @return char 
	 */
	static SWCHAR From_UTF8( const SBYTE* bytes, sInt length, sInt& bytesReaded );

	/**
	 * convert char to UTF8 bytes
	 *
	 * @param ch [in] char to convert
	 * @param bytes [in] buffer to convert
	 * @param length [in] buffer length
	 * @return bytes written if > length 0 bytes were written, 0 means invalid input stream
	 */
	static sInt To_UTF8( SWCHAR ch, SBYTE* bytes, sInt length );
};

///////////////////////////////////////////////////////////////////

#ifdef _SPL_WIN32
	#include "s_system_chars_w_win32.inl"
#endif

#ifdef _SPL_MAC
	#include "s_system_chars_w_mac.inl"
#endif

#endif // _S_SYSTEM_WCHAR_INC_
