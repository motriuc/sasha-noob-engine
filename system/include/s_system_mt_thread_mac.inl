/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_thread_mac.inl
//  Created                 : 31 3 2012
//  File path               : SLibF\system\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      Utils for multithreaded computing
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

inline ThreadPriority::ThreadPriority Thread::GetPriority() const
{
	return _priority;
}


inline void Thread::Start()
{
	pthread_CreateThread();
}

inline bool Thread::Terminating() const
{
	__S_ASSERT( sFalse );
	return sFalse;
}

inline ThreadId Thread::CurrentThreadId()
{
	__S_ASSERT( sFalse );
	return 0;
}


inline bool Thread::Finished() const
{
	__S_ASSERT( sFalse );
	return _pthread == NULL ;
}

inline void Thread::Sleep( unsigned int ms )
{
	__S_ASSERT( sFalse );
}

inline bool Thread::IsMainThread()
{
	__S_ASSERT( sFalse );
	return sTrue;
}

inline ThreadId Thread::GetMainThreadId()
{
	__S_ASSERT( sFalse );
	return 0;
}
