////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_obj_class.h
//	Created            : 30 1 2012   19:09
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

#ifndef _ED3_OBJ_CLASS_H_
#define _ED3_OBJ_CLASS_H_

#ifndef _ED3_CONF_H_
#error ed3_conf.h must be included
#endif

#include "ed3_types.h"

namespace Ed3
{
	
/**
 * d3ObjectClassNames
 */ 
class d3ObjectClass
{
public:
	d3ObjectClass():
		_class( 0 )
	{
	}
	
	d3ObjectClass( SUINT64 v )
	{
		_class = v;
	}
	
	void Add( const d3ObjectClass& c )
	{
		_class = _class | c._class;
	}
	
	sBool Contain( const d3ObjectClass& c )	const
	{
		return ( _class & c._class ) > 0;
	}
	
	void SetAll()
	{
		_class = Limit::SUINT64::Max;
	}
private:
	SUINT64		_class;
};

/**
 * d3ObjectClassNames
 */
class d3ObjectClassNames
{
public:
	d3ObjectClassNames();
	
	d3ObjectClass GetClass( const sString& name ) const throws_error;
	
	d3ObjectClass GetClassFromString( const sString& str ) const throws_error;
private:
	mutable sMap<sString, SUINT64>		_classNames;
	mutable SUINT64						_lastClass;
};
	
}

#endif // _ED3_OBJ_CLASS_H_