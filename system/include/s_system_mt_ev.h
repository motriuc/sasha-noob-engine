/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_ev.h
//  Created                 : 9 7 2007   15:53
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

/**
 *	Event
 */
class sEvent : public class_nocopy
{
public:
	/**
	 *	
	 */
	sEvent( sBool bInitState = sFalse, sBool bManual = sFalse );

	/**
	 *	
	 */
	~sEvent();

	/**
	 *	Set the event
	 */
	void Set() const;

	/**
	 *	unset the event
	 */
	void UnSet() const;

	/**
	 *	Wait for event, -1 means infinite,
	 *	Event is unset after wait if bManual is false
	 */
	sBool Wait( sInt time = -1 ) const;

// WIN32 platform
#ifdef _SPL_WIN32
private:
	_PLATFORM HANDLE	_hEvent;
public:
	_PLATFORM HANDLE GetHandle() const;
#endif // _SPL_WIN32
	
#ifdef 	_SPL_MAC
private:	
	mutable pthread_cond_t		_cond;
	mutable pthread_mutex_t		_mutex;
	mutable sBool				_state;
	sBool						_manual;
#endif	
};


#ifdef _SPL_WIN32
	#include "s_system_mt_ev_win32.inl"
#endif

#ifdef _SPL_MAC
	#include "s_system_mt_ev_mac.inl"
#endif

#endif
