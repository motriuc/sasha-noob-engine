/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_swap.h
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
 * Swap values function
 *
 * Ex:
 *    Swap( a, b )
 */
template< typename _Type >
void Swap( _Type& a, _Type& b )
{
	_Type tmp = Move( a );
	a = Move( b );
	b = Move( tmp );
}
