/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_b.h
//	Created                 : 23 6 2007   23:20
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

#ifndef _S_SYSTEM_BCHAR_INC_
#define _S_SYSTEM_BCHAR_INC_

/**
 *	SBCHAR implementation
 */
class BChar
{
public:
	/**
	 *	New line string
	 */
	static const SBCHAR* NewLine;
	
	/**
	 * Length of string
	 * @param pChars string
	 * @return Length of string
	 */
	static sInt Length( const SBCHAR* pChars );

	/**
	 * Copy strings
	 * @param pDestination destination
	 * @param pSource source
	 */
	static void Copy( SBCHAR* pDestination, const SBCHAR* pSource );
	
	/**
	 * Copy strings
	 * @param pDestination destination
	 * @param pSource source
	 * @count strings
	 */
	static void Copy( SBCHAR* pDestination, const SBCHAR* pSource, sInt count );

	/**
	 * Concatination strings
	 * @param pDestination destination
	 * @param pSource source
	 */
	static void Concat( SBCHAR* pDestination, const SBCHAR* pSource );

	/**
	 * Compare 2 strings
	 * @param pA string 1
	 * @param pB string 2
	 * @return > 0 if pA > pB, =0 if pA = pB, < 0 if pA < pB
	 */
	static sInt Compare( const SBCHAR* pA, const SBCHAR* pB );

	/**
	 * Compare No Case 2 strings
	 * @param pA string 1
	 * @param pB string 2
	 * @return > 0 if pA > pB, =0 if pA = pB, < 0 if pA < pB
	 */
	static sInt CompareNoCase( const SBCHAR* pA, const SBCHAR* pB );
	
	/**
	 * Convert integer string to Int
	 * @param pChars [in] string
	 * @return [out] int value if pChar is not an integer the result is 0
	 */
	static sInt ToInt( const SBCHAR* pChars );

	/**
	 * Convert int to char, the string must be big enough
	 * @param pChars [out] result string
	 * @param uInt [In] number to convert
	 */
	static void FromInt( SBCHAR* pChars, sInt uInt );

	/**
	 * Convert double to char, the string must be big enough
	 * @param pChars [out] result string
	 * @param number [In] number to convert
	 */
	static void FromDouble( SBCHAR* pChars, sDouble number );

	/**
	 * Convert float to char, the string must be big enough
	 * @param pChars [out] result string
	 * @param number [In] number to convert
	 */
	static void FromFloat( SBCHAR* pChars, sFloat number );
	
	/**
	 * Convert string to Float
	 * @param pChars [in] String
	 * @return [out] double value
	 */
	static sDouble ToDouble( const SBCHAR* pChars );

	/**
	 * Convert string to lower case
	 * @param pChars [in/out] String
	 * @param len [int] length
	 */
	static void LowerCase( SBCHAR* pChars, sInt len = -1 );

	/**
	 * Convert string to upper case
	 * @param pChars [in/out] String
	 * @param len [int] length
	 */
	static void UpperCase( SBCHAR* pChars, sInt len = -1 );

	/**
	 * Convert ch to lower case
	 * @param ch [in]
	 * @return [out] lowercase ch
	 */
	static SBCHAR LowerCase( SBCHAR ch );

	/**
	 * Convert ch to upper case
	 * @param ch [in]
	 * @return [out] upper ch
	 */
	static SBCHAR UpperCase( SBCHAR ch );

	/**
	 * Lower Test
	 * @param ch [in]
	 * @return [out]
	 */
	static sBool IsLower( SBCHAR ch );

	/**
	 * Upper Test
	 * @param ch [in]
	 * @return [out] 
	 */
	static sBool IsUpper( SBCHAR ch );

	/**
	 * Find char in the string
	 * @param pChars [in] string
	 * @param ch [in] char
	 * @return -1 if not
	 */
	static sInt Find( const SBCHAR* pChars, SBCHAR ch );

	/**
	 * Find char in the string starting from end
	 * @param pChars [in] string
	 * @param ch [in] char
	 * @return -1 if not
	 */
	static sInt FindReverse( const SBCHAR* pChars, SBCHAR ch );

	/**
	 * Scan strings for characters in specified character sets
	 * @param pChars [in] string
	 * @param pChset [in] 
	 * @return -1 if not
	 */
	static sInt Find( const SBCHAR* pChars, SBCHAR* pChset );

	/**
	 * Find first occurence of the any char from chSet in pChar
	 * @param pChars [in] string
	 * @param chSet [in] char set
	 * @param from [in] from to find
	 * @return position if not -1
	 */
	static sInt FindReverse( const SBCHAR* pChars, const SBCHAR* chSet, sUInt from );

	/**
	 * Find char in the string
	 * @param pChars [in] string
	 * @param ch [in] char set
	 * @return NULL if not 
	 */
	static SBCHAR* FindPtr( const SBCHAR* pChars, SBCHAR ch );

	/**
	 * Scan strings for characters in specified character sets
	 * @param pChars [in] string
	 * @param pChset [in] char set 
	 * @return NULL if not
	 */
	static SBCHAR* FindPtr( const SBCHAR* pChars, SBCHAR* pChset );

	/**
	 * Return true if char is digit
	 * @param ch [in] char
	 * @return true if is digit
	 */
	static sBool IsDigit( SBCHAR ch );

	/**
	 * Return true if char is space
	 * @param ch [in] char
	 * @return true if is space
	 */
	static sBool IsSpace( SBCHAR ch );

	/**
	 *	Convert char to wchar
	 *
	 * @param pDestination [out]
	 * @param destLen [in]
	 * @param pSource [in]
	 * @param srcLen [in]
	 */
	static sInt Convert( SWCHAR* pDestination, sInt destLen, const SBCHAR* pSource, sInt srcLen );

	/**
	 * Convert from UTF8 bytes to chars
	 *
	 * @param pChars [out] the converted chars
	 * @param charBufferCount [in] the char buffer count
	 * @param pBuffer [in] 
	 * @param bufferLength [in]
	 * @param charAdded [out]
	 */
	static const SBYTE* ConvertFrom_UTF8( SBCHAR* pChars, sInt charBufferCount, const SBYTE* pBuffer, sInt bufferLength, sInt& charAdded );
	
#ifdef _SPL_MAC
	/**
	 * Converts a string to CFStringRef
	 */
	_PLATFORM static CFStringRef ToCfString( const SBCHAR* pString );
	
	/**
	 * gets a string from CFStringRef
	 */
	_PLATFORM static void FromCfString( CFStringRef src, SBCHAR* pDest, sInt destLen );
	
#endif	
};

#ifdef _SPL_WIN32
	#include "s_system_chars_b_win32.inl"
#endif

#ifdef _SPL_MAC
	#include "s_system_chars_b_mac.inl"
#endif

#endif // _S_SYSTEM_BCHAR_INC_
