/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_font.cpp
//  Created                 : 22 1 2012   19:58
//  File path               : SLibF\render3d\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#include "rd3afx.h"
#include "rd3_types.h"
#include "rd3_font.h"

using namespace System;

namespace Rd3
{

////////////////////////////////////////////////////////////////////
// Font Class
////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------	
Font::Font( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName, ResourceType::E_FONT )
{
}
	
////////////////////////////////////////////////////////////////////
// Font Factory
////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
typedef sMap<sString, IFontFactory* > FactoryMap;

//------------------------------------------------------------------
class FontFactory : public T::ClassFactoryById2< Font, sString, FactoryMap, Render*, const sString& >
{
};
	
//------------------------------------------------------------------
FontFactory& g_FontFactory()
{
	static FontFactory factory;
	return factory;
}

//------------------------------------------------------------------
void Font::Register( const sString& name, IFontFactory* pFactory )
{
	g_FontFactory().Register( name, pFactory );
}	

//------------------------------------------------------------------
Font* Font::Create( const sString& name, Render* owner, const sString& objectName )
{
	__S_ASSERT( owner != NULL );
	
	return g_FontFactory().Create( name, owner, objectName );
}
	
}