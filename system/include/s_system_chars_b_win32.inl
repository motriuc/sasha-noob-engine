/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_b_win32.inl
//	Created                 : 23 6 2007   23:27
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


inline sInt BChar::Length( const SBCHAR* pChars )
{
	return (sInt)strlen( pChars );
}

inline void BChar::Copy( SBCHAR* pDestination, const SBCHAR* pSource )
{
	strcpy( pDestination, pSource );
}

inline void BChar::Copy( SBCHAR* pDestination, const SBCHAR* pSource, sInt count )
{
	strncpy( pDestination, pSource, count );

	// Set Null char
	pDestination[count-1] = 0;
}

inline void BChar::Concat( SBCHAR* pDestination, const SBCHAR* pSource )
{
	strcat( pDestination, pSource );
}

inline sInt BChar::Compare( const SBCHAR* pA, const SBCHAR* pB )
{
	return strcmp( pA, pB );
}

inline sInt BChar::CompareNoCase( const SBCHAR* pA, const SBCHAR* pB )
{
	return stricmp( pA, pB );
}

inline sInt BChar::ToInt( const SBCHAR* pChars )
{
	return atoi( pChars );
}

inline void BChar::FromInt( SBCHAR* pChars, sInt uInt )
{
	itoa( uInt, pChars, 10 );
}

inline void BChar::FromDouble( SBCHAR* pChars, sDouble number )
{
	_gcvt( number, 12, pChars );
}

inline sDouble BChar::ToDouble( const SBCHAR* pChars )
{
	return atof( pChars );
}

inline void BChar::LowerCase( SBCHAR* pChars, sInt len )
{
	if( len < 0 )
		len = Length( pChars );
	if( len > 0 )
		CharLowerBuffA( pChars, len );
}

inline void BChar::UpperCase( SBCHAR* pChars, sInt len )
{
	if( len < 0 )
		len = Length( pChars );
	if( len > 0 )
		CharUpperBuffA( pChars, len );
}

inline SBCHAR BChar::LowerCase( SBCHAR ch )
{
	LowerCase( &ch, 1 );
	return ch;
}

inline SBCHAR BChar::UpperCase( SBCHAR ch )
{
	UpperCase( &ch, 1 );
	return ch;
}

inline sBool BChar::IsLower( SBCHAR ch )
{
	return IsCharLowerA( ch );	
}

inline sBool BChar::IsUpper( SBCHAR ch )
{
	return IsCharUpperA( ch );
}

inline sInt BChar::Find( const SBCHAR* pChars, SBCHAR ch )
{
	const SBCHAR* p = strchr( pChars, ch );
	return p == NULL ? -1 : (sInt)(p - pChars);
}

inline SBCHAR* BChar::FindPtr( const SBCHAR* pChars, SBCHAR ch )
{
	return (SBCHAR*)strchr( pChars, ch );
}

inline SBCHAR* BChar::FindPtr( const SBCHAR* pChars, SBCHAR* pChset )
{
	return (SBCHAR*)strpbrk( pChars, pChset );
}

inline sInt BChar::Find( const SBCHAR* pChars, SBCHAR* pChset )
{
	const SBCHAR* p = strpbrk( pChars, pChset );
	return p == NULL ? -1 : (sInt)(p - pChars);
}

inline sBool BChar::IsDigit( SBCHAR ch )
{
	return isdigit( ch );
}

inline sBool BChar::IsSpace( SBCHAR ch )
{
	return isspace( ch );
}

inline sInt BChar::FindReverse( const SBCHAR* pChars, SBCHAR ch )
{
	const SBCHAR* p = strrchr( pChars, ch );
	return p == NULL ? -1 : (sInt)(p - pChars);	
}

inline sInt BChar::Convert( SWCHAR* pDestination, sInt destLen, const SBCHAR* pSource, sInt srcLen )
{
	int ret = MultiByteToWideChar(
		CP_ACP,
		0,
		pSource,
		srcLen * sizeof(SBCHAR),
		pDestination,
		destLen * sizeof(SWCHAR)
	);

	return (sInt)ret;
}