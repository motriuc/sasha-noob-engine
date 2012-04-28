/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_wstr.h
//  Created                 : 25 4 2012   16:08
//  File path               : SLibF\system\Include
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

/**
 * TextWriter	
 */
class TextWriter : public ITextWriter
{
public:
	/**
	 * TextWriter
	 */
	TextWriter( IOutputStream* pStream, Encoding::Encoding encoding = Encoding::UTF_8, sInt bufferSize = 1024 );
	~TextWriter();

	virtual void Print( sInt i );
	virtual void Print( sUInt i );
	virtual void Print( sChar ch );
	virtual void Print( sFloat f );
	virtual void Print( sDouble d );
	virtual void Print( const sString& str );
	virtual void PrintNl();
	virtual void Flush();
private:
	void PrintUTF8( const sChar* ch, sInt length );

	void Print( const sChar* ch, sInt length )
	{
		((*this).*_print)( ch, length );
	}
private:
	IOutputStream*		_stream;
	Encoding::Encoding	_encoding;

	void (TextWriter::*_print)( const sChar* ch, sInt length );

	SBYTE*				_bytesBuffer;
	sInt				_bufferSize;
	sInt				_bufferCount;
};
