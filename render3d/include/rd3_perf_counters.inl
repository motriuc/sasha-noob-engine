////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_perf_counters.inl
//	Created            : 20 1 2012   23:04
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////


inline void PerformanceCounter::operator += ( sInt n )
{
	_intCounter += n;
} 

inline void PerformanceCounter::operator -= ( sInt n )
{
	_intCounter -= n;
} 

inline void PerformanceCounter::operator += ( sFloat n )
{
	_floatCounter += n;
} 

inline void PerformanceCounter::operator -= ( sFloat n )
{
	_floatCounter -= n;
} 

inline void PerformanceCounter::operator += ( sDouble n )
{
	_doubleCounter += n;
} 

inline void PerformanceCounter::operator -= ( sDouble n )
{
	_doubleCounter -= n;
}

inline void PerformanceCounter::operator = ( sInt n )
{
	_intCounter = n;
}

inline void PerformanceCounter::operator = ( sFloat n )
{
	_floatCounter = n;
}

inline void PerformanceCounter::operator = ( sDouble n )
{
	_doubleCounter = n;
}

inline sInt PerformanceCounter::ValueInt() const
{
	return _intCounter;
}

inline sDouble PerformanceCounter::ValueDouble() const
{
	return _doubleCounter;
}

inline void PerformanceCounter::StartTimer()
{
	_timerStart = System::Platform::GetTickD();
}	

inline void PerformanceCounter::StopTimer()
{
	sDouble v = System::Platform::GetTickD() - _timerStart;
	_currentTime += v;
}

inline void PerformanceCounter::ResetTimer()
{
	_doubleCounter = _currentTime;
	_currentTime = 0.0;
}

