////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_obj_class.cpp
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
#include "ed3afx.h"
#include "ed3_obj_class.h"

namespace Ed3
{

//----------------------------------------------------------------------
d3ObjectClass d3ObjectClassNames::GetClass( const sString& name ) const throws_error
{
	SUINT64 v;
	
	if( _classNames.Lookup( name, v ) )
		return d3ObjectClass( v );
	
	if( _classNames.Size() >= 64 )
		error_throw_arg( Errors::StringError )
			_S("To many object classes: " ) + name
		);
	
	_classNames.Add( name, _lastClass );
	v = _lastClass;
	
	_lastClass = _lastClass << 1;
	
	return d3ObjectClass( v );
}
	
//----------------------------------------------------------------------
d3ObjectClassNames::d3ObjectClassNames() :
	_lastClass( 1 )
{
	GetClass( _S("default") );
}
	
//----------------------------------------------------------------------
d3ObjectClass d3ObjectClassNames::GetClassFromString( const sString& str ) const throws_error
{
	d3ObjectClass cls;
	
	sString name;
	sInt from  = 0;
	
	while ( str.Split( _S('|'), from, name ) ) 
	{
		if( name.Length() > 0 )
			cls.Add( GetClass( name ) );
	}
	
	return cls;
}

	
	
}