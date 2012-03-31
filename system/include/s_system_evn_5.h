/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_evn_5.h
//  Created                 : 6 7 2007   1:31
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      void f( p1, p2, p3, p4, p5 )
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 *	sEvent5
 */
template< typename _P1, typename _P2, typename _P3, typename _P4, typename _P5 >
class sEvent5 : public sBaseEvent
{
public:
	sEvent5()
	{
		_function._s = NULL;
	}

	sEvent5( const sEvent5< _P1, _P2, _P3, _P4, _P5>& src ) : sBaseEvent( src )
	{
	}

	void operator = ( const sEvent5< _P1, _P2, _P3, _P4, _P5>& src )
	{
		sBaseEvent::operator = ( src );
	}

	/**
	 *	Call operator
	 */
	void operator()( _P1 p1, _P2 p2, _P3 p3, _P4 p4, _P5 p5 ) const
	{
		Call( p1, p2, p3, p4, p5 );
	}
private:
	typedef void ( sEvent::*_ObjCall )( _P1, _P2, _P3, _P4, _P5 );
	typedef void (*_StaticCall)( _P1, _P2, _P3, _P4, _P5 );

	/**
	 *	Call function
	 */
	void Call( _P1 p1, _P2 p2, _P3 p3, _P4 p4, _P5 p5 ) const
	{
		
		if( _function._s == NULL )
			return;

		if( _object == NULL )
		{
			_StaticCall sCall = reinterpret_cast<_StaticCall>( _function._s );
			sCall( p1, p2, p3, p4, p5 );
		}
		else
		{
			_ObjCall sCall = reinterpret_cast<_ObjCall>( _function._o );
			
			(*reinterpret_cast<sEvent*>( _object ).*sCall)( p1, p2, p3, p4, p5 );
		}
	}
};

/**
 *	Object event class
 */
template< typename _OBJ, typename _P1, typename _P2, typename _P3, typename _P4, typename _P5 >
class sEvent5Object : public sEvent5< _P1, _P2, _P3, _P4, _P5>
{
private:
	typedef sEvent5< _P1, _P2, _P3, _P4, _P5> _BaseClass;
public:
	sEvent5Object( _OBJ* pObj, void ( _OBJ::*pF )( _P1, _P2, _P3, _P4, _P5 ) )
	{
		_BaseClass::_object = reinterpret_cast< _OBJ* >( pObj );
		_BaseClass::_function._o = reinterpret_cast<sBaseEvent::ObjCall>( pF );
	}
};

/**
 *	Static event class
 */
template< typename _P1, typename _P2, typename _P3, typename _P4, typename _P5 >
class sEvent5Function : public System::Events::sEvent5< _P1, _P2, _P3, _P4, _P5>
{
private:
	typedef sEvent5< _P1, _P2, _P3, _P4, _P5> _BaseClass;
public:
	sEvent5Function( void (*pStaticCall)( _P1, _P2, _P3, _P4, _P5 ) )
	{
		_BaseClass::_object = NULL;
		_BaseClass::_function._s =  reinterpret_cast<sBaseEvent::StaticCall>( pStaticCall );
	}
};


template<typename _P1, typename _P2, typename _P3, typename _P4, typename _P5>
inline sEvent5<_P1,_P2,_P3,_P4,_P5> Event( void (*fn)( _P1, _P2, _P3, _P4, _P5 ) )
{
	return sEvent5Function<_P1, _P2, _P3, _P4, _P5>( fn );
}

template< typename _OBJ, typename _P1, typename _P2, typename _P3, typename _P4, typename _P5 >
inline sEvent5<_P1,_P2,_P3,_P4,_P5> Event( _OBJ* obj, void ( _OBJ::*fn )( _P1,_P2,_P3,_P4,_P5 ) )
{
	return sEvent5Object<_OBJ, _P1, _P2, _P3, _P4, _P5>( obj, fn );
}