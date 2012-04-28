/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_wstr.cpp
//  Created                 : 25 4 2012   17:39
//  File path               : SLibF\system\Cpp
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
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

#define _use_Streams_
#include "s_system.h"

namespace System { namespace Streams {

//-----------------------------------------------------------------
TextWriter::TextWriter( IOutputStream* pStream, Encoding::Encoding encoding, sInt bufferSize ) :
	_stream( pStream ),
	_encoding( encoding ),
	_bufferSize( bufferSize ),
	_bufferCount( 0 )
{
	__S_ASSERT( bufferSize >= 64 );
	__S_ASSERT( _stream != NULL );

	_bytesBuffer = new SBYTE[_bufferSize ];

	switch( _encoding )
	{
	case Encoding::UTF_8:
		_print = &TextWriter::PrintUTF8;
		break;
	default:
		__S_ASSERT( sFalse );
	}
}

//-----------------------------------------------------------------
TextWriter::~TextWriter()
{
	Flush();
	delete[] _bytesBuffer;
}

//-----------------------------------------------------------------
void TextWriter::Flush()
{
	if( _bufferCount > 0 )
	{
		_stream->Write( _bytesBuffer, _bufferCount );
		_bufferCount = 0;
	}
}

//-----------------------------------------------------------------
void TextWriter::PrintUTF8( const sChar* ch, sInt length )
{
	for( sInt i = 0; i < length; ++i )
	{
		for(;;)
		{
			sInt freeCount = _bufferSize - _bufferCount;
			sInt writtenBytes = Chars::To_UTF8( *ch, _bytesBuffer + _bufferCount, freeCount );

			if( writtenBytes == 0 )
			{
				error_throw_arg( Errors::StringError )
					_S("Invalid input data stream")
				);
			}

			if( writtenBytes > freeCount )
			{
				// flush the buffer
				_stream->Write( _bytesBuffer, _bufferCount );
				_bufferCount = 0;
			}
			else
			{
				_bufferCount += writtenBytes;
				++ch;
				break;
			}
		}
	}
}

//-----------------------------------------------------------------
void TextWriter::Print( const sString& str )
{
	Print( str.c_str(), str.Length() );
}

//-----------------------------------------------------------------
void TextWriter::Print( sInt i )
{
	sChar tmp[12];
	Chars::FromInt( tmp, i );
	Print( tmp, Chars::Length( tmp ) );
}

//-----------------------------------------------------------------
void TextWriter::Print( sUInt i )
{
	sChar tmp[12];
	Chars::FromUInt( tmp, i );
	Print( tmp, Chars::Length( tmp ) );
}

//-----------------------------------------------------------------
void TextWriter::Print( sChar ch )
{
	Print( &ch, 1 );
}

//-----------------------------------------------------------------
void TextWriter::Print( sFloat f )
{
	sChar tmp[32];
	Chars::FromFloat( tmp, f );
	Print( tmp, Chars::Length( tmp ) );
}

//-----------------------------------------------------------------
void TextWriter::Print( sDouble d )
{
	sChar tmp[32];
	Chars::FromDouble( tmp, d );
	Print( tmp, Chars::Length( tmp ) );
}

}}