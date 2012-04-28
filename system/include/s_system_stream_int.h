/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_int.h
//  Created                 : 30 6 2007   13:03
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
 * Base stream interface
 */
class IBaseStream
{
public:
	virtual ~IBaseStream()				{}

	/**
	 * Get stream size 
	 */
	virtual sUInt GetSize() const = 0;

	/**
	 * Get stream aviable size
	 */
	virtual sUInt GetAvailableSize() const = 0;

	/**
	 * Flush content of the stream
	 */
	virtual void Flush() {}

	/**
	 * Is end of stream
	 */
	virtual sBool IsEos() const = 0;

	/**
	 * Is begin of stream
	 */
	virtual sBool IsBos() const = 0;

	/**
	 * Seek in the stream
	 */
	virtual sUInt Seek( 
		sInt uPos, 
		SeekType::SeekType ePosType = SeekType::eFromBegin
	) const = 0;

	/**
	 * Get Position
	 */
	virtual sUInt GetPosition() const = 0;
};

/**
 * Base input stream
 */
class IInputStream : public virtual IBaseStream
{
public:
	/**
	 * Read stream
	 */
	virtual sInt Read( void* pBuf, sInt lLength ) const throws_error = 0;
};

/**
 * Base output stream
 */
class IOutputStream : public virtual IBaseStream
{
public:
	/**
	 * Write to stream
	 */
	virtual sInt Write( const void* pBuf, sInt lLength ) throws_error = 0;
};

/**
 * Base Input Output stream
 */
class IIOStream : public IInputStream, public IOutputStream
{
};


/**
 *	Print Stream
 */
class ITextWriter
{
public:
	virtual void Print( sInt i ) = 0;
	virtual void Print( sUInt i ) = 0;
	virtual void Print( sChar ch ) = 0;
	virtual void Print( sFloat f ) = 0;
	virtual void Print( sDouble d ) = 0;
	virtual void Print( const sString& str ) = 0;
	virtual void PrintNl() = 0;
	virtual void Flush() = 0;
};

/**
 *	Read stream
 */
class ITextReader
{
public:
	virtual sBool Read( sInt& i ) = 0;
	virtual sBool Read( sUInt& i ) = 0;
	virtual sBool Read( sChar& ch ) = 0;
	virtual sBool Read( sFloat& f ) = 0;
	virtual sBool Read( sDouble& d ) = 0;
	virtual sBool Read( sString& str ) = 0;
	virtual sBool ReadLine( sString& str ) = 0;
};


