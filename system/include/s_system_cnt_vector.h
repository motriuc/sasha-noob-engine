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
 * A vector structure 
 */
template< typename _Type >
class sVector
{
private:
	enum 
	{
		_CAPACITY_INCREMENT = 0
	};

public:
	typename typedef _Type ElementType;
	typename typedef T::Traits<_Type>::AsInput InputType;
public:
	/**
	 * default constructor
	 * RATING( +-+ )
	 */
	sVector()
	{
		Reset();
	}

	/**
	 * creates a vector with and preallocated size
	 * RATING( +-+ )
	 * @param size allocated size of the vector
	 */
	explicit sVector( sInt size )
	{
		__S_ASSERT( size > 0 );

		_pElementData = new _Type[size];
		_iElementCount = 0;
		_iElementCapasity = size;
	}

	/**
	 * creates a vector with an initial size and filled with one value
	 * RATING( +-+ )
	 * @param size size of the vector
	 * @param val value to be filled
	 */
	sVector( sInt size, InputType val )
	{
		__S_ASSERT( size > 0 );

		_pElementData = new _Type[size];
		_iElementCount = size;
		_iElementCapasity = size;

		for( sInt i = 0; i < size; i++ )
			_pElementData[i] = val;
	}

	/**
	 * copy constructor
	 * RATING( +-+ )
	 * @param v the vector source
	 */
	sVector( const sVector< _Type >& v )
	{
		sInt size = v.Size();
		if( size > 0 )
		{
			_pElementData = new _Type[size];
			_iElementCount = size;
			_iElementCapasity = size;

			for( sInt i = 0; i < size; i++ )
				_pElementData[i] = v._pElementData[i];
		}
		else
		{
			Reset();
		}
	}

#ifdef _SLIB_CPP11
	/**
	 * move constructor
	 * RATING( +-- )
	 * @param v the vector source
	 */
	sVector( sVector< _Type >&& v )
	{
		Move( v );
		v.Reset();
	}

	/**
	 * move operator
	 * RATING( +-- )
	 * @param v the source vector
	 */
	void operator = ( sVector< _Type >&& v )
	{
		if( this != &v )
		{
			Free();
			Move( v );
			v.Reset();
		}
	}
#endif

	/**
	 *	destructor
	 */
	~sVector()
	{
		Free();
	}

	/**
	 * copy operator
	 * RATING( +-- )
	 * @param v the source vector
	 */
	void operator = ( const sVector< _Type >& v )
	{
		EnsureCapacityNoCopy( v.Size() );

		for( sInt i = 0; i < v.Size(); i++ )
			_pElementData[i] = v._pElementData[i];
		
		Reset( v.Size() );
		_iElementCount = v.Size();
	}

	/**
	 * returns vector size
	 * @return vector size
	 */
	sInt Size() const
	{
		return _iElementCount;
	}

	/**
	 * returns vector current capacity
	 * @return vector capacity
	 */
	sInt Capacity() const
	{
		return _iElementCapasity;
	}

	/**
	 * get set element at 0<= index < Size
	 */
	_Type& operator[] ( sInt index )
	{
		__S_ASSERT( index >=0 && index < _iElementCount );
		return _pElementData[index];
	}

	/**
	 * get set element at 0<= index < Size
	 */
	const _Type& operator[] ( sInt index ) const
	{
		__S_ASSERT( index >=0 && index < _iElementCount );
		return _pElementData[index];
	}

	/**
	 * adds and element to the end of the vector
	 * RATING( +-+ )
	 * @param item the elemet
	 * @return index of the new added element
	 */
	sInt Add( InputType item )
	{
		EnsureCapacity( _iElementCount + 1 );
		_pElementData[ _iElementCount ++ ] = item;
		return _iElementCount-1;
	}

	/**
	 *	Add elements to the end
	 */
	void Add( InputType item1, InputType item2 )
	{
		EnsureCapacity( _iElementCount + 2 );
		_pElementData[ _iElementCount ++ ] = item1;
		_pElementData[ _iElementCount ++ ] = item2;
	}

	/**
	 *	Add elements to the end
	 */
	void Add( InputType item1, InputType item2, InputType item3 )
	{
		EnsureCapacity( _iElementCount + 3 );
		_pElementData[ _iElementCount ++ ] = item1;
		_pElementData[ _iElementCount ++ ] = item2;
		_pElementData[ _iElementCount ++ ] = item3;
	}

	/**
	 *	Add elements to the end
	 */
	void Add( InputType item1, InputType item2, InputType item3, InputType item4 )
	{
		EnsureCapacity( _iElementCount + 4 );
		_pElementData[ _iElementCount ++ ] = item1;
		_pElementData[ _iElementCount ++ ] = item2;
		_pElementData[ _iElementCount ++ ] = item3;
		_pElementData[ _iElementCount ++ ] = item4;
	}
	
	/**
	 * Adds one element count times at the end
	 */
	void AddCount( InputType item, sInt count )
	{
		EnsureCapacity( _iElementCount + count );
		
		while( count > 0 )
		{
			_pElementData[ _iElementCount ++ ] = item;
			--count;
		}
	}

	/**
	 * adds an element at index position in the vector
	 * RATING( +-+ )
	 * @patam index new element position
	 * @param item the element
	 * @return returns the index of added element
	 */
	sInt AddAt( sInt index, InputType item )
	{
		if( index >= _iElementCount )
			return Add( item );

		if( index < 0 )
			index = 0;

		__S_ASSERT( index >= 0 && index <= _iElementCount );

		EnsureCapacity( _iElementCount + 1 );

		for( sInt i = _iElementCount; i > index; i-- )
			_pElementData[i] = T::Move( _pElementData[i - 1] );
		
		_iElementCount++;
		_pElementData[index] = item;

		return index;
	}

	/**
	 *	remove all elements
	 */
	void RemoveAll()
	{
		Reset( 0 );
		_iElementCount = 0;
	}

	/**
	 *	Removes last element and returs it
	 */
	void RemoveLast( _Type& t )
	{
		__S_ASSERT( _iElementCount > 0 );

		t = _pElementData[--_iElementCount];
		_pElementData[_iElementCount] = _Type();
	}

	/**
	 *	Removes last element
	 */
	void RemoveLast()
	{
		__S_ASSERT( _iElementCount > 0 );

		_pElementData[--_iElementCount] = _Type();
	}

	/**
	 * Removes element at index	
	 */
	void RemoveAt( sInt index, _Type& ret )
	{
		__S_ASSERT( index >= 0 && index < _iElementCount );
		
		ret = _pElementData[index];
		
		RemoveAt( index );
	}

	/**
	 * Removes element at index	
	 */
	void RemoveAt( sInt index )
	{
		__S_ASSERT( index >= 0 && index < _iElementCount );

		for( sInt i = index; i < _iElementCount - 1; i++ )
			_pElementData[i] = T::Move( _pElementData[i+1] );

		_pElementData[--_iElementCount] = _Type();
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
			_pElementData[i] = T::Move( _pElementData[k] );
		}

		SetSize( _iElementCount -  to + from - 1 );
	}

	/**
	 *	Set vector size
	 */
	void SetSize( sInt size )
	{
		__S_ASSERT( size >= 0 );

		Reset( size );
		EnsureCapacity( size );
		_iElementCount = size;
	}

	/**
	 *	return TRUE if is empty
	 */
	sBool IsEmpty() const
	{
		return _iElementCount <= 0;
	}

	/**
	 * Reserve 
	 */
	void Reserve( sInt minCapacity )
	{
		EnsureCapacity( minCapacity );
	}

	/**
	 * must not be used in normal cases
	 */
	_PLATFORM const _Type* GetBuffer() const { return _pElementData; }
	_PLATFORM _Type* GetBuffer() { return _pElementData; }

private:
	void EnsureCapacity( sInt minCapacity ) 
	{
		if( minCapacity <= _iElementCapasity ) return;

		_Type* pOldElement = _pElementData;

		sInt newCapacity = ( _CAPACITY_INCREMENT > 0 ) ? 
			( _iElementCapasity + _CAPACITY_INCREMENT ) : ( _iElementCapasity * 2 );

    	if( newCapacity < minCapacity ) newCapacity = minCapacity;

		_pElementData = new _Type[newCapacity];
		_iElementCapasity = newCapacity;

 		for( System::Types::sInt i = 0; i < _iElementCount; i++ ) 
			_pElementData[i] = T::Move( pOldElement[i] );

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

		_pElementData = new _Type[newCapacity];
		_iElementCapasity = newCapacity;
	}

	/**
	 * Resets the elements from size to element count
	 */
	void Reset( sInt size )
	{
		if( !T::Traits<_Type>::IsBasicType )
		{
			for( sInt i = size;  i < _iElementCount; i++ )
				_pElementData[i] = _Type();
		}
	}

	void Reset()
	{
		_pElementData = NULL;
		_iElementCount = 0;
		_iElementCapasity = 0;
	}

	void Move( const sVector< _Type >& v )
	{
		_pElementData = v._pElementData;
		_iElementCount = v._iElementCount;
		_iElementCapasity = v._iElementCapasity;
	}

	void Free()
	{
		delete[] _pElementData;
	}

private:
	_Type*	_pElementData;
	sInt	_iElementCount;
	sInt	_iElementCapasity;
};

/**
 *	Basic type vector definitions
 */
typedef sVector<sInt> sIntVector;
typedef sVector<sBool> sBoolVector;
typedef sVector<sString> sStrings;

#endif // _SYSTEM_CNT_VECTOR_INC_
