////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_physics_shape.cpp
//  Created            : 20 1 2012   19:09
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//  Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////


#include "ed3afx.h"
#include "ed3_physics_shape.h"

#ifdef ED3_ENGINE_USE_PHYSICS

namespace Ed3
{

//------------------------------------------------------------------
/**
 * FactoryMap
 */
typedef sMap<sString, IphShapeFactory* > FactoryMap;
	
/**
 * phShapeFactory
 */
class phShapeFactory : public T::ClassFactoryById1< phShape, sString, FactoryMap, d3Object* >
{
public:
};
	
//------------------------------------------------------------------
phShapeFactory& g_phShapeFactory()
{
	static phShapeFactory factory;
	return factory;
}
		
//------------------------------------------------------------------
void phShape::Register( const sString& name, IphShapeFactory* pFactory )
{
		g_phShapeFactory().Register( name, pFactory );
}
	
//------------------------------------------------------------------
phShape* phShape::Create( const sString& name, d3Object* obj )
{
	return g_phShapeFactory().Create( name, obj );
}
		
	
}

#endif // ED3_ENGINE_USE_PHYSICS
