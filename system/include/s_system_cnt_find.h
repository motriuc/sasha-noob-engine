/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_cnt_find.h
//  Created                 : 18 12 2007   21:40
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

template< typename _COLLECTION , typename _CMP >
class Find
{
private:
	typedef typename _COLLECTION::ElementType Type;
public:
	/**
	 *
	 */
	static sInt BinaryLowerBound( const _COLLECTION& collection, const Type& elem, sInt L, sInt R )
	{
		if( collection.Size() <= 0 )
			return 0;

		return privateBinaryLowerBound( collection, elem, L, R );
	}

	/**
	 *
	 */
	static inline sInt BinaryLowerBound( const _COLLECTION& collection, const Type& elem )
	{
		return BinaryLowerBound( collection, elem, 0, collection.Size() - 1 );
	}

	/**
	 *
	 */
	static inline sInt BinaryUpperBound( const _COLLECTION& collection, const Type& elem, sInt L, sInt R )
	{
		if( collection.Size() <= 0 )
			return 0;

		return privateBinaryUpperBound( collection, elem, L, R );
	}

	/**
	 *
	 */
	static inline sInt BinaryUpperBound( const _COLLECTION& collection, const Type& elem )
	{
		return BinaryUpperBound( collection, elem, 0, collection.Size() - 1 );
	}

private:
	static sInt privateBinaryLowerBound( const _COLLECTION& collection, const Type& elem, sInt L, sInt R )
	{
		for(;;)
		{
			__S_ASSERT( L >= 0 && L < collection.Size() );
			__S_ASSERT( R >= 0 && R < collection.Size() );

			if( L >= R )
			{
				if( _CMP::Big( elem, collection[R] ) )
					return R + 1;
				return R;
			}

			sInt M = ( L + R ) / 2;

			if( _CMP::Big( elem, collection[M] ) )
				L = M + 1;
			else
				R = M;
		}
	}

	static sInt privateBinaryUpperBound( const _COLLECTION& collection, const Type& elem, sInt L, sInt R )
	{
		for(;;)
		{
			__S_ASSERT( L >= 0 && L < collection.Size() );
			__S_ASSERT( R >= 0 && R < collection.Size() );

			if( L >= R )
			{
				if( _CMP::Small( elem, collection[R] ) )
					return R;
				return R + 1;
			}

			sInt M = ( L + R + 1 ) / 2;

			if( _CMP::Small( elem, collection[M] ) )
				R = M - 1;
			else
				L = M;
		}
	}
};

