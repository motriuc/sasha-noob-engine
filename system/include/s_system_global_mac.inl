/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_global_mac.inl
//  Created                 : 11 01 2012   17:07
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

void DebugWarning( const sChar* pMessage )
{
#ifdef _SLIB_WCHAR
	#error not implemented
#else
	printf( "\nDebug Warning: %s", pMessage );
#endif	 
}

inline void ShowWarning( const sChar* pMessage )
{
#ifdef _SLIB_WCHAR
	#error not implemented
#else
	printf( "\nWarning: %s", pMessage );
#endif	 
}
   
inline void ShowError( const sChar* pMessage )
{
#ifdef _SLIB_WCHAR
	#error not implemented
#else
	printf("\nError: %s", pMessage );
#endif	 
}

inline void ShowMessage( const sChar* pMessage )
{
#ifdef _SLIB_WCHAR
	#error not implemented
#else
	printf("\nMessage: %s", pMessage );
#endif	 
}

inline sDouble GetTickD()
{
	static sDouble delta = 0.0;
		
	if (delta == 0.0 ) 
	{
		mach_timebase_info_data_t timeBase;
		mach_timebase_info( &timeBase );
		delta = (sDouble)timeBase.numer / (sDouble)timeBase.denom;
		delta *= 1e-9;
	}
		
	sDouble time = (sDouble)mach_absolute_time();
	time *= delta;
		
	return time;
}

inline sUInt GetTick()
{
	static uint64_t startTime = 0;
	static mach_timebase_info_data_t timeBase;
	
	if( startTime )
	{
		mach_timebase_info( &timeBase );
		startTime = mach_absolute_time();
	}
	
	uint64_t dt = ( mach_absolute_time() - startTime ) / 1000000;
	
	return (sUInt)dt;
}


inline void Exit( sInt returnCode )
{
	__S_ASSERT( false );
}
