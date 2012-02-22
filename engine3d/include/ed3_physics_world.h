////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_physics_world.h
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


#if !defined(_ED3_PHYSIC_WORLD_H_)
#define _ED3_PHYSIC_WORLD_H_

/**
 * Check configuration file include
 */
#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif


#ifdef ED3_ENGINE_USE_PHYSICS

/**
 * Bulet forward declarations
 */
class btCollisionDispatcher;
class btDefaultCollisionConfiguration;
class btBroadphaseInterface;
class btConstraintSolver;
class btDiscreteDynamicsWorld;

namespace Ed3
{

class phShape;	
class d3PhysicsWorld
{
public:
	d3PhysicsWorld();
	~d3PhysicsWorld();
	
	void SetGravityVector( const d3Vector& v );
	void AddShape( phShape* pShape )		{ _shapes.Add( pShape ); }

	void Initialize( ) throws_error;
	
	void Simulate( d3Float deltaTime );
private:
	btDefaultCollisionConfiguration*		_btCollisionConfiguration;
	btCollisionDispatcher*					_btCollisionDispatcher;
	btBroadphaseInterface*					_btBroadphaseInterface;
	btConstraintSolver*						_btSolver;
	btDiscreteDynamicsWorld*				_btDynamicsWorld;
	sVector<phShape*>						_shapes;
	
};
	
}

#endif // ED3_ENGINE_USE_PHYSICS

#endif // _ED3_PHYSIC_WORLD_H_
