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

AUTO_REGISTER_PH_SHAPE_FACTORY( _S("static.plane"), phStaticPlane )
AUTO_REGISTER_PH_SHAPE_FACTORY( _S("sphere"), phSphere )

//----------------------------------------------------------------------	
inline void getTransformation( btRigidBody* pRigidBody, d3Matrix& m )
{
	const btTransform& tran = pRigidBody->getCenterOfMassTransform();
	tran.getOpenGLMatrix( m.v );
}

/***********************************************************************/
/* phStaticPlahe                                                       */
/***********************************************************************/
	
//----------------------------------------------------------------------	
phRigidBodyShape::phRigidBodyShape( d3Object* owner ) :
	_BaseClass( owner ),
	_rigidBody( NULL ),
	_shape( NULL )
{	
}
	
//----------------------------------------------------------------------	
phRigidBodyShape::~phRigidBodyShape()
{
	delete _shape;
	delete _rigidBody;
}

//----------------------------------------------------------------------	
void phRigidBodyShape::SetScaling( const d3Vector& scaling )
{
	__S_ASSERT( _shape != NULL );
	_shape->setLocalScaling( btVector3( scaling.x, scaling.y, scaling.z )); 	
}

//----------------------------------------------------------------------	
void phRigidBodyShape::Move( const d3Vector& v )
{
	__S_ASSERT( _rigidBody != NULL );
	
	_rigidBody->translate( btVector3( v.x, v.y, v.z ) );
}

//----------------------------------------------------------------------	
void phRigidBodyShape::GetTransformation( d3Matrix& transformation )
{
	__S_ASSERT( _rigidBody != NULL );
	__S_ASSERT( _shape != NULL );
	
	d3Matrix m;
	getTransformation( _rigidBody, m );
	
	const btVector3& v = _shape->getLocalScaling();
	
	transformation.SetScale( v.getX(), v.getY(), v.getZ() );
	transformation *= m;	
}

//----------------------------------------------------------------------	
void phRigidBodyShape::MakeRigidBody( d3Float mass )
{
	__S_ASSERT( _rigidBody == NULL );
	__S_ASSERT( _shape != NULL );
	
	btVector3 inertia( 0.0f, 0.0f, 0.0f );

	if( mass != 0.0 )
		_shape->calculateLocalInertia( mass, inertia );
	
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, NULL, _shape, inertia );
	_rigidBody = new btRigidBody( rbInfo );	
}
	
/***********************************************************************/
/* phStaticPlane                                                       */
/***********************************************************************/

//----------------------------------------------------------------------	
phStaticPlane::phStaticPlane( d3Object* owner ) :
	_BaseClass( owner )
{
}

//----------------------------------------------------------------------	
phStaticPlane::phStaticPlane( d3Object* owner, const d3Plane& plane ) :
	_BaseClass( owner )
{
	const d3Vector& normal = plane.Normal();
	
	_shape = new btStaticPlaneShape(
			btVector3( normal.x,normal.y,normal.z ),
			btScalar( plane.GetD() )
	);
	
	MakeRigidBody( 0.0f );
}
	
//----------------------------------------------------------------------	
void phStaticPlane::LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	__S_ASSERT( _shape == NULL );
	
	d3Float x = element.GetAttributeValue( _S("normal.x"), 0.0f );
	d3Float y = element.GetAttributeValue( _S("normal.y"), 0.0f );
	d3Float z = element.GetAttributeValue( _S("normal.z"), 0.0f );
	
	d3Float c = element.GetAttributeValue( _S("const"), 0.0f );
	
	_shape = new btStaticPlaneShape( btVector3( x,y,z ), btScalar( c ) );
	
	MakeRigidBody( 0.0f );
}

/***********************************************************************/
/* phSphere                                                            */
/***********************************************************************/

//----------------------------------------------------------------------
phSphere::phSphere( d3Object* owner ):
	_BaseClass( owner )
{
}

//----------------------------------------------------------------------
phSphere::phSphere( d3Object* owner, d3Float radius, d3Float mass ) :
	_BaseClass( owner )
{
	_shape = new btSphereShape( btScalar( radius ) );
	
	MakeRigidBody( 0.0f );
}

//----------------------------------------------------------------------	
void phSphere::LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	__S_ASSERT( _shape == NULL );
	
	d3Float mass = element.GetAttributeValue( _S("mass"), 0.0f );
	d3Float r = element.GetAttributeValue( _S("radius"), 0.0f );
	
	_shape = new btSphereShape( btScalar( r ) );

	MakeRigidBody( mass );
}

}

#endif // ED3_ENGINE_USE_PHYSICS
