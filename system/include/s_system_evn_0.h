/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_evn_0.h
//  Created                 : 6 7 2007   1:22
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      void f()
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 *	sEvent
 */
class sEvent : public sBaseEvent
{
public:
	inline sEvent()
	{
		_function._s = NULL;
	}

	inline sEvent( const sEvent& src ) : sBaseEvent( src )
	{
	}

	inline void operator = ( const sEvent& src )
	{
		sBaseEvent::operator = ( src );
	}

	/**
	 *	Call operator
	 */
	inline void operator()() const
	{
		Call();
	}
private:
	typedef void ( sEvent::*_ObjCall )();
	typedef void (*_StaticCall)();

	/**
	 *	Call function
	 */
	inline void Call() const
	{
		
		if( _function._s == NULL )
			return;

		if( _object == NULL )
		{
			_StaticCall sCall = reinterpret_cast<_StaticCall>( _function._s );
			sCall();
		}
		else
		{
			_ObjCall sCall = reinterpret_cast<_ObjCall>( _function._o );
			
			(*reinterpret_cast<sEvent*>( _object ).*sCall)();
		}
	}

};


/**
 *	Object event class
 */
template< typename _OBJ>
class sEventObject : public sEvent
{
public:
	sEventObject( _OBJ* pObj, void ( _OBJ::*pF )() )
	{
		sEvent::_object = reinterpret_cast< _OBJ* >( pObj );
		sEvent::_function._o = reinterpret_cast<sBaseEvent::ObjCall>( pF );
	}
};

/**
 *	Static event class
 */
class sEventFunction : public sEvent
{
public:
	sEventFunction( void (*pStaticCall)() )
	{
		sEvent::_object = NULL;
		sEvent::_function._s = reinterpret_cast<sBaseEvent::StaticCall>( pStaticCall );
	}
};

/**
 *
 */
inline sEvent Event( void (*fn)() )
{
	return sEventFunction( fn );
}

/**
 *
 */
template< typename _OBJ >
inline sEvent Event( _OBJ* obj, void ( _OBJ::*fn )() )
{
	return sEventObject<_OBJ>( obj, fn );
}