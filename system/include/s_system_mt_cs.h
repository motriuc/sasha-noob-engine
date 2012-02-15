/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_cs.h
//	Created                 : 23 6 2007   22:54
//	File path               : SLibF\system\include
//	Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////
#ifndef _SYSTEM_MT_CS_INC_
#define _SYSTEM_MT_CS_INC_

/**
 *	An empty critical section
 */
_PLATFORM class sNoCriticalSection
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
private:
	sNoCriticalSection( const sNoCriticalSection& );
	sNoCriticalSection& operator=( const sNoCriticalSection& );
};


/**
 *	A critical section
 */
_PLATFORM class sCriticalSection
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
private:
	sCriticalSection( const sCriticalSection& );
	sCriticalSection& operator=( const sCriticalSection& );
	
#ifdef _SPL_WIN32
	_PLATFORM mutable CRITICAL_SECTION	_cs;
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
class sAutoCs
{
public:
	sAutoCs( const sCs& cs );
	~sAutoCs();
private:
	sAutoCs( const sAutoCs& );
	void operator = ( const sAutoCs& );
private:
	const sCs& _cs;
};

/************************************************************************/
/* Inline include                                                       */
/************************************************************************/
#include "s_system_mt_cs.inl"

/************************************************************************/
/* Platform include                                                     */
/************************************************************************/

#ifdef _SPL_WIN32
	#include "s_system_mt_cs_win32.inl"
#endif

#endif // _SYSTEM_MT_CS_INC_
