/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_evn_1.h
//  Created                 : 6 7 2007   1:24
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      void f( p1 )
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 *	sEvent1
 */
template< typename _P1>
class sEvent1 : public sBaseEvent
{
public:
	sEvent1()
	{
		_function._s = NULL;
	}

	sEvent1( const sEvent1<_P1>& src ) : sBaseEvent( src )
	{
	}

	void operator = ( const sEvent1<_P1>& src )
	{
		sBaseEvent::operator = ( src );
	}

	/**
	 *	Call operator
	 */
	void operator()( _P1 p1 ) const
	{
		Call( p1 );
	}
private:
	typedef void ( sEvent::*_ObjCall )( _P1 );
	typedef void (*_StaticCall)( _P1 );

	/**
	 *	Call function
	 */
	void Call( _P1 p1 ) const
	{
		if( _function._s == NULL )
			return;

		if( _object == NULL )
		{
			_StaticCall sCall = reinterpret_cast<_StaticCall>( _function._s );
			sCall( p1 );
		}
		else
		{
			_ObjCall sCall = reinterpret_cast<_ObjCall>( _function._o );
			
			(*reinterpret_cast<sEvent*>( _object ).*sCall)( p1 );
		}
	}
};


/**
 *	Object event class
 */
template< typename _OBJ, typename _P1 >
class sEvent1Object : public sEvent1< _P1 >
{
private:
	typedef sEvent1< _P1 > _BaseClass;
public:
	sEvent1Object( _OBJ* pObj, void ( _OBJ::*pF )( _P1 ) )
	{
		_BaseClass::_object = reinterpret_cast< _OBJ* >( pObj );
		_BaseClass::_function._o = reinterpret_cast<sBaseEvent::ObjCall>( pF );
	}
};

/**
 *	Static event class
 */
template< typename _P1 >
class sEvent1Function : public sEvent1< _P1 >
{
private:
	typedef sEvent1< _P1 > _BaseClass;
public:
	sEvent1Function( void (*pStaticCall)( _P1 ) )
	{
		_BaseClass::_object = NULL;
		_BaseClass::_function._s = reinterpret_cast<sBaseEvent::StaticCall>( pStaticCall );
	}
};

template<typename _P1>
inline sEvent1<_P1> Event( void (*fn)( _P1 ) )
{
	return sEvent1Function<_P1>( fn );
}

/**
 *
 */
template< typename _OBJ, typename _P1 >
inline sEvent1<_P1> Event( _OBJ* obj, void ( _OBJ::*fn )( _P1 ) )
{
	return sEvent1Object<_OBJ, _P1>( obj, fn );
}