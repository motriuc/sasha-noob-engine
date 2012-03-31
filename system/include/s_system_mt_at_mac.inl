/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_at_win32.inl
//  Created                 : 23 6 2011   23:09
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

#ifdef _SLIB_MT
	#include <libkern/OSAtomic.h>
#endif

inline sInt Inc( volatile sInt& nNumber )
{
#ifdef _SLIB_MT
	return OSAtomicIncrement32( &nNumber );
#else
	return ++nNumber;
#endif
}
inline sInt Dec( volatile sInt& nNumber )
{
#ifdef _SLIB_MT
	return ::OSAtomicDecrement32( &nNumber );
#else
	return --nNumber;
#endif
}

inline sUInt Inc( volatile sUInt& nNumber )
{
#ifdef _SLIB_MT
	return OSAtomicIncrement32( &nNumber );
#else
	return ++nNumber;
#endif
}

inline sUInt Dec( volatile sUInt& nNumber )
{
#ifdef _SLIB_MT
	return ::OSAtomicDecrement32( &nNumber );
#else
	return --nNumber;
#endif
}
