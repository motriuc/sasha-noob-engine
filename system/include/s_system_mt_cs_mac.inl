/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_cs_mac.inl
//  Created                 : 31 3 2012 
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
	pthread_mutex_init( &_mutex, NULL );
}

inline sCriticalSection::~sCriticalSection()
{
	pthread_mutex_destroy( &_mutex );
}

inline void sCriticalSection::Enter() const
{
	pthread_mutex_lock( &_mutex );
}

inline void sCriticalSection::Leave() const
{
	pthread_mutex_unlock( &_mutex );
}
