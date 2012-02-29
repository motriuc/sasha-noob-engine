////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_physics_shapes.h
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


#if !defined(_ED3_PHYSIC_SHAPES_H_)
#define _ED3_PHYSIC_SHAPES_H_

/**
 * Check configuration file include
 */
#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif

#ifdef ED3_ENGINE_USE_PHYSICS

#include "ed3_physics_shape.h"
#include "btBulletDynamicsCommon.h"

namespace Ed3
{

/**
 * base class for bullet shapes
 */
class phRigidBodyShape : public phShape
{
private:
	typedef phShape _BaseClass;
	
protected:
	phRigidBodyShape( d3Object* owner );
	
public:	
	virtual ~phRigidBodyShape();
	
	virtual void SetScaling( const d3Vector& scaling );
	virtual void Move( const d3Vector& v );
	
	virtual void GetTransformation( d3Matrix& transformation );
protected:
	btRigidBody*		_rigidBody;
	btCollisionShape*	_shape;
	
	void MakeRigidBody( d3Float mass );
	virtual btRigidBody* GetRigidBody() const { return _rigidBody; }
};
	
/**
 * phStaticPlane
 */
class phStaticPlane : public phRigidBodyShape
{
private:
	typedef phRigidBodyShape _BaseClass;
public:
	/**
	 *
	 */
	phStaticPlane( d3Object* owner );
	phStaticPlane( d3Object* owner, const d3Plane& plane );
	
	/**
	 *
	 */
	virtual void LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	
};

/**
 * phSphere
 */
class phSphere : public phRigidBodyShape
{
private:
	typedef phRigidBodyShape _BaseClass;
public:
	/**
	 *
	 */
	phSphere( d3Object* owner );
	phSphere( d3Object* owner, d3Float radius, d3Float mass );
		
	virtual void LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
};

}

#endif // ED3_ENGINE_USE_PHYSICS

#endif // _ED3_PHYSIC_SHAPE_H_
