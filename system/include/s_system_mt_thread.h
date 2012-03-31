/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_thread.h
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

typedef sUInt ThreadId;

/**
 *	Thread execution priority
 */
namespace ThreadPriority
{
	enum ThreadPriority
	{
		/**
		 *	
		 */
		eHigh	= 100,

		/**
		 *	
		 */
		eNormal = 0,

		/**
		 *	
		 */
		eLow	= -100,

		/**
		 *	
		 */
		eIdle	= -1000
	};
}

/**
 *	Thread class
 */
class Thread : private class_nocopy
{
public:
	/**
	 *	Creates a thread
	 *  if bAutoDelete == true thread deletes itself when it finishes
	 */
	explicit Thread( const Events::sEvent &run = Events::sEvent(), bool bAutoDelete = false );

	/**
	 *	Starts the thread
	 */
	void Start() throws_error;

	/**
	 *	 Destructor
	 */
	virtual ~Thread();

	/**
	 *	Terminates the thread
	 *	@param time [in] 0 -> no wait, > 0 -> wait in msec, < 0 infinite
	 */
	bool Terminate( int time = -1 );

	/**
	 *	check if the thread is finished
	 */
	bool Finished() const;

	/**
	 *	Checks if thread is terminating
	 */
	bool Terminating( ) const;

	/**
	 *	Sets thread priority
	 */
	void SetPriority( ThreadPriority::ThreadPriority p );

	/**
	 *	Returns current thread priority
	 */
	ThreadPriority::ThreadPriority GetPriority() const;

	/**
	 *	Sleep current thread
	 *	@param ms [in] msec
	 */
	static void Sleep( unsigned int ms );
		
	/**
	 *	returns current thread id
	 */
	static ThreadId CurrentThreadId();

	/**
	 *	Returns main Thread ID
	 */
	static ThreadId GetMainThreadId();

	/**
	 *	return True if the current thread is main thread
	 */
	static bool IsMainThread();

protected:
	virtual void OnCreate()		{}
	virtual void OnTerminate()	{}
	virtual void OnExec();

private:
	void DoStop();
private:
	ThreadId						_threadId;
	bool							_bAutoDelete;
	ThreadPriority::ThreadPriority	_priority;
	Events::sEvent					_run;

#ifdef _SPL_WIN32
private:
	HANDLE		_hThread;
	HANDLE		_hTerminate;

	static DWORD WINAPI ThreadFunc( LPVOID lpParam );

	void win32_CreateThread( bool bSuspended );
	void win32_CloseThreadHandle();

#endif // _SPL_WIN32
	
#ifdef _SPL_MAC	
	pthread_t						_pthread;
	
	void pthread_CreateThread();
	
	static void* pthread_ThreadFunc( void* param );
#endif // _SPL_MAC	
};

#ifdef _SPL_WIN32
	#include "s_system_mt_thread_win32.inl"
#endif // _SPL_WIN32

#ifdef _SPL_MAC
	#include "s_system_mt_thread_mac.inl"
#endif
