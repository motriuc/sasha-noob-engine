/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive_sphere.h
//	Created                 : 5 2 2012   0:05
//	File path               : SLibF\render3d\include\primitives
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#include "rd3afx.h"
#include "rd3_primitive_torus.h"

using namespace System;
using namespace System::d3Math;
using namespace System::d2Math;

namespace Rd3
{
//------------------------------------------------------------------
PrimitiveTorus::PrimitiveTorus( d3Float radius, d3Float tubeRadius, sInt ns, sInt nt ) :
	_radius( radius ),
	_tubeRadius( tubeRadius ),
	_ns( ns ),
	_nt( nt )
{
}

//------------------------------------------------------------------
void PrimitiveTorus::GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& tx ) const
{
	for( sInt s = 0; s <= _ns; s++)
	{
		sFloat theta = s * FMath::f2Pi / _ns;
		
		for (int t = 0; t <= _nt; t++)
		{
			sFloat phi = t * FMath::f2Pi / _nt;
			
			sFloat sinTheta =	FMath::Sin( theta );
			sFloat sinPhi =		FMath::Sin( phi );
			sFloat cosTheta =	FMath::Cos( theta );
			sFloat cosPhi =		FMath::Cos( phi );
			
			sFloat x = sinTheta * ( _radius + _tubeRadius * sinPhi );
			sFloat y =						- _tubeRadius * cosPhi;
			sFloat z = cosTheta * ( _radius + _tubeRadius * sinPhi );
			
			sFloat nx = sinTheta * sinPhi;
			sFloat ny = -cosPhi;
			sFloat nz = cosTheta * sinPhi;
			
			sFloat u = 1.0f * s / _ns;
			sFloat v = 1.0f - ( 1.0f * t / _nt );
			
			p.Add( d3Vector( x, y, z ) );
			n.Add( d3Vector( nx, ny, nz ) );
			tx.Add( d2Vector( u, v ) );
		}
	}
	
	for( sInt s = 0; s < _ns; s++ ) 
	{
		for( sInt t = 0; t < _nt; t++ )
		{
			sInt first = (s * (_nt + 1)) + t;
			sInt second = first + (_nt + 1);
			sInt third = first + 1;
			sInt fourth = second + 1;
			
			i.Add( first, second, third );
			i.Add( second, fourth, third );			
		}
	}
}
	
//------------------------------------------------------------------	
sInt PrimitiveTorus::EstimateVertexCount() const
{
	return (_nt + 1) * (_ns + 1);
}
	
//------------------------------------------------------------------	
sInt PrimitiveTorus::EstimateIndexCount() const
{
	return _nt * _ns * 6;
}
	
	
}