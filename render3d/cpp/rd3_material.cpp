/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_material.cpp
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\cpp
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
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

#include "rd3afx.h"
#include "rd3_material.h"
#include "rd3_render.h"

using namespace System;

namespace Rd3
{

/**
 * FactoryMap
 */
typedef sMap<sString, IMaterialFactory* > FactoryMap;

/**
 * MaterialFactory
 */
class MaterialFactory : public T::ClassFactoryById2< Material, sString, FactoryMap, Render*, const sString& >
{
};
	
//------------------------------------------------------------------
MaterialFactory& g_MaterialFactory()
{
	static MaterialFactory factory;
	return factory;
}

//------------------------------------------------------------------
void Material::Register( const sString& name, IMaterialFactory* pFactory )
{
	g_MaterialFactory().Register( name, pFactory );
}	

//------------------------------------------------------------------
Material* Material::Create( const sString& name, Render* owner, const sString& objectName )
{
	__S_ASSERT( owner != NULL );
	
	return g_MaterialFactory().Create( name, owner, objectName );
}
	
//------------------------------------------------------------------
Material::Material( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName, ResourceType::E_MATERIAL )
{
	_quality = GetOwner()->GetDefaultMaterialQuality();	
}

//------------------------------------------------------------------

//------------------------------------------------------------------
	
}