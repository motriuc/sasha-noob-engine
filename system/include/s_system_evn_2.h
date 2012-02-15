/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_evn_2.h
//  Created                 : 6 7 2007   1:26
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      void f( p1, p2  )
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 *	sEvent2
 */
template< typename _P1, typename _P2 >
class sEvent2 : public sBaseEvent
{
public:
	sEvent2()
	{
		_function._s = NULL;
	}

	sEvent2( const sEvent2<_P1, _P2>& src ) : sBaseEvent( src )
	{
	}

	void operator = ( const sEvent2<_P1, _P2>& src )
	{
		sBaseEvent::operator = ( src );
	}

	/**
	 *	Call operator
	 */
	void operator()( _P1 p1, _P2 p2 ) const
	{
		Call( p1, p2 );
	}
private:
	typedef void ( sEvent::*_ObjCall )( _P1, _P2 );
	typedef void (*_StaticCall)( _P1, _P2 );

	/**
	 *	Call function
	 */
	void Call( _P1 p1, _P2 p2 ) const
	{
		
		if( _function._s == NULL )
			return;

		if( _object == NULL )
		{
			_StaticCall sCall = reinterpret_cast<_StaticCall>( _function._s );
			sCall( p1, p2 );
		}
		else
		{
			_ObjCall sCall = reinterpret_cast<_ObjCall>( _function._o );
			
			(*reinterpret_cast<sEvent*>( _object ).*sCall)( p1, p2 );
		}
	}
};


/**
 *	Object event class
 */
template< typename _OBJ, typename _P1, typename _P2 >
class sEvent2Object : public sEvent2<_P1, _P2>
{
private:
	typedef sEvent2<_P1, _P2> _BaseClass;
public:
	sEvent2Object( _OBJ* pObj, void ( _OBJ::*pF )( _P1, _P2 ) )
	{
		_BaseClass::_object = reinterpret_cast< _OBJ* >( pObj );
		_BaseClass::_function._o = reinterpret_cast<sBaseEvent::ObjCall>( pF );
	}
};

/**
 *	Static event class
 */
template< typename _P1, typename _P2 >
class sEvent2Function : public sEvent2<_P1, _P2>
{
private:
	typedef sEvent2<_P1, _P2> _BaseClass;
public:
	sEvent2Function( void (*pStaticCall)( _P1, _P2 ) )
	{
		_BaseClass::_object = NULL;
		_BaseClass::_function._s = reinterpret_cast<sBaseEvent::StaticCall>( pStaticCall );
	}
};

template<typename _P1, typename _P2>
inline sEvent2<_P1,_P2> Event( void (*fn)( _P1, _P2 ) )
{
	return sEvent2Function<_P1, _P2>( fn );
}

template< typename _OBJ, typename _P1, typename _P2 >
inline sEvent2<_P1,_P2> Event( _OBJ* obj, void ( _OBJ::*fn )( _P1,_P2 ) )
{
	return sEvent2Object<_OBJ, _P1, _P2>( obj, fn );
}