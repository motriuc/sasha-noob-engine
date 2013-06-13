/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_string_format.cpp
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
#define _use_sObject_
#include "s_system.h"

namespace System { namespace StringFormat {

//-------------------------------------------------------------------
StringItemWriter::StringItemWriter( const Obj::Object& obj ) :
	_nextItem( NULL ),
	_convert( NULL ),
	_estimateSize( NULL ),
	_string( obj.ToString() )
{
	_data = _string.c_str();
	_firstItem = this;
}

//-------------------------------------------------------------------
StringItemWriter::StringItemWriter( const Obj::Object* obj ) :
	_nextItem( NULL ),
	_convert( NULL ),
	_estimateSize( NULL ),
	_string( obj->ToString() )
{
	_data = _string.c_str();
	_firstItem = this;
}

//-------------------------------------------------------------------
sInt StringItemWriter::EstimateTotalSize() const
{
	sInt stringSize = 0;

	const StringItemWriter* item = _firstItem;
	while( item != NULL )
	{
		stringSize += item->EstimateSize();

		item = item->_nextItem;
	}

	return stringSize;
}

//-------------------------------------------------------------------
sInt StringItemWriter::ConvertTo( sChar* chars, sInt itemPos ) const
{
	const StringItemWriter* item = _firstItem;

	for( sInt i = 0; i < itemPos ; ++i )
	{
		if( item == NULL )
			break;
		item = item->_nextItem;
	}

	if( item == NULL )
		return 0;

	return item->ConvertTo( chars );
}

//-------------------------------------------------------------------
sString StringItemWriter::ToString() const
{
	__S_ASSERT( _firstItem != NULL );
	__S_ASSERT( _firstItem->_convert == NULL );

	sInt estimateStringSize = EstimateTotalSize();
	if( estimateStringSize <= 0 )
			return sString();

	sString string( estimateStringSize );

	const sChar* formatChars = (const sChar*)_firstItem->_data;
	sChar* dstChars = string.GetCharBuffer();
	sInt dstSize = 0;

	while( *formatChars )
	{
		if( *formatChars == _S('{') )
		{
			formatChars++;
			if( !*formatChars  )
			{
				// Incomplete format string Ex: 'User Name {'
				__S_ASSERT( sFalse );
				break;
			}

			if( *formatChars != _S('{') )
			{
				sInt id = 0;
				while( *formatChars && *formatChars >= _S('0') && *formatChars <= _S('9') )
				{
					id = id * 10 + *formatChars - _S('0');
					++formatChars;
				}

				if( id != 0 )
				{
					sInt len = ConvertTo( dstChars, id );
					dstChars+= len;
					dstSize += len;
				}
				else
				{
					// Missing element Id Ex: 'User Name {}'
					__S_ASSERT( sFalse );
				}

				while( *formatChars && *formatChars != _S('}') )
					++formatChars;

				if( !*formatChars )
				{
					// Incomplete format string Ex: 'User Name {12'
					__S_ASSERT( sFalse );
					break;
				}

				++formatChars;

				continue;
			}
		}
		
		*dstChars = *formatChars;
		++dstChars;
		++dstSize;

		++formatChars;
	}

	string.UpdateLength( dstSize );

	return string;
}


} }
