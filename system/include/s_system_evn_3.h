/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_evn_3.h
//  Created                 : 6 7 2007   1:28
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      void f( p1, p2, p3 )
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 *	sEvent3
 */
template< typename _P1, typename _P2, typename _P3 >
class sEvent3 : public sBaseEvent
{
public:
	sEvent3()
	{
		_function._s = NULL;
	}

	sEvent3( const sEvent3<_P1, _P2, _P3>& src ) : sBaseEvent( src )
	{
	}

	void operator = ( const sEvent3<_P1, _P2, _P3>& src )
	{
		sBaseEvent::operator = ( src );
	}

	/**
	 *	Call operator
	 */
	void operator()( _P1 p1, _P2 p2, _P3 p3 ) const
	{
		Call( p1, p2, p3 );
	}
private:
	typedef void ( sEvent::*_ObjCall )( _P1, _P2, _P3 );
	typedef void (*_StaticCall)( _P1, _P2, _P3 );

	/**
	 *	Call function
	 */
	void Call( _P1 p1, _P2 p2, _P3 p3 ) const
	{
		
		if( _function._s == NULL )
			return;

		if( _object == NULL )
		{
			_StaticCall sCall = reinterpret_cast<_StaticCall>( _function._s );
			sCall( p1, p2, p3 );
		}
		else
		{
			_ObjCall sCall = reinterpret_cast<_ObjCall>( _function._o );
			
			(*reinterpret_cast<sEvent*>( _object ).*sCall)( p1, p2, p3 );
		}
	}
};


/**
 *	Object event class
 */
template< typename _OBJ, typename _P1, typename _P2, typename _P3 >
class sEvent3Object : public sEvent3<_P1, _P2, _P3>
{
private:
	typedef sEvent3<_P1, _P2, _P3> _BaseClass;
public:
	sEvent3Object( _OBJ* pObj, void ( _OBJ::*pF )( _P1, _P2, _P3 ) )
	{
		_BaseClass::_object = reinterpret_cast< _OBJ* >( pObj );
		_BaseClass::_function._o = reinterpret_cast<sBaseEvent::ObjCall>( pF );
	}
};

/**
 *	Static event class
 */
template< typename _P1, typename _P2, typename _P3 >
class sEvent3Function : public System::Events::sEvent3<_P1, _P2, _P3>
{
private:
	typedef sEvent3<_P1, _P2, _P3> _BaseClass;
public:
	sEvent3Function( void (*pStaticCall)( _P1, _P2, _P3 ) )
	{
		_BaseClass::_object = NULL;
		_BaseClass::_function._s = reinterpret_cast<sBaseEvent::StaticCall>( pStaticCall );
	}
};

template<typename _P1, typename _P2, typename _P3>
inline sEvent3<_P1,_P2,_P3> Event( void (*fn)( _P1, _P2, _P3 ) )
{
	return sEvent3Function<_P1, _P2, _P3>( fn );
}

template< typename _OBJ, typename _P1, typename _P2, typename _P3 >
inline sEvent3<_P1,_P2,_P3> Event( _OBJ* obj, void ( _OBJ::*fn )( _P1,_P2,_P3 ) )
{
	return sEvent3Object<_OBJ, _P1, _P2, _P3>( obj, fn );
}