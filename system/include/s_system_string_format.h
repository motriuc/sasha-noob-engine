/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_string_format.h
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

namespace StringFormat
{

using namespace System::Types;
using namespace System;

/**
 * StringItemWriter
 * Internal class must not be used directly
 */
class StringItemWriter
{
private:
	typedef Types::sInt( *ConvertCall ) ( const void*, sChar* );
	typedef sInt( *EstimateSizeCall )( const void* );
public:
	StringItemWriter( const Obj::Object& obj );
	StringItemWriter( const Obj::Object* obj );
	StringItemWriter( const sChar* chars );
	StringItemWriter( const sString& chars );

	template< typename Type >
	StringItemWriter( const Type& v ) :
		_nextItem( NULL ),
		_data( &v )
	{
		_convert = reinterpret_cast<ConvertCall>( &StringFormater<Type>::Convert );
		_estimateSize = reinterpret_cast<EstimateSizeCall>( &StringFormater<Type>::EstimateSize );
		_firstItem = this;
	}

	const StringItemWriter& operator % ( const StringItemWriter& next ) const;

	sString ToString() const;
	operator sString() const;

private:
	sInt ConvertTo( sChar* chars, sInt itemPos ) const;
	sInt ConvertTo( sChar* chars ) const;
	sInt EstimateSize() const;
	sInt EstimateTotalSize() const;
private:
	mutable const StringItemWriter*		_firstItem;
	mutable const StringItemWriter*		_nextItem;
	const void*							_data;

	ConvertCall							_convert;
	EstimateSizeCall					_estimateSize;
	sString								_string;
};

#include "s_system_string_format.inl"

}

inline StringFormat::StringItemWriter Format( const Types::sChar* chars )
{
	return StringFormat::StringItemWriter( chars );
}


