/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_w_win32.inl
//	Created                 : 23 6 2007   23:38
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

inline sInt WChar::Length( const SWCHAR* pChars )
{
	return (sInt)wcslen( pChars );
}

inline void WChar::Copy( SWCHAR* pDestination, const SWCHAR* pSource )
{
	wcscpy( pDestination, pSource );
}

inline void WChar::Copy( SWCHAR* pDestination, const SWCHAR* pSource, sInt count )
{
	wcsncpy( pDestination, pSource, count );
	pDestination[count-1] = 0;
}

inline void WChar::Concat( SWCHAR* pDestination, const SWCHAR* pSource )
{
	wcscat( pDestination, pSource );
}

inline sInt WChar::Compare( const SWCHAR* pA, const SWCHAR* pB )
{
	return wcscmp( pA, pB );
}

inline sInt WChar::CompareNoCase( const SWCHAR* pA, const SWCHAR* pB )
{
	return wcsicmp( pA, pB );
}

inline sInt WChar::ToInt( const SWCHAR* pChars )
{
	return _wtoi( pChars );
}

inline void WChar::FromInt( SWCHAR* pChars, sInt uInt )
{
	_itow( uInt, pChars, 10 );
}

inline void WChar::LowerCase( SWCHAR* pChars, sInt len )
{
	if( len < 0 )
		len = Length( pChars );
	if( len > 0 )
		CharLowerBuffW( pChars, len );
}

inline void WChar::UpperCase( SWCHAR* pChars, sInt len )
{
	if( len < 0 )
		len = Length( pChars );
	if( len > 0 )
		CharUpperBuffW( pChars, len );
}

inline SWCHAR WChar::LowerCase( SWCHAR ch )
{
	LowerCase( &ch, 1 );
	return ch;
}

inline SWCHAR WChar::UpperCase( SWCHAR ch )
{
	UpperCase( &ch, 1 );
	return ch;
}

inline sBool WChar::IsLower( SWCHAR ch )
{
	return IsCharLowerW( ch );	
}

inline sBool WChar::IsUpper( SWCHAR ch )
{
	return IsCharUpperW( ch );
}

inline sInt WChar::Find( const SWCHAR* pChars, SWCHAR ch )
{
	const SWCHAR* p = wcschr( pChars, ch );
	return p == NULL ? -1 : (sInt)(p - pChars);
}

inline SWCHAR* WChar::FindPtr( const SWCHAR* pChars, SWCHAR ch )
{
	return (SWCHAR*)wcschr( pChars, ch );
}

inline SWCHAR* WChar::FindPtr( const SWCHAR* pChars, SWCHAR* pChset )
{
	return (SWCHAR*)wcspbrk( pChars, pChset );
}

inline sInt WChar::Find( const SWCHAR* pChars, SWCHAR* pChset )
{
	const SWCHAR* p = wcspbrk( pChars, pChset );
	return p == NULL ? -1 : (sInt)(p - pChars);
}

inline sBool WChar::IsDigit( SWCHAR ch )
{
	return iswdigit( ch );
}

inline sBool WChar::IsSpace( SWCHAR ch )
{
	return iswspace( ch );
}

inline sInt WChar::Convert( SBCHAR* pDestination, sInt destLen, const SWCHAR* pSource, sInt srcLen )
{
	int ret = WideCharToMultiByte(
		CP_ACP,
		0,
		pSource,
		srcLen,
		pDestination,
		destLen,
		NULL,
		NULL
	);

	return (sInt)ret;
}

inline sInt WChar::FindReverse( const SWCHAR* pChars, SWCHAR ch )
{
	const SWCHAR* p = wcsrchr( pChars, ch );
	return p == NULL ? -1 : (sInt)(p - pChars);	
}
