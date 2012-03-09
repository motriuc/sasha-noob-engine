/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_cnt_sorted.h
//  Created                 : 6 2 2012   21:40
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
 * Sorted vector
 */
template< typename _Type, typename _CMP >
class sSorted
{
private:
	typedef Find< sVector<_Type>, _CMP > FindData;
	
public:
	
	sSorted( sInt maxElementCount = 0 ) :
		_maxElementCount( maxElementCount )
	{
	}
	
	void Add( const _Type& v )
	{
		sInt i = FindData::BinaryUpperBound( _data, v );
		
		_data.AddAt( i, v );
		
		if( _maxElementCount != 0 )
		{
			if( _maxElementCount < _data.Size() )
			{
				_data.RemoveAt( _data.Size() - 1 );
			}
		}
	}

	sInt FindUpperBound( const _Type& v ) const
	{
		return FindData::BinaryUpperBound( _data, v );
	}
	
	inline sInt Size() const
	{
		return _data.Size();
	}
	
	inline _Type& operator[] ( sInt index )
	{
		return _data[index];
	}
	
	inline const _Type& operator[] ( sInt index ) const
	{
		return _data[index];
	}
	
	inline void RemoveAll()
	{
		_data.RemoveAll();
	}
	
	inline void Reserve( sInt minCapacity )
	{
		_data.Reserve( minCapacity );
	}
	
private:
	sVector<_Type>	_data;
	sInt			_maxElementCount;
};
