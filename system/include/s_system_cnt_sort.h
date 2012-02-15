/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_sort.h
//  Created                 : 6 2 2012   18:12
//  File path               : SLibF\system\include
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

template< typename _COLLECTION, typename _CMP >
class Sort
{
private:
	typedef typename _COLLECTION::ElementType Type;	
public:
	/**
	 * QuickSort
	 */
	static void QuickSort( _COLLECTION& collection, sInt L, sInt R )
	{
		__S_ASSERT( L >= 0 && L < collection.Size() );
		__S_ASSERT( R >= 0 && R < collection.Size() );
		
		sInt I, J;
		
		do
		{
			I = L;
			J = R;
			
			Type P = collection[ (L + R) / 2 ];
			do
			{
				while( _CMP::Small( collection[I],  P ) ) I++;
				while( _CMP::Big( collection[J], P ) ) J--;
				
				if( I <= J )
				{
					Type S = collection[I];
					collection[I] = collection[J];
					collection[J] = S;
					I++;
					J--;
				}
			} while( I <= J );
			
			if( L < J )
				QuickSort( collection, L, J );
			
			L = I;
		} while( I < R );
	}
	
	/**
	 *
	 */
	static inline void QuickSort( _COLLECTION& collection )
	{
		QuickSort( collection, 0, collection.Size() );
	}
};


