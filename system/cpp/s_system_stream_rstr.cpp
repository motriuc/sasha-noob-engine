/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_rstr.cpp
//  Created                 : 25 8 2007   17:39
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
TextReader::TextReader( const IInputStream* pStream, Encoding::Encoding encoding, sInt bufferSize ) :
	_stream( pStream ),
	_encoding( encoding ),

	_charsBuffer( NULL ),
	_bytesBuffer( NULL ),
	_bufferSize( bufferSize ),
	
	_charsBufferPos( 0 ),
	_charsBufferCount( 0 ),
	_bytesBufferOffset( 0 )
{
	__S_ASSERT( _stream != NULL );
	__S_ASSERT( bufferSize >= 64 ); 

	_charsBuffer = new sChar[_bufferSize];
	_bytesBuffer = new SBYTE[_bufferSize];
}

//-----------------------------------------------------------------
void TextReader::FillBuffer( sChar* pBuffer )
{
	__S_ASSERT( pBuffer != NULL );
	__S_ASSERT( _charsBufferCount == 0 );

	_charsBufferPos = 0;

	switch( _encoding )
	{
	// Utf-8
	case Encoding::UTF_8:
		{
			sInt readBytes = _stream->Read( _bytesBuffer + _bytesBufferOffset, _bufferSize - _bytesBufferOffset ) 
				+ _bytesBufferOffset;

			_bytesBufferOffset = 0;

			Utf8Decode( readBytes );
		}
		break;

	default:
		__S_ASSERT( sFalse );
	}
}

//-----------------------------------------------------------------
void TextReader::Utf8Decode( sInt countBytes )
{
	__S_ASSERT( _charsBufferCount == 0 );

	const SBYTE* bytes = _bytesBuffer;
	sChar* ch = _charsBuffer;

	while( countBytes > 0 )
	{
		sInt bytesReaded;
		*ch = Chars::From_UTF8( bytes, countBytes, bytesReaded );

		if( bytesReaded == 0 )
		{
			error_throw_arg( Errors::StringError )
				_S("Invalid UTF8 stream")
			);
		}

		// need more data
		if( bytesReaded < 0 )
		{
			if( _charsBufferCount == 0 )
			{
				error_throw_arg( Errors::StringError )
					_S("Incomplete UTF8 stream")
				);
			}

			// move unreaded bytes to begin of the buffer
			for( sInt i = 0; i < countBytes; ++i )
				_bytesBuffer[i] = bytes[i];

			_bytesBufferOffset = bytesReaded;
			break;
		}

		++_charsBufferCount;
		++ch;
		++bytes;
		countBytes -= bytesReaded;
	}
}

//-----------------------------------------------------------------
TextReader::~TextReader()
{
	delete _charsBuffer;
	delete _bytesBuffer;
}

//-----------------------------------------------------------------
sBool TextReader::Read( sChar& ch )
{
	if( !CheckReadBuffer() ) 
		return sFalse;

	ch = _charsBuffer[_charsBufferPos];
	_charsBufferPos++;
	_charsBufferCount--;

	return sTrue;
}

//-----------------------------------------------------------------
sBool TextReader::ReadLine( sString& str )
{
	str = _S("");
	
	while( CheckReadBuffer() )
	{
		sChar* pChar = _charsBuffer + _charsBufferPos;
		
		for( sInt i = 0; i < _charsBufferCount; i++ )
		{
			if( !Chars::IsNewLine( *pChar ) )
				goto getString;
			
			_charsBufferPos ++;
			_charsBufferCount --;
			
			pChar++;
		}
	}
	
	getString:
	
	while( CheckReadBuffer() )
	{
		sChar* pChar = _charsBuffer + _charsBufferPos;
		
		for( sInt i = 0; i < _charsBufferCount; i++ )
		{
			if( Chars::IsNewLine( *pChar ) )
			{
				if( i > 0 )
				{
					str.Add( _charsBuffer + _charsBufferPos, i );
					_charsBufferPos += i;
					_charsBufferCount -= i;
				}
				
				return sTrue;
			}
			
			pChar++;
		}
		
		str.Add( _charsBuffer + _charsBufferPos, _charsBufferCount );
		
		_charsBufferCount = 0;
	}
	
	return str.Length() > 0;	
}
	
//-----------------------------------------------------------------
sBool TextReader::Read( sString& str )
{
	str = _S("");

	while( CheckReadBuffer() )
	{
		sChar* pChar = _charsBuffer + _charsBufferPos;

		for( sInt i = 0; i < _charsBufferCount; i++ )
		{
			if( !Chars::IsSpace( *pChar ) )
				goto getString;

			_charsBufferPos ++;
			_charsBufferCount --;
			
			pChar++;
		}
	}

	getString:

	while( CheckReadBuffer() )
	{
		sChar* pChar = _charsBuffer + _charsBufferPos;

		for( sInt i = 0; i < _charsBufferCount; i++ )
		{
			if( Chars::IsSpace( *pChar ) )
			{
				if( i > 0 )
				{
					str.Add( _charsBuffer + _charsBufferPos, i );
					_charsBufferPos += i;
					_charsBufferCount -= i;
				}
          
				return sTrue;
			}
			
			pChar++;
		}
		
		str.Add( _charsBuffer + _charsBufferPos, _charsBufferCount );
    
		_charsBufferCount = 0;
	}

	return str.Length() > 0;
}

//-----------------------------------------------------------------
sBool TextReader::Read( sInt& i )
{
	sString str;

	if( !Read( str ) ) 
		return sFalse;
	
	i = str.ToInt();

	return sTrue;
}

//-----------------------------------------------------------------
sBool TextReader::Read( sUInt& i )
{
	sString str;

	if( !Read( str ) ) 
		return sFalse;
	
	i = str.ToInt();

	return sTrue;
}

//-----------------------------------------------------------------
sBool TextReader::Read( sDouble& d )
{
	sString str;

	if( !Read( str ) ) 
		return sFalse;
	
	d = str.ToDouble();

	return sTrue;
}

//-----------------------------------------------------------------
sBool TextReader::Read( sFloat& f )
{
	sString str;

	if( !Read( str ) ) 
		return sFalse;
	
	f = str.ToFloat();

	return sTrue;
}
//-----------------------------------------------------------------


}}