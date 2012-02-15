/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_evn_4.h
//  Created                 : 6 7 2007   1:29
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      void f( p1, p2, p3, p4 )
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 *	sEvent4
 */
template< typename _P1, typename _P2, typename _P3, typename _P4 >
class sEvent4 : public sBaseEvent
{
public:
	sEvent4()
	{
		_function._s = NULL;
	}

	sEvent4( const sEvent4<_P1, _P2, _P3, _P4 >& src ) : sBaseEvent( src )
	{
	}

	void operator = ( const sEvent4<_P1, _P2, _P3, _P4 >& src )
	{
		sBaseEvent::operator = ( src );
	}

	/**
	 *	Call operator
	 */
	void operator()( _P1 p1, _P2 p2, _P3 p3, _P4 p4 ) const
	{
		Call( p1, p2, p3, p4 );
	}
private:
	typedef void ( sEvent::*_ObjCall )( _P1, _P2, _P3, _P4 );
	typedef void (*_StaticCall)( _P1, _P2, _P3, _P4 );

	/**
	 *	Call function
	 */
	void Call( _P1 p1, _P2 p2, _P3 p3, _P4 p4 ) const
	{
		
		if( _function._s == NULL )
			return;

		if( _object == NULL )
		{
			_StaticCall sCall = reinterpret_cast<_StaticCall>( _function._s );
			sCall( p1, p2, p3, p4 );
		}
		else
		{
			_ObjCall sCall = reinterpret_cast<_ObjCall>( _function._o );
			
			(*reinterpret_cast<sEvent*>( _object ).*sCall)( p1, p2, p3, p4 );
		}
	}
};


/**
 *	Object event class
 */
template< typename _OBJ, typename _P1, typename _P2, typename _P3, typename _P4 >
class sEvent4Object : public sEvent4<_P1, _P2, _P3, _P4 >
{
private:
	typedef sEvent4<_P1, _P2, _P3, _P4 > _BaseClass;
public:
	sEvent4Object( _OBJ* pObj, void ( _OBJ::*pF )( _P1, _P2, _P3, _P4 ) )
	{
		_BaseClass::_object = reinterpret_cast< _OBJ* >( pObj );
		_BaseClass::_function._o = reinterpret_cast<sBaseEvent::ObjCall>( pF );
	}
};

/**
 *	Static event class
 */
template< typename _P1, typename _P2, typename _P3, typename _P4 >
class sEvent4Function : public System::Events::sEvent4<_P1, _P2, _P3, _P4 >
{
private:
	typedef sEvent4<_P1, _P2, _P3, _P4 > _BaseClass;
public:
	sEvent4Function( void (*pStaticCall)( _P1, _P2, _P3, _P4 ) )
	{
		_BaseClass::_object = NULL;
		_BaseClass::_function._s = reinterpret_cast<sBaseEvent::StaticCall>( pStaticCall );
	}
};

template<typename _P1, typename _P2, typename _P3, typename _P4>
inline sEvent4<_P1,_P2,_P3,_P4> Event( void (*fn)( _P1, _P2, _P3, _P4 ) )
{
	return sEvent4Function<_P1, _P2, _P3, _P4>( fn );
}

template< typename _OBJ, typename _P1, typename _P2, typename _P3, typename _P4 >
inline sEvent4<_P1,_P2,_P3,_P4> Event( _OBJ* obj, void ( _OBJ::*fn )( _P1,_P2,_P3,_P4 ) )
{
	return sEvent4Object<_OBJ, _P1, _P2, _P3, _P4>( obj, fn );
}