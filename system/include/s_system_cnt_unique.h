/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_cnt_unique.h
//  Created                 : 28 3 2012
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
 * Sorted vector
 */
template< typename _Type, typename _CMP >
class sUnique
{
private:
	typedef Find< sVector<_Type>, _CMP > FindData;
	
public:
	
	sUnique( sInt maxElementCount = 0 ) :
		_maxElementCount( maxElementCount )
	{
	}
	
	void Add( const _Type& v )
	{
		sInt i = FindData::BinaryUpperBound( _data, v );
		
		if( i < Size() && _CMP::Equal( v, _data[i] ) )
		{
			_data[i] = v;
		}
		else
		{
			_data.AddAt( i, v );
		
			if( _maxElementCount != 0 )
			{
				if( _maxElementCount < _data.Size() )
				{
					_data.RemoveAt( _data.Size() - 1 );
				}
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

	inline void Remove( sInt from, sInt to )
	{
		_data.Remove( from, to );
	}
	
private:
	sVector<_Type>	_data;
	sInt			_maxElementCount;
};
