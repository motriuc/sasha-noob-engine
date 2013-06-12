/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_move.h
//  Created                 : 28 6 2013   23:19
//  File path               : SLibF\system\Include
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
 * Move function
 * Ex:
 *   a = Move( b );
 */
#if defined( _SLIB_CPP11 )
	template< typename _Type >
	typename Traits<_Type>::RemoveReference&& Move( _Type&& src )
	{
		return (typename Traits<_Type>::RemoveReference&&)src;
	}
#else
	template< typename _Type >
	_Type& Move( _Type& src )
	{
		return src;
	}
#endif