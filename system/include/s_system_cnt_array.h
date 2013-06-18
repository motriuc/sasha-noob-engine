/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_array.h
//  Created                 : 10 4 2012
//  File path               : SLibF\system\include
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
 * A static size Array
 * Ex:
 *    Array<int,7> array of 7;
 */
template< typename _Type, sInt _Size >
class Array
{
public:
	typename typedef _Type ElementType;
	typename typedef T::Traits<_Type>::AsInput InputType;
public:
	Array()
	{
	}

	sInt Size() const
	{
		return _Size;
	}

	_Type& operator []( sInt index )
	{
		__S_ASSERT( index >= 0 );
		__S_ASSERT( index < _Size );
		return _array[index];
	}

	const _Type& operator []( sInt index ) const
	{
		__S_ASSERT( index >= 0 );
		__S_ASSERT( index < _Size );
		return _array[index];
	}

	/**
	 * must not be used in normal cases
	 */
	_PLATFORM const _Type* GetBuffer() const { return _array; }
	_PLATFORM _Type* GetBuffer() { return _array; }
private:
	_Type	_array[_Size];
};
