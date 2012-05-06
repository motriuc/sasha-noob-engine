/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_file.h
//  Created                 : 30 6 2007   13:32
//  File path               : SLibF\system\Include
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

/**
 *	FileStream
 */
class FileStream : public IIOStream, private class_nocopy
{
public:
	FileStream( Files::LFile* file ) :
		_file( file )
	{
		__S_ASSERT( file != NULL );
	}
	
	virtual sUInt GetSize() const
	{
		return _file->Size();
	}

	virtual sUInt GetAvailableSize() const
	{
		return Limit::sUInt::Max;
	}

	virtual void Flush()
	{
	}

	virtual sBool IsEos() const
	{
		return _file->Size() == _file->Position();
	}

	virtual sBool IsBos() const
	{
		return _file->Position() == 0;
	}

	virtual sUInt Seek( sInt uPos, SeekType::SeekType ePosType = SeekType::eFromBegin ) const
	{
		return _file->Seek( uPos, ePosType );
	}

	virtual sUInt GetPosition() const
	{
		return _file->Position();
	}

	virtual sInt Read( void* pBuf, sInt lLength ) const throws_error
	{
		return _file->Read( pBuf, lLength );
	}

	virtual sInt Write( const void* pBuf, sInt lLength ) throws_error
	{
		return _file->Write( pBuf, lLength );
	}

private:
	Files::LFile*	_file;
};