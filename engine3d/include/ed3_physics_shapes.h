////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_physics_shapes.h
//	Created            : 20 1 2012   19:09
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
 * phStaticPlahe
 */
class phStaticPlahe : public phShape
{
private:
	typedef phShape _BaseClass;
public:
	phStaticPlahe( d3Object* owner ) :
		_BaseClass( owner ),
		_shape( NULL ),
		_rigidBody( NULL )
	{
	}

	~phStaticPlahe()
	{
		delete _shape;
		delete _rigidBody;
	}
	
	virtual void LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual void GetTransformation( d3Matrix& transformation );
protected:
	virtual btRigidBody* GetRigidBody( const btTransform& transform ) const;
	
private:
	btStaticPlaneShape*		_shape;
	mutable btRigidBody*	_rigidBody;
}; 	

/**
 * phSphere
 */
class phSphere : public phShape
{
private:
	typedef phShape _BaseClass;
public:
	phSphere( d3Object* owner ):
		_BaseClass( owner ),
		_shape( NULL ),
		_rigidBody( NULL )
	{
	}

	~phSphere()
	{
		delete _rigidBody;
		delete _shape;
	}
	
	virtual void LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual void GetTransformation( d3Matrix& transformation );
	
protected:
	virtual btRigidBody* GetRigidBody( const btTransform& transform ) const;
private:
	btSphereShape*			_shape;
	mutable btRigidBody*	_rigidBody;
	d3Float					_mass;
};
	
}

#endif // ED3_ENGINE_USE_PHYSICS

#endif // _ED3_PHYSIC_SHAPE_H_
