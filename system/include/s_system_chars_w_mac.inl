/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_w_mac.inl
//	Created                 : 11 1 2011   23:38
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


inline sInt WChar::ToInt( const SWCHAR* pChars )
{
	return wcstol( pChars, NULL, 10 );
}

inline sDouble WChar::ToDouble( const SWCHAR* pChars )
{
	return wcstod( pChars, NULL);
}

inline void WChar::FromInt( SWCHAR* pChars, sInt uInt )
{
	swprintf( pChars, 32, L"%d", uInt );
}

inline void WChar::FromDouble( SWCHAR* pChars, sDouble number )
{
	swprintf( pChars, 64, L"%f", number ); 	
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
