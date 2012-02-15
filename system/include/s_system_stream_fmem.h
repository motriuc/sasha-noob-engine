/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_fmem.h
//  Created                 : 17 1 2012   13:01
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
 * ReadMemStream
 */
class ReadMemStream : public IInputStream, private class_nocopy
{
public:
	ReadMemStream( const void* pBuffer, sInt length ) :
		_pBuffer( reinterpret_cast<const SBYTE*> ( pBuffer ) ),
		_length( length ),
		_pos( 0 )
	{
	}
	
	virtual sUInt GetSize() const
	{
		return _length;
	}
	
	virtual sUInt GetAvailableSize() const
	{
		return _length;
	}
	
	virtual void Flush()
	{
	}
	
	virtual sBool IsEos() const
	{
		return _length == _pos;
	}
	
	virtual sBool IsBos() const
	{
		return _pos == 0;
	}
	
	virtual sUInt Seek( sInt uPos, SeekType::SeekType ePosType = SeekType::eFromBegin ) const
	{
		switch (ePosType) 
		{
			case SeekType::eFromBegin:
				_pos = uPos;
			break;
			
			case SeekType::eFromEnd:
				_pos = _length + uPos;
			break;
				
			case SeekType::eFromCurrent:
				_pos += uPos;
			break;
		}
		
		if (_pos < 0 )
			_pos = 0;
		else if( _pos > _length )
			_pos = _length;
		
		return _pos;
	}
	
	virtual sUInt GetPosition() const
	{
		return _pos;
	}
	
	virtual sInt Read( void* pBuf, sInt lLength ) const throws_error
	{
		sInt len = System::FMath::Min( _length - _pos, lLength );
		System::Memory::Copy( pBuf, _pBuffer + _pos, len );
		
		return len;
	}
		
private:
	const SBYTE*	_pBuffer;
	sInt			_length;
	mutable sInt	_pos;
};