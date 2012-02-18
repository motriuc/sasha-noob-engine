/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive.cpp
//	Created                 : 5 2 2012   0:05
//	File path               : SLibF\render3d\cpp\primitives
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
#include "rd3_primitive.h"

using namespace System;

namespace Rd3
{
	
/**
 * FactoryMap
 */
typedef sMap<sString, IPrimitive3DFactory* > FactoryMap;

/**
 * Primitive3DFactory
 */
class Primitive3DFactory : public T::ClassFactoryById< Primitive3D, sString, FactoryMap >
{
public:
	
};

/**
 *
 */
Primitive3DFactory& g_Primitive3DFactory()
{
	static Primitive3DFactory factory;
	return factory;
}

//--------------------------------------------------------------------------------------
void Primitive3D::Register( const sString& idname, IPrimitive3DFactory* pFactory )
{
	__S_ASSERT( pFactory != NULL );
	
	g_Primitive3DFactory().Register( idname, pFactory );
}

//--------------------------------------------------------------------------------------
Primitive3D* Primitive3D::Create( const sString& idname )
{
	return g_Primitive3DFactory().Create( idname );
}
	
}
