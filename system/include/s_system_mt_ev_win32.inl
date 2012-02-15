/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_ev_win32.inl
//  Created                 : 9 7 2007   16:00
//  File path               : SLibF\system\include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//  Library                 : 
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

inline sEvent::sEvent( sBool bInitState, sBool bManual ) :
	_hEvent ( ::CreateEvent( NULL, bManual, bInitState, NULL ) )
{
}

inline sEvent::~sEvent()
{
	::CloseHandle( _hEvent );
}

inline void sEvent::Set() const
{
	::SetEvent( _hEvent );
}

inline void sEvent::UnSet() const
{
	::ResetEvent( _hEvent );
}

inline sBool sEvent::Wait( sInt time ) const
{
	return 
		::WaitForSingleObject( _hEvent, time < 0 ? INFINITE : time ) 
		== WAIT_OBJECT_0;
}

inline HANDLE sEvent::GetHandle() const
{
	return _hEvent;
}

