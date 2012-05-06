/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_camera.cpp
//  Created                 : 22 1 2011   22:28
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#define _use_d3Math_

#include "s_system.h"

namespace System { namespace d3Math {
	
using namespace System::Types;

//-------------------------------------------------------------------		
d3Camera::d3Camera() :
	// View Params
	_pPosition ( 0.0f, 0.0f, 4.0f ),
	_vLookAt   ( 0.0f, 0.0f, -1.0f ),
	_vWorldUp  ( 0.0f, 1.0f, 0.0f ), 

	// Proj Params
	_fFov      ( FMath::fPi / 4 ),
#ifdef _SPL_MAC	
	_fAspect   ( 1.5f ),
#else	
	_fAspect   ( 1.0f ),
#endif

	_fNearPlane( 0.01f ),
	_fFarPlane ( 100.0f ),
	_bChanged( sTrue )
{
}

//-------------------------------------------------------------------		
void d3Camera::GetFrustum( d3Frustum& f ) const
{
	d3Float t  = FMath::Tan( _fFov / 2.0f );
	d3Float nh = _fNearPlane * t;
	d3Float nw = nh / _fAspect;

	const d3Vector& P = _pPosition;
	const d3Vector& U = _vWorldUp;

	d3Vector Z = -_vLookAt;
 
	d3Vector X;
	d3Vector::CrossProduct( X, U, Z );
	X = X.UnitVector();

	d3Vector Y;
	d3Vector::CrossProduct( Y, Z, X );

	d3Vector nc = P - Z * _fNearPlane;
	d3Vector fc = P - Z * _fFarPlane;

	f.AddPlane( d3Plane( -Z, nc ) );
	f.AddPlane( d3Plane( Z,  fc ) );

	d3Vector aux;
	d3Vector normal;
  
	aux = ( ( nc + Y * nh ) - P ).UnitVector();
	normal = aux ^ X;
	f.AddPlane( d3Plane( normal, nc + Y * nh ) );
  
	aux = ( ( nc - Y * nh ) - P ).UnitVector();
	normal = X ^ aux;
	f.AddPlane( d3Plane( normal, nc - Y * nh ) );

	aux = ( ( nc - X * nw ) - P ).UnitVector();
	normal = aux ^ Y;
	f.AddPlane( d3Plane( normal, nc - X * nw ) );

	aux = ( ( nc +  X * nw ) - P ).UnitVector();
	normal = Y ^ aux;
	f.AddPlane( d3Plane( normal , nc + X * nw ) );
}
	
//-------------------------------------------------------------------		
void d3Camera::SetCamera2D()
{
	_pPosition = d3Point( 0.5f, 0.5f, -1.2f );
	_vLookAt = d3Vector( 0.0f, 0.0f, 1.0f );
	_vWorldUp = d3Vector( 0.0f, -1.0f, 0.0f );
	
	_fFov = FMath::fPi / 4;
	_fAspect = 1.0f;
	_fNearPlane = 0.01f;
	_fFarPlane = 100.0f;
	_bChanged = sTrue;	
}	

	

}}
