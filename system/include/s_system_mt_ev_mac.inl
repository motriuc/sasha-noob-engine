/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mt_ev_mac.inl
//  Created                 : 31 3 2012
//  File path               : SLibF\system\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
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
	_manual( bManual ),
	_state( bInitState )
{
	pthread_cond_init( &_cond, NULL );
	pthread_mutex_init( &_mutex, NULL );
	
}

inline sEvent::~sEvent()
{
	pthread_mutex_destroy( &_mutex );
	pthread_cond_destroy( &_cond );
}

inline void sEvent::Set() const
{
	pthread_mutex_lock( &_mutex );
	if( _state != sTrue )
	{
		_state = sTrue;
		pthread_cond_broadcast( &_cond );
	}
	pthread_mutex_lock( &_mutex );	
}

inline void sEvent::UnSet() const
{
	pthread_mutex_lock( &_mutex );
	if( _state != sFalse )
	{
		_state = sFalse;
		pthread_cond_broadcast( &_cond );
	}
	pthread_mutex_lock( &_mutex );
}

inline sBool sEvent::Wait( sInt time ) const
{
	sBool rv = sFalse;

	pthread_mutex_lock( &_mutex );
	if( _state )
	{
		rv = sTrue;
		if( !_manual )
			_state = sFalse;
	}
	else
	{
		if( time > 0 )
		{
			struct timespec timeout;
			timeout.tv_sec = time / 1000;
			timeout.tv_nsec = ( time % 1000 ) * 1000000;
		
			pthread_cond_timedwait( &_cond, &_mutex, &timeout );
		}
		else if( time < 0 )
		{
			pthread_cond_wait( &_cond, &_mutex );
		}
		
		if( _state )
		{
			rv = sTrue;
			if( !_manual )
				_state = sFalse;
		}
	}
	pthread_mutex_lock( &_mutex );

	return rv;
}


