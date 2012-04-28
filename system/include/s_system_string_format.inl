/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_string_format.inl
//  Created                 : 28 4 2012   4:28
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

//-------------------------------------------------------------------
inline StringItemWriter::operator sString() const
{
	return ToString();
}

//-------------------------------------------------------------------
inline StringItemWriter::StringItemWriter( const sChar* chars ) :
	_nextItem( NULL ),
	_data( chars ),
	_convert( NULL ),
	_estimateSize( NULL )
{
	_firstItem = this;
}

//-------------------------------------------------------------------
inline StringItemWriter::StringItemWriter( const sString& chars ) :
	_nextItem( NULL ),
	_data( chars.c_str() ),
	_convert( NULL ),
	_estimateSize( NULL )
{
	_firstItem = this;
}

//-------------------------------------------------------------------
inline const StringItemWriter& StringItemWriter::operator % ( const StringItemWriter& next ) const
{
	__S_ASSERT( _nextItem == NULL );

	_nextItem = &next;
	next._firstItem = _firstItem;
	return next;
}

//-------------------------------------------------------------------
inline sInt StringItemWriter::EstimateSize() const
{
	if( _estimateSize == NULL )
		return Chars::Length( (const sChar*) _data );

	return (*_estimateSize)( _data );
}

//-------------------------------------------------------------------
inline sInt StringItemWriter::ConvertTo( sChar* chars ) const
{
	sInt len = 0;

	if( _convert == NULL )
	{
		Chars::Copy( chars, (const sChar*)_data );
		len = Chars::Length( (const sChar*)_data );
	}
	else
	{
		len = (*_convert)( _data, chars );
	}

	return len;
}

