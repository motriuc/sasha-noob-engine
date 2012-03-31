/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_cs_win32.inl
//  Created                 : 23 6 2007   22:59
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

inline sCriticalSection::sCriticalSection()
{
	InitializeCriticalSection( &_cs );
}

inline sCriticalSection::~sCriticalSection()
{
	DeleteCriticalSection( &_cs );
}

inline void sCriticalSection::Enter() const
{
	EnterCriticalSection( &_cs );
}

inline void sCriticalSection::Leave() const
{
	LeaveCriticalSection( &_cs );
}
