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

inline sInt Inc( Atomic& nNumber )
{
#ifdef _SLIB_MT
	return ::InterlockedIncrement( (long*)&nNumber );
#else
	return ++nNumber;
#endif
}

inline sInt Dec( Atomic& nNumber )
{
#ifdef _SLIB_MT
	return ::InterlockedDecrement( (long*)&nNumber );
#else
	return --nNumber;
#endif
}

inline sUInt Inc( volatile sUInt& nNumber )
{
#ifdef _SLIB_MT
	return ::InterlockedIncrement( (long*)&nNumber );
#else
	return ++nNumber;
#endif
}

inline sUInt Dec( volatile sUInt& nNumber )
{
#ifdef _SLIB_MT
	return ::InterlockedDecrement( (long*)&nNumber );
#else
	return --nNumber;
#endif
}

