/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t.h
//  Created                 : 26 8 2007   18:12
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

namespace T
{
	using namespace System::Types;
	/**
	 * Swaps 2 values
	 */

	template<typename _TYPE>
	inline void SwapValues( _TYPE& a, _TYPE& b )
	{
		_TYPE tmp = a;
		a = b;
		b = tmp;
	}
	
	#include "s_system_t_typetraits.h"
	#include "s_system_t_factory.h"
}

template< typename _Type >
class DefaultCmp : public T::Traits< _Type >::Cmp
{	
};
