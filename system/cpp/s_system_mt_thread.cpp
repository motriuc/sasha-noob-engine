/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_thread.cpp
//  Created                 : 31 3 2012
//  File path               : SLibF\system\cpp
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

#define _use_sError_
#include "s_system.h"

namespace System
{
namespace Mt
{

	/**
	 *	Main thread Id
	 */
#ifdef _SPL_WIN32
	DWORD system_mt_gmThreadId = ::GetCurrentThreadId();
#endif // _WIN32

	/**
	 * Thread
	 */
	Thread::Thread( bool bAutoDelete ) :
		_bAutoDelete( bAutoDelete ),
		_threadId( 0 ),
		_priority( ThreadPriority::eNormal ),
#ifdef _SPL_WIN32
		_hThread( NULL ),
		_hTerminate( NULL )
#endif // _SPL_WIN32
	{
	}

	/**
	 * DoStop()
	 */
	inline void Thread::DoStop()
	{
#ifdef _SPL_WIN32
		SetEvent( _hTerminate );
#endif // _SPL_WIN32
		OnTerminate();

		if( _bAutoDelete )
		{
			_bAutoDelete = false;
			delete this;
		}
	}

	/**
	 * SetPriority
	 */
	void Thread::SetPriority( ThreadPriority::ThreadPriority p )
	{
		_priority = p;

	#ifdef _SPL_WIN32
		if( _hThread != NULL )
		{
			int win32Priority = THREAD_PRIORITY_NORMAL;

			switch( p )
			{
			case ThreadPriority::eHigh:
				win32Priority = THREAD_PRIORITY_HIGHEST;
				break;
			case ThreadPriority::eNormal:
				win32Priority = THREAD_PRIORITY_NORMAL;
				break;
			case ThreadPriority::eLow:
				win32Priority = THREAD_PRIORITY_LOWEST;
				break;
			case ThreadPriority::eIdle:
				win32Priority = THREAD_PRIORITY_IDLE;
				break;
			}

			::SetThreadPriority( _hThread, win32Priority );
		}
	#endif // _SPL_WIN32
	}

#ifdef _SPL_WIN32

	DWORD WINAPI Thread::ThreadFunc( LPVOID lpParam )
	{
		Thread* pTh = (Thread*)lpParam;

		try
		{
			pTh->OnExec();
		}
		catch(...)
		{
			// do nothing here for now
		}

		try
		{
			pTh->DoStop();
		}
		catch(...)
		{
		}

		return 0;
	}

	void Thread::win32_CreateThread( bool bSuspended )
	{
		__S_ASSERT( _threadId == 0 );
		__S_ASSERT( _hTerminate == NULL );
		__S_ASSERT( _hThread == NULL );

		_hTerminate	= ::CreateEvent( NULL,TRUE, TRUE, NULL );

		if( _hTerminate == NULL )
			error_throw( Errors::Win32Error );

		ULONG id = 0;
		_hThread = ::CreateThread(
			NULL,
			0,
			ThreadFunc,
			this,
			CREATE_SUSPENDED,
			&id
		);

		_threadId = static_cast<ThreadId>( id );

		if( _hThread == NULL )
			error_throw( Errors::Win32Error );
		
		// Set start priority
		SetPriority( _priority );

		//
		ResetEvent( _hTerminate );

		OnCreate();

		if( !bSuspended )
			ResumeThread( _hThread );
	}

	#endif // _SPL_WIN32

	Thread::~Thread()
	{
#ifdef _SPL_WIN32
		win32_CloseThreadHandle();
#endif
	}

#ifdef _SPL_WIN32
	bool Thread::Terminate( int time )
	{
		::SetEvent( _hTerminate );

		bool ret = true;

		if( time != 0 )
		{
			DWORD t = time < 0 ? INFINITE : (DWORD) time;
			ret = ::WaitForSingleObject( _hThread, t ) == WAIT_OBJECT_0;
		}

		return ret;
	}
#endif // _SPL_WIN32

}

}
