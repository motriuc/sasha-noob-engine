/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_alloc_fixed.h
//  Created                 : 19 06 2013
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
 * Memory chunk with memory fixed space
 */
template< typename _Type >
class FixedMemoryChunk : private class_nocopy
{
public:
	/**
	 * Creates memory chunk
	 * @param uBlockSize block size in _TYPE units
	 * @param uBlockCount block count
	 */
	FixedMemoryChunk( sUInt uBlockSize, sUInt uBlockCount ) :
		_uBlockSize( uBlockSize ),
		_uBlockCount( uBlockCount )
	{
		_pData = new _Type[ _uBlockCount * _uBlockSize ];
		Reset();
	}

	~FixedMemoryChunk()
	{
		delete[] _pData;
	}
    
	/**
	 * reset the allocations
	 */
	void Reset()
	{
		_uBlockFirstAviable = 0;
		_uBlockAviable = _uBlockCount;
    
		_Type* pBlock = _pData;
		
		for( sUInt i = 1; i <= _uBlockCount;  pBlock += _uBlockSize, i++ )
		{
			*pBlock = i;
		}
	}

	/**
	 * Allocate a _uBlockSize of _Type
	 */
	void* Allocate()
	{
		_Type* pResult = _pData + _uBlockSize * _uBlockFirstAviable;
		_uBlockFirstAviable = *pResult;
		_uBlockAviable--;
		return pResult;
	}

	/**
	 * Return TRUE if pointer belong to chunk
	 */
	sBool IsHere( void* pPtr )
	{
		return (_Type*)pPtr >= _pData && (_Type*)pPtr < ( _pData + _uBlockSize * _uBlockCount );
	}

	/**
	 * Deallocate a _uBlockSize of _Type
	 */
	void Deallocate( void* pPtr )
	{
		__S_ASSERT( IsHere( pPtr ) );
		
		_Type* pToRelease = static_cast<_Type*>( pPtr );
		*pToRelease = _uBlockFirstAviable;
		_uBlockFirstAviable = ( pToRelease - _pData) / _uBlockSize;
		_uBlockAviable++;
	}

	/**
	 * Return TRUE if chunk has free space
	 */
	sBool HasSpace()
	{
		return _uBlockAviable > 0;
	}

	/**
	 * Retrun TRUE if the chunk is empty
	 */
	sBool IsEmpty()
	{
		return _uBlockAviable == _uBlockCount;
	}

private:
	sUInt   _uBlockSize;
	sUInt   _uBlockCount;
	sUInt   _uBlockAviable;
	sUInt   _uBlockFirstAviable;
	_Type*  _pData;
};
