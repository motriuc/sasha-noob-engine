/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_at_win32.inl
//  Created                 : 23 6 2007   23:09
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

inline sInt Inc( sAtomic& nNumber )
{
#ifdef _SLIB_MT
	return ::InterlockedIncrement( (long*)&nNumber );
#else
	return ++nNumber;
#endif
}

inline sInt Dec( sAtomic& nNumber )
{
#ifdef _SLIB_MT
	return ::InterlockedDecrement( (long*)&nNumber );
#else
	return --nNumber;
#endif
}

inline sUInt Inc( sUAtomic& nNumber )
{
#ifdef _SLIB_MT
	return ::InterlockedIncrement( (long*)&nNumber );
#else
	return ++nNumber;
#endif
}

inline sUInt Dec( sUAtomic& nNumber )
{
#ifdef _SLIB_MT
	return ::InterlockedDecrement( (long*)&nNumber );
#else
	return --nNumber;
#endif
}

inline sBool SetIf( sAtomic& nNumber, sInt i, sInt v )
{
#ifdef _SLIB_MT
	return ::InterlockedCompareExchange( (long*)&nNumber, v, i ) == i;
#else
	if( nNumber == i )
	{
		nNumber = v;
		return sTrue;
	}
	return sFalse;
#endif
}

inline sBool SetIf( sUAtomic& nNumber, sUInt i, sUInt v )
{
#ifdef _SLIB_MT
	return ::InterlockedCompareExchange( (long*)&nNumber, v, i ) == i;
#else
	if( nNumber == i )
	{
		nNumber = v;
		return sTrue;
	}
	return sFalse;
#endif
}

