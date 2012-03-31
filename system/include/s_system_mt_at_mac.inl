/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_at_mac.inl
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

inline sInt Inc( Atomic& nNumber )
{
#ifdef _SLIB_MT
	return OSAtomicIncrement32Barrier( &nNumber );
#else
	return ++nNumber;
#endif
}

inline sInt Dec( Atomic& nNumber )
{
#ifdef _SLIB_MT
	return OSAtomicDecrement32Barrier( &nNumber );
#else
	return --nNumber;
#endif
}

inline sUInt Inc( volatile sUInt& nNumber )
{
#ifdef _SLIB_MT
	return OSAtomicIncrement32Barrier( (int32_t*) &nNumber );
#else
	return ++nNumber;
#endif
}

inline sUInt Dec( volatile sUInt& nNumber )
{
#ifdef _SLIB_MT
	return OSAtomicDecrement32Barrier( (int32_t*) &nNumber );
#else
	return --nNumber;
#endif
}

#ifdef _SLIB_MT

inline sBool SetIf( Atomic& nNumber, sInt i, sInt v )
{
	return OSAtomicCompareAndSwap32Barrier( v, i, &nNumber );
}

#endif