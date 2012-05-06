/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_cnt_vector.h
//  Created                 : 25 6 2007   1:01
//  File path               : SLibF\system\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 100%
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
#ifndef _SYSTEM_CNT_VECTOR_INC_
#define _SYSTEM_CNT_VECTOR_INC_

/**
 *	 sVector
 */
template< typename _TYPE, System::Types::sInt _CAPACITY_INCREMENT = 0 >
class sVector
{
public:
	/**
	 *	Element type
	 */
	typedef _TYPE ElementType;
public:
	/**
	 *	default constructor
	 */
	inline sVector() :
		_pElementData( NULL ),
		_iElementCount( 0 ),
		_iElementCapasity( 0 )
	{
	}

	/**
	 *	Create vector with initial size
	 */
	explicit sVector( sInt size )
	{
		__S_ASSERT( size > 0 );

		_pElementData = new _TYPE[size];
		_iElementCount = 0;
		_iElementCapasity = size;
	}

	/**
	 *	Create vector with size and fill it with val
	 */
	sVector( sInt size, _TYPE val )
	{
		__S_ASSERT( size > 0 );

		_pElementData = new _TYPE[size];
		_iElementCount = size;
		_iElementCapasity = size;

		for( sInt i = 0; i < size; i++ )
			_pElementData[i] = val;
	}

	/**
	 *	Copy constructor
	 */
	sVector( const sVector< _TYPE, _CAPACITY_INCREMENT >& v )
	{
		sInt size = v.Size();
		if( size > 0 )
		{
			_pElementData = new _TYPE[size];
			_iElementCount = size;
			_iElementCapasity = size;

			for( sInt i = 0; i < size; i++ )
				_pElementData[i] = v._pElementData[i];
		}
		else
		{
			_pElementData = NULL;
			_iElementCount = 0;
			_iElementCapasity = 0;
		}
	}

	/**
	 *	destructor
	 */
	inline ~sVector()
	{
		delete[] _pElementData;
	}

	/**
	 *	copy operator
	 */
	void operator = ( const sVector< _TYPE, _CAPACITY_INCREMENT>& v )
	{
		EnsureCapacityNoCopy( v.Size() );

		for( sInt i = 0; i < v.Size(); i++ )
			_pElementData[i] = v._pElementData[i];
		
		if( !T::Traits<_TYPE>::BasicType )
		{
			for( sInt i = v.Size();  i < _iElementCount; i++)
				_pElementData[i] = _TYPE();
		}
	
		_iElementCount = v.Size();
	}

	/**
	 * get Vector Size
	 */
	inline sInt Size() const
	{
		return _iElementCount;
	}

	/**
	 * get set element at 0<= index < Size
	 */
	inline _TYPE& operator[] ( sInt index )
	{
		__S_ASSERT( index >=0 && index < _iElementCount );
		return _pElementData[index];
	}

	/**
	 * get set element at 0<= index < Size
	 */
	inline const _TYPE& operator[] ( sInt index ) const
	{
		__S_ASSERT( index >=0 && index < _iElementCount );
		return _pElementData[index];
	}

	/**
	 *	Add element to the end
	 */
	inline sInt Add( const _TYPE& item )
	{
		EnsureCapacity( _iElementCount + 1 );
		_pElementData[ _iElementCount ++ ] = item;
		return _iElementCount-1;
	}

	/**
	 *	Add elements to the end
	 */
	inline void Add( const _TYPE& item1, const _TYPE& item2 )
	{
		EnsureCapacity( _iElementCount + 2 );
		_pElementData[ _iElementCount ++ ] = item1;
		_pElementData[ _iElementCount ++ ] = item2;
	}

	/**
	 *	Add elements to the end
	 */
	inline void Add( const _TYPE& item1, const _TYPE& item2, const _TYPE& item3 )
	{
		EnsureCapacity( _iElementCount + 3 );
		_pElementData[ _iElementCount ++ ] = item1;
		_pElementData[ _iElementCount ++ ] = item2;
		_pElementData[ _iElementCount ++ ] = item3;
	}

	/**
	 *	Add elements to the end
	 */
	inline void Add( const _TYPE& item1, const _TYPE& item2, const _TYPE& item3, const _TYPE& item4 )
	{
		EnsureCapacity( _iElementCount + 4 );
		_pElementData[ _iElementCount ++ ] = item1;
		_pElementData[ _iElementCount ++ ] = item2;
		_pElementData[ _iElementCount ++ ] = item3;
		_pElementData[ _iElementCount ++ ] = item4;
	}
	
	/**
	 *
	 */
	inline void AddCount( const _TYPE& item, sInt count )
	{
		EnsureCapacity( _iElementCount + count );
		
		while( count > 0 )
		{
			_pElementData[ _iElementCount ++ ] = item;
			--count;
		}
	}

	/**
	 *	Add element to the end
	 */
	inline sInt AddC( const _TYPE item )
	{
		return Add( item );
	}

	/**
	 *	Add element at index
	 */
	sInt AddAt( sInt index, const _TYPE& item )
	{
		if( index >= _iElementCount )
			return Add( item );

		if( index < 0 )
			index = 0;

		__S_ASSERT( index >= 0 && index <= _iElementCount );

		EnsureCapacity( _iElementCount + 1 );

		for( sInt i = _iElementCount; i > index; i-- )
			_pElementData[i] = _pElementData[i - 1];
		
		_iElementCount++;
		_pElementData[index] = item;

		return index;
	}

	/**
	 *	Add element at index
	 */
	inline sInt AddAtC( sInt index, const _TYPE item )
	{
		return AddAt( index, item );
	}

	/**
	 *	remove all elements
	 */
	inline void RemoveAll()
	{
		if( !T::Traits<_TYPE>::BasicType )
		{
			for( sInt i = 0; i < _iElementCount; i++ )
				_pElementData[i] = _TYPE();
		}

		_iElementCount = 0;
	}

	/**
	 *	Removes last element and returs it
	 */
	inline void RemoveLast( _TYPE& t )
	{
		__S_ASSERT( _iElementCount > 0 );

		t = _pElementData[--_iElementCount];
		_pElementData[_iElementCount] = _TYPE();
	}

	/**
	 *	Removes last element
	 */
	inline void RemoveLast()
	{
		__S_ASSERT( _iElementCount > 0 );

		_pElementData[--_iElementCount] = _TYPE();
	}

	/**
	 * Removes element at index	
	 */
	void RemoveAt( sInt index, _TYPE& ret )
	{
		__S_ASSERT( index >= 0 && index < _iElementCount );
		
		ret = _pElementData[index];
		
		RemoveAt( index );
	}

	/**
	 * Removes element at index	
	 */
	inline void RemoveAt( sInt index )
	{
		__S_ASSERT( index >= 0 && index < _iElementCount );
				
		for( sInt i = index; i < _iElementCount - 1; i++ )
			_pElementData[i] = _pElementData[i+1];
		
		_pElementData[--_iElementCount] = _TYPE();
	}
	
	
	/**
	 * Remove elements from to to from the vector
	 */
	void Remove( sInt from, sInt to )
	{
		__S_ASSERT( from >= 0 && from < _iElementCount );

		if( to >= _iElementCount )
			to = _iElementCount - 1;

		if( to > from )
			to = from;

		for( sInt i = from, k = to + 1; k < _iElementCount; ++i, ++k )
		{
			_pElementData[i] = _pElementData[k];
		}

		SetSize( _iElementCount -  to + from - 1 );
	}

	/**
	 *	Set vector size
	 */
	inline void SetSize( sInt size )
	{
		__S_ASSERT( size >= 0 );

		if( !T::Traits<_TYPE>::BasicType )
		{
			for( sInt i = size;  i < _iElementCount; i++)
				_pElementData[i] = _TYPE();
		}

		EnsureCapacity( size );
		_iElementCount = size;
	}

	/**
	 *	return TRUE if is empty
	 */
	inline sBool IsEmpty() const
	{
		return _iElementCount <= 0;
	}

	/**
	 * Reserve 
	 */
	inline void Reserve( sInt minCapacity )
	{
		EnsureCapacity( minCapacity );
	}

	/**
	 * must not be used in normal cases
	 */
	inline _PLATFORM const _TYPE* GetBuffer() const { return _pElementData; }
	inline _PLATFORM _TYPE* GetBuffer() { return _pElementData; }

private:
	void EnsureCapacity( sInt minCapacity ) 
	{
		if( minCapacity <= _iElementCapasity ) return;

		_TYPE* pOldElement = _pElementData;

		sInt newCapacity = ( _CAPACITY_INCREMENT > 0 ) ? 
			( _iElementCapasity + _CAPACITY_INCREMENT ) : ( _iElementCapasity * 2 );

    	if( newCapacity < minCapacity ) newCapacity = minCapacity;

		_pElementData = new _TYPE[newCapacity];
		_iElementCapasity = newCapacity;

 		for( System::Types::sInt i = 0; i < _iElementCount; i++ ) 
			_pElementData[i] = pOldElement[i];

		if( pOldElement )
			delete[] pOldElement;		
    }

	void EnsureCapacityNoCopy( sInt minCapacity )
	{
		if( minCapacity <= _iElementCapasity ) return;

		if( _pElementData )
			delete[] _pElementData;

		System::Types::sInt newCapacity = ( _CAPACITY_INCREMENT > 0 ) ? 
			( _iElementCapasity + _CAPACITY_INCREMENT ) : ( _iElementCapasity * 2 );

		if( newCapacity < minCapacity )
			newCapacity = minCapacity;

		_pElementData = new _TYPE[newCapacity];
		_iElementCapasity = newCapacity;
	}

private:
	_TYPE*	_pElementData;
	sInt	_iElementCount;
	sInt	_iElementCapasity;
};

/**
 *	Some vectors
 */
typedef sVector<System::Types::sInt>	sIntVector;
typedef sVector<System::Types::sBool>	sBoolVector;
typedef sVector<System::Types::sString>	sStrings;

#endif // _SYSTEM_CNT_VECTOR_INC_
