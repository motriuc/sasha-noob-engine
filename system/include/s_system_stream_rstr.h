/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_rstr.h
//  Created                 : 31 1 2012   16:08
//  File path               : SLibF\system\Include
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

/**
 * TextReader	
 */
class TextReader : public ITextReader
{
public:
	TextReader( const IInputStream* pStream, Encoding::Encoding encoding = Encoding::UTF_8, sInt bufferSize = 1024 );

	~TextReader();

	virtual sBool Read( sInt& i );
	virtual sBool Read( sUInt& i );
	virtual sBool Read( sChar& ch );
	virtual sBool Read( sFloat& f );
	virtual sBool Read( sDouble& d );
	virtual sBool Read( sString& str );
	virtual sBool ReadLine( sString& str );

private:
	const IInputStream*		_stream;
	Encoding::Encoding		_encoding;

	sChar*					_pReadBuffer;
	SBYTE*					_pTmpBuffer;
	sInt					_bufferSize;

	sInt                    _iPosBuffer;
	sInt                    _iToReadFromBuffer;

private:
	void FillBuffer( sChar* pBuffer );
	sBool CheckReadBuffer();
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
inline sBool TextReader::CheckReadBuffer()
{
	if( _iToReadFromBuffer > 0 )
		return sTrue;

	FillBuffer( _pReadBuffer );
	return _iToReadFromBuffer > 0;
}
