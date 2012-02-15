/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_chars_b_win32.inl
//	Created                 : 11 1 2012   23:27
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
	return strcasecmp( pA, pB );
}

inline sInt BChar::ToInt( const SBCHAR* pChars )
{
	return strtol(pChars, (char **)NULL, 10);
}

inline void BChar::FromInt( SBCHAR* pChars, sInt uInt )
{
	sprintf( pChars, "%d", uInt ); 
}

inline void BChar::FromDouble( SBCHAR* pChars, sDouble number )
{
	sprintf( pChars, "%f", number ); 	
}

inline void BChar::FromFloat( SBCHAR* pChars, sFloat number )
{
	sprintf( pChars, "%f", number ); 	
}

inline sDouble BChar::ToDouble( const SBCHAR* pChars )
{
	return strtod( pChars, NULL );
}

inline void BChar::LowerCase( SBCHAR* pChars, sInt len )
{
	if( len < 0 )
	{
		while( *pChars )
		{
			*pChars = tolower( *pChars );
			++pChars;
		}
	}
	else
	{
		for( int i = 0; i < len; i++ )
		{
			pChars[i] = tolower( pChars[i] );
		}
	}
}

inline void BChar::UpperCase( SBCHAR* pChars, sInt len )
{
	if( len < 0 )
	{
		while( *pChars )
		{
			*pChars = toupper( *pChars );
			++pChars;
		}
	}
	else
	{
		for( int i = 0; i < len; i++ )
		{
			pChars[i] = toupper( pChars[i] );
		}
	}
}

inline SBCHAR BChar::LowerCase( SBCHAR ch )
{
	return tolower( ch );
}

inline SBCHAR BChar::UpperCase( SBCHAR ch )
{
	return toupper( ch );
}

inline sBool BChar::IsLower( SBCHAR ch )
{
	return islower( ch );	
}

inline sBool BChar::IsUpper( SBCHAR ch )
{
	return isupper( ch );
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
	__S_ASSERT( false );
	return 0;
}

inline _PLATFORM CFStringRef BChar::ToCfString( const SBCHAR* pString )
{
	return CFStringCreateWithCString( 
		kCFAllocatorDefault,
		pString,
		kCFStringEncodingUTF8
	);
}
	
inline _PLATFORM void BChar::FromCfString( CFStringRef src, SBCHAR* pDest, sInt destLen )
{
	CFStringGetCString( src, pDest, sizeof(SBCHAR)*destLen, kCFStringEncodingUTF8 ); 
}

