/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_obj_factory.cpp
//  Created             : 19 1 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\cpp
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////
#include "ed3afx.h"
#include "ed3_obj_factory.h"
#include "ed3_object.h"
#include "ed3_world.h"

namespace Ed3 
{
	
/**
 * FactoryMap
 */
typedef sMap<sString, Id3ObjectFactory* > FactoryMap;

/**
 * d3ObjectFactory
 */
class d3ObjectFactory : public T::ClassFactoryById< d3Object, sString, FactoryMap >
{
public:

};

/**
 *
 */
d3ObjectFactory& g_d3ObjectFactory()
{
	static d3ObjectFactory factory;
	return factory;
}

//--------------------------------------------------------------------------------------
void d3ObjectFactory_Register( const sString& idname, Id3ObjectFactory* pFactory )
{
	__S_ASSERT( pFactory != NULL );
	
	g_d3ObjectFactory().Register( idname, pFactory );
}

//--------------------------------------------------------------------------------------
d3Object* d3ObjectFactory_Create( const sString& idname )
{
	return g_d3ObjectFactory().Create( idname );
}

}
