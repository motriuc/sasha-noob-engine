/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_evn_b.h
//  Created                 : 6 7 2007   1:20
//  File path               : SLibF\system\Include
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

/**
 *	Base Event
 */
class sBaseEvent
{
public:
	inline sBaseEvent()
	{
	}

	inline sBaseEvent( const sBaseEvent& src ) :
		_object( src._object ),
		_function( src._function )
	{
	}

	inline void operator = ( const sBaseEvent& src )
	{
		_object = src._object;
		_function = src._function;
	}

	inline sBool IsNull() const
	{
		return _function._s == NULL;
	}

	inline sBool operator == ( const sBaseEvent& c )
	{
		return 
			_object == c._object &&
			_function._s == c._function._s;	
	}

protected:
	_PLATFORM typedef void ( sBaseEvent::*ObjCall )();
	_PLATFORM typedef void (*StaticCall)();

protected:
	_PLATFORM void*	_object;

	_PLATFORM union
	{
		ObjCall		_o;
		StaticCall	_s;
	} _function;
};

