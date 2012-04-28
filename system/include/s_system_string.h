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
	 *	
	 */
	sString( const sChar* pChars );

	/**
	 *
	 */
	sString( const sCharO* pChars );

	/**
	 *
	 */
	sString( const sCharO* pChars, sUInt nCount );

	/**
	 *	
	 */
	sString( const sChar* pChars, sUInt nCount );

	/**
	 *	
	 */
	sString( const sString& src );
	
#ifdef _SPL_MAC
	sString( CFStringRef src );
#endif	

	/**
	 *	Create a string with len memory length
	 */
	explicit sString( sInt len );

	/**
	 *	
	 */
	void operator = ( const sString& src );

	/**
	 *	
	 */
	void operator = ( const sChar ch );
	
	/**
	 *	
	 */
	operator const sChar*() const;

	/**
	 *
	 */
	const sChar* c_str() const;

	/**
	 *	
	 */
	void operator += ( const sChar* str );

	/**
	 *	
	 */
	void operator += ( const sString& str );

	/**
	 *	
	 */
	void operator += ( sChar ch );

	/**
	 *	string length
	 */
	sUInt Length() const;

	/**
	 *	
	 */
	sString operator + ( const sChar* str ) const;

	/**
	 *	
	 */
	sString operator + ( const sString& str ) const;

	/**
	 *	
	 */
	sString operator + ( sChar ch ) const;

	/**
	 *	Convert Int to String
	 */
	static sString IntToString( sInt nr );

	/**
	 *	Convert Double to string
	 */
	static sString DoubleToString( sDouble nr );
	
	/**
	 * Converst float to string
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
	 *	Return string char
	 */
	sChar GetChar( sInt i ) const;

	/**
	 *
	 */
	void Add( const sChar* pChars, sInt count );

	/**
	 *	
	 */
	sInt ToInt() const;

	/**
	 *
	 */
	sFloat ToFloat() const;

	/**
	 *	
	 */
	sDouble ToDouble() const;

	/**
	 *	
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
	 * 
	 */
	sInt Find( const sChar ch ) const;
	
	/**
	 * 
	 */
	sInt Find( sInt from, const sChar ch ) const;
	
	/**
	 *
	 */
	sInt FindReverse( const sChar ch ) const;

	/**
	 *
	 */
	sInt FindReverse( const sChar* chSet, sInt from ) const;
	
	/**
	 *
	 */
	sInt FindReverse( const sChar* chSet ) const;
	
	/**
	 *
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
		static struct __str* AssignEmptyString();
		static struct __str* CreateString( const sChar* pChars );
		static struct __str* CreateString( const sChar* pChars, sUInt n );
		static struct __str* CreateString( const sCharO* pChar, sUInt n );
		static struct __str* CreateString( const sCharO* pChar );

	}* _data;
};


#endif // _SYSTEM_STRING_INC_
