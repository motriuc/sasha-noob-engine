/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_string.h
//  Created                 : 24 6 2007   0:38
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
#ifndef _SYSTEM_STRING_INC_
#define _SYSTEM_STRING_INC_

/**
 *	String class
 */
class sString
{
public:
	/**
	 *	default constructor
	 */
	sString();

	/**
	 *	destructor
	 */
	~sString();

	/**
	 *	creates a string from an char array
	 */
	sString( const sChar* pChars );

	/**
	 * creates a string from an char array
	 */
	sString( const sCharO* pChars );

	/**
	 * creates a string from an char array
	 */
	sString( const sCharO* pChars, sUInt nCount );

	/**
	 * creates a string from ans char array
	 */
	sString( const sChar* pChars, sUInt nCount );

	/**
	 * creates a string from another string
	 */
	sString( const sString& src );

#ifdef _SLIB_CPP11
	/**
	 * Move constructor
	 */
	sString( sString&& src );
#endif
	
#ifdef _SPL_MAC
	sString( CFStringRef src );
#endif	

	/**
	 *	Create a string of length len, the string content is undefined
	 */
	explicit sString( sInt len );

	/**
	 * Assign operator from a sString
	 */
	void operator = ( const sString& src );

	/**
	 * Assign operator from a sChar
	 */
	void operator = ( const sChar ch );
	
	/**
	 * returns a const array of the string content 
	 */
	operator const sChar*() const;

	/**
	 * returns a const array of the string content
	 */
	const sChar* c_str() const;

	/**
	 * adds an array of chars to the string
	 */
	void operator += ( const sChar* str );

	/**
	 * adds a string to a string
	 */
	void operator += ( const sString& str );

	/**
	 * adds a char to a string
	 */
	void operator += ( sChar ch );

	/**
	 *	returns string length
	 */
	sUInt Length() const;

	/**
	 * adds String and  a char array
	 */
	sString operator + ( const sChar* str ) const;

	/**
	 * adds a String and String
	 */
	sString operator + ( const sString& str ) const;

	/**
	 * adds a String and a char
	 */
	sString operator + ( sChar ch ) const;

	/**
	 *	converts Int to String using default converter
	 */
	static sString IntToString( sInt nr );

	/**
	 *	convert Double to string using default converter
	 */
	static sString DoubleToString( sDouble nr );
	
	/**
	 * converst float to string
	 */
	static sString FloatToString( sFloat nr );

	sBool operator >  ( const sString& str ) const;
	sBool operator >  ( const sChar* str ) const;

	sBool operator <  ( const sString& str ) const;
	sBool operator <  ( const sChar* str ) const;

	sBool operator >= ( const sString& str ) const;
	sBool operator >= ( const sChar* str ) const;

	sBool operator <= ( const sString& str ) const;
	sBool operator <= ( const sChar* str ) const;


	sBool operator != ( const sString& str ) const;
	sBool operator != ( const sChar* str ) const;

	sBool operator == ( const sString& str ) const;
	sBool operator == ( const sChar* str ) const;

	/**
	 * return string char at i position
	 */
	sChar GetChar( sInt i ) const;

	/**
	 * adds a char array to the string
	 */
	void Add( const sChar* pChars, sInt count );

	/**
	 * converts string to an integer
	 */
	sInt ToInt() const;

	/**
	 * converts a string to an float number
	 */
	sFloat ToFloat() const;

	/**
	 * converts a string to an double number
	 */
	sDouble ToDouble() const;

	/**
	 * returns a substring of the string
	 */
	sString SubString( sInt from, sInt length ) const;
	sString SubString( sInt from ) const;
	
	/**
	 * returns true if the string begins with prefix
	 */
	sBool BeginsWith( const sString& prefix ) const;
	
	/**
	 * returns true if string ends with sifix
	 */
	sBool EndsWith( const sString& sufix ) const;
	
	/**
	 * finds the position of the char in the string
	 */
	sInt Find( const sChar ch ) const;
	
	/**
	 * finds the position of the char in the string
	 */
	sInt Find( sInt from, const sChar ch ) const;
	
	/**
	 * finds the position of the char in the string from end
	 */
	sInt FindReverse( const sChar ch ) const;

	/**
	 * finds the position of the chars in the string from end
	 */
	sInt FindReverse( const sChar* chSet, sInt from ) const;
	
	/**
	 *
	 */
	sInt FindReverse( const sChar* chSet ) const;
	
	/**
	 * splits the string in parts by char
	 * Ex:
	 *  "sasha heloo"
	 *   1. Split( ' ', from, v ) => from = 6, v = "sasha", false
	 *   2. Split( ' ', from, v ) => from = 11, v = "heloo", false
	 *   3. Split( ' ', from, v ) => from = 12, v ="", true
	 */
	sBool Split( sChar ch, sInt& from, sString& v ) const;

	/**
	 *	Update string length after content modifications
	 *	works only for 1 string reference
	 */
	_PLATFORM void UpdateLength( sUInt length = 0 );

	/**
	 *	return char buffer 
	 *	Use UpdateLength after using of it
	 *	Must have only 1 reference
	 */
	_PLATFORM sChar* GetCharBuffer() const;
	
#ifdef _SPL_MAC
	/**
	 * Converts a string to CFStringRef
	 */
	_PLATFORM CFStringRef ToCfString() const;
#endif

protected:
	void FreeString();
	void BeforeChange( sUInt n );
	void GrowReAlloc( sUInt n );
	void Assign( const sString& src );	

private:
	struct __str
	{
		volatile sUInt nRefs;
		sUInt nDataLength;
		sUInt nAllocLength;
		sChar ch;

		sChar* data();

		static void FreeString( struct __str*& pStr );
		static struct __str* AllocNewString( sUInt n );
		static struct __str* GetEmptyString();
		static struct __str* CreateString( const sChar* pChars );
		static struct __str* CreateString( const sChar* pChars, sUInt n );
		static struct __str* CreateString( const sCharO* pChar, sUInt n );
		static struct __str* CreateString( const sCharO* pChar );

	}* _data;
};

#endif // _SYSTEM_STRING_INC_
