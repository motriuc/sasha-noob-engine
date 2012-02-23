////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_physics_world.cpp
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
#include "ed3_physics_world.h"
#include "ed3_physics_shape.h"
#include "ed3_object.h"
#include "rd3_perf_counters.h"

#ifdef ED3_ENGINE_USE_PHYSICS

#include "btBulletDynamicsCommon.h"

COUNTER_USE( rd3_render_time_physics )

namespace Ed3
{
//-----------------------------------------------------------------------
d3PhysicsWorld::d3PhysicsWorld() :
	_btCollisionConfiguration( NULL ),
	_btCollisionDispatcher( NULL ),
	_btBroadphaseInterface( NULL ),
	_btSolver( NULL ),
	_btDynamicsWorld( NULL )
{
	_btCollisionConfiguration = new btDefaultCollisionConfiguration();
	_btCollisionDispatcher = new btCollisionDispatcher( _btCollisionConfiguration );
	_btBroadphaseInterface = new btDbvtBroadphase();
	_btSolver = new btSequentialImpulseConstraintSolver();
	
	_btDynamicsWorld = new btDiscreteDynamicsWorld( 
		_btCollisionDispatcher,
		_btBroadphaseInterface,
		_btSolver,
		_btCollisionConfiguration
	);
}

//-----------------------------------------------------------------------
void d3PhysicsWorld::Simulate( d3Float deltaTime )
{
	COUNTER_TIME_START( rd3_render_time_physics );
	
	__S_ASSERT( _btDynamicsWorld != NULL );
	
	_btDynamicsWorld->stepSimulation( deltaTime );

	COUNTER_TIME_STOP( rd3_render_time_physics );
}	

//-----------------------------------------------------------------------
void d3PhysicsWorld::Initialize( ) throws_error
{
	d3Object* tranObj = NULL;
	btTransform transform;
	d3Vector scale;
	
	for( sInt i = 0; i < _shapes.Size(); ++i )
	{
		phShape& shape = *_shapes[i];
		
		if( shape.GetOwner() != tranObj )
		{
			tranObj = shape.GetOwner();
			
			d3Matrix matrix;
			
			shape.GetOwner()->GetAbsoluteTransformationMatrix( matrix );
			// support only translation for now
			d3Vector translation;
			matrix.GetTranslation( translation );
			
			transform.setIdentity();
			transform.setOrigin( btVector3( translation.x, translation.y, translation.z ) );
			
			matrix.GetScale( scale );
		}
		
		shape.SetLocalScaling( scale );
		
		btRigidBody* prBody = shape.GetRigidBody( transform );
		
		if( prBody != NULL )
			_btDynamicsWorld->addRigidBody( prBody );
	}
}
	
//-----------------------------------------------------------------------
void d3PhysicsWorld::SetGravityVector( const d3Vector& v )
{
	_btDynamicsWorld->setGravity( btVector3( v.x, v.y, v.z ) );
}
	
//-----------------------------------------------------------------------
d3PhysicsWorld::~d3PhysicsWorld()
{
	delete _btDynamicsWorld;
	delete _btSolver;
	delete _btBroadphaseInterface;
	delete _btCollisionDispatcher;
	delete _btCollisionConfiguration;
}
	
}

#endif // ED3_ENGINE_USE_PHYSICS
