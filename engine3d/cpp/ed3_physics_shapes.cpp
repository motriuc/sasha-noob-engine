////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_physics_shapes.cpp
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
#include "ed3_physics_shapes.h"

#ifdef ED3_ENGINE_USE_PHYSICS

namespace Ed3
{

AUTO_REGISTER_PH_SHAPE_FACTORY( _S("static.plane"), phStaticPlahe )
AUTO_REGISTER_PH_SHAPE_FACTORY( _S("sphere"), phSphere )

//----------------------------------------------------------------------	
inline void getTransformation( btRigidBody* pRigidBody, d3Matrix& m )
{
	const btTransform& tran = pRigidBody->getCenterOfMassTransform();
	tran.getOpenGLMatrix( m.v );
}
	
//----------------------------------------------------------------------	
void phStaticPlahe::GetTransformation( d3Matrix& transformation )
{
	__S_ASSERT( _rigidBody != NULL );
	getTransformation( _rigidBody, transformation );
}
	
//----------------------------------------------------------------------	
btRigidBody* phStaticPlahe::GetRigidBody( const btTransform& transform ) const
{
	if( _rigidBody == NULL )
	{		
		btVector3 inertia( 0.0f, 0.0f, 0.0f );
		btDefaultMotionState* motionState = new btDefaultMotionState( transform );
		btRigidBody::btRigidBodyConstructionInfo rbInfo( 0.0f, motionState, _shape, inertia );	
		_rigidBody = new btRigidBody( rbInfo );
	}
	return _rigidBody;
}
//----------------------------------------------------------------------	
void phStaticPlahe::LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	__S_ASSERT( _shape == NULL );
	
	d3Float x = element.GetAttributeValue( _S("normal.x"), 0.0f );
	d3Float y = element.GetAttributeValue( _S("normal.y"), 0.0f );
	d3Float z = element.GetAttributeValue( _S("normal.z"), 0.0f );
	
	d3Float c = element.GetAttributeValue( _S("const"), 0.0f );
	
	_shape = new btStaticPlaneShape( btVector3( x,y,z ), btScalar( c ) );
}

//----------------------------------------------------------------------	
void phSphere::GetTransformation( d3Matrix& transformation )
{
	__S_ASSERT( _rigidBody != NULL );
	getTransformation( _rigidBody, transformation );
}
	
//----------------------------------------------------------------------	
btRigidBody* phSphere::GetRigidBody( const btTransform& transform ) const
{
	if( _rigidBody == NULL )
	{		
		btVector3 inertia( 0.0f, 0.0f, 0.0f );
	
		if( _mass != 0.0 )
			_shape->calculateLocalInertia( _mass, inertia );
	
		btDefaultMotionState* motionState = new btDefaultMotionState( transform );
		btRigidBody::btRigidBodyConstructionInfo rbInfo( _mass, motionState, _shape, inertia );
		
		_rigidBody = new btRigidBody( rbInfo );
	}
	return _rigidBody;
}
	
//----------------------------------------------------------------------	
void phSphere::LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	__S_ASSERT( _shape == NULL );
	
	_mass = element.GetAttributeValue( _S("mass"), 0.0f );
	d3Float r = element.GetAttributeValue( _S("radius"), 0.0f );
	
	_shape = new btSphereShape( btScalar( r ) );
}
	
}

#endif // ED3_ENGINE_USE_PHYSICS
