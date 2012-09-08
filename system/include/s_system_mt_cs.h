/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_cs.h
//  Created                 : 23 6 2007   22:54
//  File path               : SLibF\system\include
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

/**
 *	An empty critical section
 */
_PLATFORM class sNoCriticalSection : private class_nocopy
{
public:
	/**
	 *
	 */
	sNoCriticalSection() {}
	
	/**
	 * Enter Critical Section
	 */
	inline void Enter() const {}

	/**
	 * Leave Critical Section
	 */
	inline void Leave() const {}
};


/**
 *	A critical section
 */
_PLATFORM class sCriticalSection : private class_nocopy
{
public:
	/**
	 *
	 */
	sCriticalSection();
	~sCriticalSection();

	/**
	 * Enter Critical Section
	 */
	void Enter() const;

	/**
	 * Leave Critical Section
	 */
	void Leave() const;
	
#ifdef _SPL_WIN32
	_PLATFORM mutable CRITICAL_SECTION	_cs;
#endif
	
#ifdef _SPL_MAC
	_PLATFORM mutable pthread_mutex_t	_mutex;
#endif	
};


/**
 *	Critical section
 */
#ifdef _SLIB_MT
	typedef sCriticalSection sCs;
#else
	typedef sNoCriticalSection sCs;
#endif

/**
 *	Auto critical section
 */
class sAutoCs : private class_nocopy
{
public:
	sAutoCs( const sCs& cs );
	~sAutoCs();
private:
	const sCs& _cs;
};

/************************************************************************/
/* Inline include                                                       */
/************************************************************************/
#include "s_system_mt_cs.inl"

/************************************************************************/
/* Platform inline include                                              */
/************************************************************************/

#ifdef _SPL_WIN32
	#include "s_system_mt_cs_win32.inl"
#endif

#ifdef _SPL_MAC
	#include "s_system_mt_cs_mac.inl"
#endif // _SPL_MAC

