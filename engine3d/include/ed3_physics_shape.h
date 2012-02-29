////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_physics_shape.h
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


#if !defined(_ED3_PHYSIC_SHAPE_H_)
#define _ED3_PHYSIC_SHAPE_H_

/**
 * Check configuration file include
 */
#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif

#ifdef ED3_ENGINE_USE_PHYSICS

class btRigidBody;
class btTransform;

namespace Ed3
{

/**
 * forward declarations
 */
class d3Object;
class phShape;
class LoadDataParams;
	
typedef System::T::IClassFactory1<phShape, d3Object*> IphShapeFactory;
	
/**
 * phShape
 */
class phShape : private class_nocopy
{
protected:
	phShape( d3Object* owner );
	
public:	
	virtual ~phShape();
	
	/**
	 * returns shape owner
	 */
	d3Object* GetOwner();
	
	/**
	 * loads the object from xml
	 */
	virtual void LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error = 0;
	
	/**
	 * returns current shape transformation
	 */
	virtual void GetTransformation( d3Matrix& transformation ) = 0;
	
	/**
	 * Sets object scaling
	 */
	virtual void SetScaling( const d3Vector& scaling ) = 0;
	
	/**
	 * Moves the object
	 */
	virtual void Move( const d3Vector& v ) = 0;
public:	
	/**
	 *
	 */
	static void Register( const sString& name, IphShapeFactory* pFactory );
	
	/**
	 *
	 */
	static phShape* Create( const sString& name, d3Object* obj );
	
protected:	
	virtual btRigidBody* GetRigidBody() const = 0;	

private:
	d3Object*	_owner;
	
	friend class d3PhysicsWorld;
};
	
#include "ed3_physics_shape.inl"
	
}

#define AUTO_REGISTER_PH_SHAPE_FACTORY( _name, _class ) \
class Factory_Register_ph_shape_##_class \
{ \
public: \
	Factory_Register_ph_shape_##_class( ) \
	{ \
		static System::T::ClassFactory1<_class, phShape, d3Object*> obj; \
		Ed3::phShape::Register( _name, &obj ); \
	} \
}; \
Factory_Register_ph_shape_##_class register_ph_shape_##_class;


#endif // ED3_ENGINE_USE_PHYSICS

#endif // _ED3_PHYSIC_SHAPE_H_
