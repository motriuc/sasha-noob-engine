/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_thread_win32.inl
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
	win32_CreateThread( false );
}

inline bool Thread::Terminating() const
{
	return ::WaitForSingleObject( _hTerminate, 0 ) == WAIT_OBJECT_0;
}

inline ThreadId Thread::CurrentThreadId()
{
	return ::GetCurrentThreadId();
}

inline void Thread::win32_CloseThreadHandle()
{
	if( _hThread != NULL )
	{
		::CloseHandle( _hThread );
		_hThread = NULL;
	}
}

inline bool Thread::Finished() const
{
	return _hThread == NULL || ::WaitForSingleObject( _hThread, 0 ) == WAIT_OBJECT_0;
}

inline void Thread::Sleep( unsigned int ms )
{
	::Sleep( ms );
}

inline bool Thread::IsMainThread()
{
	extern DWORD system_mt_gmThreadId;
	return system_mt_gmThreadId == ::GetCurrentThreadId();
}

inline ThreadId Thread::GetMainThreadId()
{
	extern DWORD system_mt_gmThreadId;
	return system_mt_gmThreadId;
}
