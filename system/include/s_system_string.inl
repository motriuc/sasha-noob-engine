/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_string.inl
//  Created                 : 24 6 2007   0:39
//  File path               : C:\Sasha\C++\SLibF\system\Include
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

namespace Types
{

inline sString::sString() :
	_data( __str::AssignEmptyString() )
{
}

inline sString::~sString()
{
	FreeString();
}

inline sString::sString( const sChar* pChars ) :
	_data( __str::CreateString( pChars ) )
{
}	

inline sString::sString( const sCharO* pChars ) :
	_data( __str::CreateString( pChars ) )
{
}

inline sString::sString( const sCharO* pChars, sUInt nCount ):
	_data( __str::CreateString( pChars, nCount ) )
{
}

inline sString::sString( const sChar* pChars, sUInt nCount ):
	_data( __str::CreateString( pChars, nCount ) )
{
}

inline sString::sString( sInt len ) :
   _data( __str::AllocNewString( len ) )
{
	_data->data()[len] = 0;
}

#ifdef _SPL_MAC
inline sString::sString( CFStringRef src )
{
	sInt len = CFStringGetLength( src );
	_data = __str::AllocNewString( len );
	
	Chars::FromCfString( src, _data->data(), _data->nAllocLength );
	_data->nDataLength = len;
}
#endif	


inline sString::sString( const sString& src )
{
	if( this != &src )
	{
		Mt::Inc( src._data->nRefs );
		_data = src._data;
	}
}

inline void sString::operator = ( const sString& src )
{
	if( &src != this )
	{
		FreeString();
		Mt::Inc( src._data->nRefs );
		_data = src._data;
	}
}

inline void sString::operator = ( const sChar ch )
{
	*this = sString( &ch, 1 );
}

inline sString::operator const sChar*() const
{
	__S_ASSERT( _data != NULL );
	return _data->data();
}

inline const sChar* sString::c_str() const
{
	__S_ASSERT( _data != NULL );
	return _data->data();
}


inline void sString::operator+= ( const sString& str )
{
	sUInt strLength = str.Length();
	if( strLength > 0 )
	{
		GrowReAlloc( Length() + strLength );
		Memory::Copy( _data->data() + Length(), str._data->data(), sizeof(sChar) * ( strLength + 1 ) );
		_data->nDataLength += strLength;
	}
}

inline void sString::operator+= ( const sChar* str )
{
	__S_ASSERT( str != NULL );

	sUInt strLength = Chars::Length( str );
	if( strLength > 0 )
	{
		GrowReAlloc( Length() + strLength );
		Memory::Copy( _data->data() + Length(), str, sizeof(sChar) * ( strLength + 1 ) );
		_data->nDataLength += strLength;
	}
}

inline void sString::operator += ( sChar ch )
{
	GrowReAlloc( Length() + 1 );
	sChar* p = _data->data() + Length();
	*p = ch;
	p++;
	*p = 0;
	_data->nDataLength ++;
}


inline sUInt sString::Length() const
{
	return _data->nDataLength;
}

inline sString sString::operator + ( const sChar* str ) const
{
	__S_ASSERT( str != NULL );

	sString rez( *this );
	rez += str;
	return rez;
}

inline sString sString::operator + ( const sString& str ) const
{
	sString rez( *this );
	rez += str;
	return rez;
}

inline sString operator + ( const sChar* pChars, const sString& str )
{
	sString ch( pChars );
	ch += str;
	return ch;
}

inline sString sString::operator + ( sChar ch ) const
{
	sString rez( *this );
	rez += ch;
	return rez;
}

inline _PLATFORM sChar* sString::GetCharBuffer() const
{
	__S_ASSERT( _data != NULL );

	return _data->data();
}

inline sString sString::IntToString( sInt nr )
{
	sString nrStr( 12 );
	
	Chars::FromInt( nrStr.GetCharBuffer(), nr );
	nrStr.UpdateLength();

	return nrStr;
}

inline sString sString::DoubleToString( sDouble nr )
{
	sString nrStr( 32 );

	Chars::FromDouble( nrStr.GetCharBuffer(), nr );
	nrStr.UpdateLength();

	return nrStr;
}

inline sString sString::FloatToString( sFloat nr )
{
	sString nrStr( 32 );

	Chars::FromFloat( nrStr.GetCharBuffer(), nr );
	nrStr.UpdateLength();

	return nrStr;
}

inline void sString::UpdateLength( sUInt length )
{
	if( _data && _data->nRefs == 1 )
	{
		if( length == 0 )
			_data->nDataLength = Chars::Length( _data->data() );
		else
		{
			__S_ASSERT( _data->nAllocLength >= length );

			_data->nDataLength = length;
			_data->data()[length] = 0;
		}
	}
}

inline sBool sString::operator > ( const sString& str ) const
{
	__S_ASSERT( _data != NULL );

	return Chars::Compare( _data->data(), str ) > 0;
}

inline sBool sString::operator > ( const sChar* str ) const
{
	__S_ASSERT( _data != NULL );
	__S_ASSERT( str != NULL );

	return Chars::Compare( _data->data(), str ) > 0;
}

inline sBool sString::operator < ( const sString& str ) const
{
	__S_ASSERT( _data != NULL );

	return Chars::Compare( _data->data(), str ) < 0;
}

inline sBool sString::operator < ( const sChar* str ) const
{
	__S_ASSERT( _data != NULL );
	__S_ASSERT( str != NULL );

  return Chars::Compare( _data->data(), str ) < 0;
}

inline sBool sString::operator >= ( const sString& str ) const
{
	__S_ASSERT( _data != NULL );

	return Chars::Compare( _data->data(), str ) >= 0;
}

inline sBool sString::operator >= ( const sChar* str ) const
{
	__S_ASSERT( _data != NULL );
	__S_ASSERT( str != NULL );

	return Chars::Compare( _data->data(), str ) >= 0;
}

inline sBool sString::operator <= ( const sString& str ) const
{
	__S_ASSERT( _data != NULL );

	return Chars::Compare( _data->data(), str ) <= 0;
}

inline sBool sString::operator <= ( const sChar* str ) const
{
	__S_ASSERT( _data != NULL );
	__S_ASSERT( str != NULL );

	return Chars::Compare( _data->data(), str ) <= 0;
}

inline sBool sString::operator != ( const sChar* str ) const
{
	__S_ASSERT( _data != NULL );
	__S_ASSERT( str != NULL );

	return Chars::Compare( _data->data(), str ) != 0;
}

inline sBool sString::operator != ( const sString& str ) const
{
	__S_ASSERT( _data != NULL );

	return Chars::Compare( _data->data(), str._data->data() ) != 0;
}

inline sBool sString::operator == ( const sChar* str ) const
{
	__S_ASSERT( _data != NULL );
	__S_ASSERT( str != NULL );

	return Chars::Compare( _data->data(), str ) == 0;
}

inline sBool sString::operator == ( const sString& str ) const
{
	__S_ASSERT( _data != NULL );

	return Chars::Compare( _data->data(), str._data->data() ) == 0;
}

inline sChar sString::GetChar( sInt i ) const
{
	__S_ASSERT( _data != NULL );

	__S_ASSERT( i >= 0 && i < (sInt)Length() );
	return _data->data()[i];
}

inline void sString::Add( const sChar* pChars, sInt count )
{
	__S_ASSERT( pChars != NULL );
	__S_ASSERT( _data != NULL );
	__S_ASSERT( count > 0 );

	GrowReAlloc( Length() + count );
	Memory::Copy( _data->data() + Length(), pChars, sizeof(sChar) * ( count ) );

	*(_data->data() + Length() + count) = 0;

	count = Chars::Length( _data->data() + Length() );
  
	_data->nDataLength += count;
}

inline sInt sString::ToInt() const
{
	__S_ASSERT( _data != NULL );

	return Chars::ToInt( _data->data() );
}

inline sDouble sString::ToDouble() const
{
	__S_ASSERT( _data != NULL );

	return Chars::ToDouble( _data->data() );
}

inline sFloat sString::ToFloat() const
{
	__S_ASSERT( _data != NULL );

	return (sFloat)Chars::ToDouble( _data->data() );
}

inline sString sString::SubString( sInt from ) const
{
	return SubString( from, Length() );
}

inline sString sString::SubString( sInt from, sInt length ) const
{
	__S_ASSERT( _data != NULL );
	__S_ASSERT( from >= 0 );

	sInt strLen = (sInt)Length();

	if( from >= strLen || length <= 0 )
		return sString();

	strLen -= from;
	length = ( strLen < length ) ? strLen : length;

	return sString( _data->data() + from, length );

}

inline sBool sString::BeginsWith( const sString& prefix ) const
{
	sInt oLength = Length();
	sInt pLength = prefix.Length();

	if( pLength > oLength )
		return sFalse;

	return Memory::Compare( 
		_data->data(),
		prefix._data->data(),
		sizeof(sChar) * pLength ) == 0;
}

inline sBool sString::EndsWith( const sString& sufix ) const
{
	sInt oLength = Length();
	sInt sLength = sufix.Length();

	if( sLength > oLength )
		return sFalse;

	return Memory::Compare( 
		_data->data() + oLength - sLength,
		sufix._data->data(),
		sizeof(sChar) * sLength ) == 0;
}

inline sInt sString::Find( const sChar ch ) const
{
	return Chars::Find( c_str(), ch );
}

inline sInt sString::Find( sInt from, const sChar ch ) const
{
	__S_ASSERT( from >= 0 );
	
	if( from >= (sInt)Length() )
		return -1;
	
	sInt ret = Chars::Find( c_str() + from, ch );
	if( ret >= 0 )
		ret += from;
		
	return ret;
}

inline sBool sString::Split( sChar ch, sInt& from, sString& v ) const
{
	if( from >= (sInt)Length() )
		return sFalse;
		
	for( sInt i = from; i < (sInt)Length(); ++i )
	{
		if( GetChar( i ) == ch )
		{
			v = SubString( from, i - from );
			from = i+1;
			return sTrue;
		}
	}
	
	v = SubString( from );
	from = Length();
	
	return sTrue;
}
	
inline sInt sString::FindReverse( const sChar ch ) const
{
	return Chars::FindReverse( c_str(), ch );
}

inline sInt sString::FindReverse( const sChar* chSet, sInt from ) const
{
	__S_ASSERT( chSet != NULL );
	__S_ASSERT( _data != NULL );

	return Chars::FindReverse( _data->data(), chSet, from );
}

inline sInt sString::FindReverse( const sChar* chSet ) const
{
	__S_ASSERT( chSet != NULL );
	__S_ASSERT( _data != NULL );

	return Chars::FindReverse( _data->data(), chSet, Length() - 1 );
}


#ifdef _SPL_MAC

inline CFStringRef sString::ToCfString() const
{
	return Chars::ToCfString( c_str() );
}

#endif

/************************************************************************/
/* protected                                                            */
/************************************************************************/

inline void sString::FreeString()
{
	if( Mt::Dec( _data->nRefs ) <= 0 )
		__str::FreeString( _data );
}

inline void sString::BeforeChange( sUInt n )
{
	__S_ASSERT( _data != NULL );

	if( n <= 0 )
	{
		FreeString();
		_data = __str::AssignEmptyString();
	}
	else if( _data->nRefs != 1 || _data->nAllocLength < n )
	{
		FreeString();
		_data = __str::AllocNewString( n );
	}
}

inline void sString::GrowReAlloc( sUInt n )
{
	__S_ASSERT( n >= Length() );
	__S_ASSERT( _data != NULL );

	if( _data->nRefs == 1 && _data->nAllocLength >= n ) return;

	struct __str*  newStr = __str::AllocNewString( n );

	if( _data )
	{
		Memory::Copy( newStr->data(), _data->data(), sizeof(sChar) * ( Length() + 1 ) );
		newStr->nDataLength = Length();
	}

	FreeString();
	_data = newStr;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

inline sChar* sString::__str::data()
{
	return ( sChar* )( &ch );
}

inline struct sString::__str* sString::__str::GetEmptyString()
{
	static struct __str emptyString = { 1, 0, 0, 0 };
	return &emptyString;
}

inline struct sString::__str* sString::__str::AllocNewString( sUInt n )
{
	const sUInt _SLIB_MIN_STEP_STRING_ALLOC = 2;

	n = ( ( n / _SLIB_MIN_STEP_STRING_ALLOC ) + 1 ) * _SLIB_MIN_STEP_STRING_ALLOC;

	struct __str* str = ( struct __str* ) new SBYTE
		[sizeof( struct __str ) + sizeof( sChar ) * n ];

	*str->data() = 0;
	str->nAllocLength = n;
	str->nDataLength = 0;
	str->nRefs = 1;
	return str;
}

inline struct sString::__str* sString::__str::AssignEmptyString()
{
	Mt::Inc( GetEmptyString()->nRefs );
	return GetEmptyString();
}

inline void sString::__str::FreeString( struct __str*& pStr )
{
	__S_ASSERT( pStr != NULL );
	__S_ASSERT( pStr != __str::GetEmptyString() );

	delete[] ( SBYTE* )pStr;
	pStr = NULL;
};

inline struct sString::__str* sString::__str::CreateString( const sChar* pChars, sUInt n )
{
	__S_ASSERT( pChars != NULL );

	if( n <= 0 )
		return __str::AssignEmptyString();

	struct __str* pStr = __str::AllocNewString( n );

	Memory::Copy( pStr->data(), pChars, sizeof(sChar) * n );
	*( pStr->data() + n ) = 0;

	pStr->nDataLength = n;

	return pStr;
}

inline struct sString::__str* sString::__str::CreateString( const sChar* pChars )
{
	__S_ASSERT( pChars != NULL );

	return CreateString( pChars, Chars::Length( pChars ) );
}

inline struct sString::__str* sString::__str::CreateString( const sCharO* pChar, sUInt n )
{
	__S_ASSERT( pChar != NULL );
	if( n <= 0 )
		return __str::AssignEmptyString();

	struct __str* pStr = __str::AllocNewString( n );
	
	n = CharsO::Convert( pStr->data(), n, pChar, n );

	pStr->nDataLength = n;
	*( pStr->data() + n ) = 0;
	return pStr;
}

inline struct sString::__str* sString::__str::CreateString( const sCharO* pChar )
{
	__S_ASSERT( pChar != NULL );

	return CreateString( pChar, CharsO::Length( pChar ) );
}


}
