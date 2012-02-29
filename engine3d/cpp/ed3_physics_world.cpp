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
	_btDynamicsWorld( NULL ),
	_init( sFalse )
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
	
	d3Vector scale;
	d3Vector translation;
	
	for( sInt i = 0; i < _shapes.Size(); ++i )
	{
		phShape& shape = *_shapes[i];
		
		if( shape.GetOwner() != tranObj )
		{
			tranObj = shape.GetOwner();
			
			d3Matrix matrix;			
			tranObj->GetAbsoluteTransformationMatrix( matrix );
			
			matrix.GetTranslation( translation );			
			matrix.GetScale( scale );
		}
		
		shape.SetScaling( scale );
		shape.Move( translation );
		
		btRigidBody* prBody = shape.GetRigidBody();
		
		if( prBody != NULL )
			_btDynamicsWorld->addRigidBody( prBody );
	}
	
	_init = sTrue;
}

//-----------------------------------------------------------------------
phShape* d3PhysicsWorld::GetShape( sInt id )
{
	if( id < 0 || id >= _shapes.Size() )
		return NULL;
	
	return _shapes[id];
}
	
//-----------------------------------------------------------------------
sInt d3PhysicsWorld::AddShape( phShape* pShape )
{
	__S_ASSERT( pShape != NULL );
			   
	sInt idobj = _shapes.Add( pShape );
	
	if( _init )
	{
		d3Vector scale;
		d3Vector translation;
		
		d3Matrix matrix;			
		pShape->GetOwner()->GetAbsoluteTransformationMatrix( matrix );
		
		matrix.GetTranslation( translation );			
		matrix.GetScale( scale );

		pShape->SetScaling( scale );
		pShape->Move( translation );
		
		btRigidBody* prBody = pShape->GetRigidBody();
		
		if( prBody != NULL )
			_btDynamicsWorld->addRigidBody( prBody );
	}
	
	return idobj;
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
