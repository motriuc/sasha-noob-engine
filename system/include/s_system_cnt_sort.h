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

/**
 * Standard sorting algorithms
 */
template< typename _Collection, typename _CMP = System::DefaultCmp<_Collection::ElementType> >
class Sort
{
private:
	typedef typename _Collection::ElementType Type;
public:

public:
	/**
	 * sorts elemets in the colletion using QuickSort
	 * @param collection collection to sort
	 * @param L left position in the collectioin to sort
	 * @param R right position in the collection to sort
	 */
	static void QuickSort( _Collection& collection, sInt L, sInt R )
	{
		__S_ASSERT( L >= 0 && L < collection.Size() );
		__S_ASSERT( R >= 0 && R < collection.Size() );

		sInt delta = R - L;

		if( delta <= 0 )
			return;

		if( delta == 1 )
		{
			Sort2Elements( collection, L );
			return;
		}

		if( delta == 2 )
		{
			Sort3Elements( collection, L );
			return;
		}
		
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
					T::Swap( collection[I], collection[J] ); 
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
	 * sorts elemets in the colletion using QuickSort
	 * @param collection collection to sort
	 */
	static void QuickSort( _Collection& collection )
	{
		QuickSort( collection, 0, collection.Size() - 1 );
	}

	/**
	 * sorts 2 elements from a collection from position L
	 * @param collection collection to sort
	 * @param L position to sort
	 */
	static void Sort2Elements( _Collection& collection, sInt L )
	{
		Type& v0 = collection[L];
		Type& v1 = collection[L+1];

		if( _CMP::Big( v0, v1 ) )
		{
			T::Swap( v0, v1 );
		}
	}

	/**
	 * sorts 3 elements from a collection from position L
	 * @param collection collection to sort
	 * @param L position to sort
	 */
	static void Sort3Elements( _Collection& collection, sInt L )
	{
		Type& v0 = collection[L];
		Type& v1 = collection[L+1];
		Type& v2 = collection[L+2];

		if( _CMP::Big( v0, v1 ) ) // v0 > v1
		{
			if( _CMP::Big( v0, v2 ) ) // v0 > v2
			{
				if( _CMP::Big( v1, v2 ) ) // v1 > v2
				{
					T::Swap( v0, v2 );
				}
				else // v1 <= v2 
				{
					Type tmp = T::Move( v0 );
					v0 = T::Move( v1 );
					v1 = T::Move( v2 );
					v2 = T::Move( tmp );
				}
			}
			else // v0 <= v2
			{
				T::Swap( v0, v1 );
			}
		}
		else // v0 <= v1
		{
			if( _CMP::Big( v1, v2 ) ) // v1 > v2
			{
				if( _CMP::Big( v0, v2 ) ) // v0 > v2
				{
					Type tmp = T::Move( v0 );
					v0 = T::Move( v2 );
					v2 = T::Move( v1 );
					v1 = T::Move( tmp );
				}
				else // v0 <= v2
				{
					T::Swap( v1, v2 );
				}
			}
			else // v1 <= v2
			{
				// do nothing
			}
		}
	}
};
