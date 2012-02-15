////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_def.cpp
//	Created            : 16.3.2006   21:53
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\cpp
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
#include "rd3afx.h"
#include "rd3_def.h"

namespace Rd3
{

//-------------------------------------------------------------------	
Def::Def()
{
}

//-------------------------------------------------------------------
Def::Def( const Def& src )
{
	_defines = src._defines;
}

//-------------------------------------------------------------------	
void Def::operator = ( const Def& src )
{
	_defines = src._defines;
}

//-------------------------------------------------------------------	
sBool Def::IsOneDefined( const sStrings& d ) const
{
	for( sInt i = 0; i < d.Size(); i++ )
	{
		if( IsDefined( d[i]) )
			return sTrue;
	}
	return sFalse;
}

//-------------------------------------------------------------------	
sBool Def::IsAllDefined( const sStrings& d ) const
{
	for( sInt i = 0; i < d.Size(); i++ )
	{
		if( !IsDefined( d[i]) )
			return sFalse;
	}
	return sTrue;
}

//-------------------------------------------------------------------	
void Def::GetAllDefined( sStrings& d ) const
{
	Map::ConstIterator it = _defines.ConstBegin();
	
	while( it != _defines.ConstEnd() )
	{
		d.Add( it.Key() );
		++it;
	}
}

//-------------------------------------------------------------------	
void Def::Define( const sString& d )
{
	_defines[d] = _S("\b");
}

//-------------------------------------------------------------------	
void Def::Undef( const sString& d )
{
	_defines[d] = _S("");
}

//-------------------------------------------------------------------	
sBool Def::IsDefined( const sString& d ) const
{
	sString r;
	_defines.Lookup( d, r );
	return r.Length() > 0;
}

//-------------------------------------------------------------------	
const sString Def::operator[] ( sString d ) const
{
	sString r;
	_defines.Lookup( d, r );

	if( r != _S("\b") )
		return r;

	return _S("");
}

//-------------------------------------------------------------------	
void Def::Define( const sString& d, const sString& v )
{
	_defines[d] = v;
}

}