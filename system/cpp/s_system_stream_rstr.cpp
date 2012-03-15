/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_rstr.cpp
//  Created                 : 25 8 2007   17:39
//  File path               : SLibF\system\Cpp
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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

namespace System
{

namespace Streams
{

//-----------------------------------------------------------------
TextReader::TextReader( const IInputStream* pStream, Encoding::Encoding encoding, sInt bufferSize ) :
	_stream( pStream ),
	_encoding( encoding ),

	_pReadBuffer( NULL ),
	_pTmpBuffer( NULL ),
	_bufferSize( bufferSize ),
	
	_iPosBuffer( 0 ),
	_iToReadFromBuffer( 0 )
{
	_pReadBuffer = new sChar[_bufferSize];
	_pTmpBuffer = new SBYTE[_bufferSize];
}

//-----------------------------------------------------------------
void TextReader::FillBuffer( sChar* pBuffer )
{
	__S_ASSERT( pBuffer != NULL );
	__S_ASSERT( _iToReadFromBuffer == 0 );

	_iPosBuffer = 0;

	switch( _encoding )
	{
	// Utf-8
	case Encoding::UTF_8:
		{
			sInt readBytes = _stream->Read( _pTmpBuffer, _bufferSize );
			Chars::ConvertFrom_UTF8( _pReadBuffer, _bufferSize, _pTmpBuffer, readBytes, _iToReadFromBuffer );
		}
		break;

	default:
		__S_ASSERT( sFalse );
	}
}

//-----------------------------------------------------------------
TextReader::~TextReader()
{
	delete _pReadBuffer;
	delete _pTmpBuffer;
}

//-----------------------------------------------------------------
sBool TextReader::Read( sChar& ch )
{
	if( !CheckReadBuffer() ) 
		return sFalse;

	ch = _pReadBuffer[_iPosBuffer];
	_iPosBuffer++;
	_iToReadFromBuffer--;

	return sTrue;
}

//-----------------------------------------------------------------
sBool TextReader::ReadLine( sString& str )
{
	str = _S("");
	
	while( CheckReadBuffer() )
	{
		sChar* pChar = _pReadBuffer + _iPosBuffer;
		
		for( sInt i = 0; i < _iToReadFromBuffer; i++ )
		{
			if( !Chars::IsNewLine( *pChar ) )
				goto getString;
			
			_iPosBuffer ++;
			_iToReadFromBuffer --;
			
			pChar++;
		}
	}
	
	getString:
	
	while( CheckReadBuffer() )
	{
		sChar* pChar = _pReadBuffer + _iPosBuffer;
		
		for( sInt i = 0; i < _iToReadFromBuffer; i++ )
		{
			if( Chars::IsNewLine( *pChar ) )
			{
				if( i > 0 )
				{
					str.Add( _pReadBuffer + _iPosBuffer, i );
					_iPosBuffer += i;
					_iToReadFromBuffer -= i;
				}
				
				return sTrue;
			}
			
			pChar++;
		}
		
		str.Add( _pReadBuffer + _iPosBuffer, _iToReadFromBuffer );
		
		_iToReadFromBuffer = 0;
	}
	
	return str.Length() > 0;	
}
	
//-----------------------------------------------------------------
sBool TextReader::Read( sString& str )
{
	str = _S("");

	while( CheckReadBuffer() )
	{
		sChar* pChar = _pReadBuffer + _iPosBuffer;

		for( sInt i = 0; i < _iToReadFromBuffer; i++ )
		{
			if( !Chars::IsSpace( *pChar ) )
				goto getString;

			_iPosBuffer ++;
			_iToReadFromBuffer --;
			
			pChar++;
		}
	}

	getString:

	while( CheckReadBuffer() )
	{
		sChar* pChar = _pReadBuffer + _iPosBuffer;

		for( sInt i = 0; i < _iToReadFromBuffer; i++ )
		{
			if( Chars::IsSpace( *pChar ) )
			{
				if( i > 0 )
				{
					str.Add( _pReadBuffer + _iPosBuffer, i );
					_iPosBuffer += i;
					_iToReadFromBuffer -= i;
				}
          
				return sTrue;
			}
			
			pChar++;
		}
		
		str.Add( _pReadBuffer + _iPosBuffer, _iToReadFromBuffer );
    
		_iToReadFromBuffer = 0;
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


}

}