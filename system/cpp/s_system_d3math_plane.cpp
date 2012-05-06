/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_plane.cpp
//  Created                 : 3 12 2007   20:17
//  File path               : SLibF\system\Cpp
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

namespace System
{
namespace d3Math
{
using namespace System::Types;

//-------------------------------------------------------------------	
sInt d3Plane::FirstOnSameSide( const d3Point& p, const d3Point* points, sInt count ) const
{
	d3Float pt1 = d3Vector::DotProduct( _normal, p );

	for( sInt i = 0; i < count; i++ )
	{
		d3Float pt2 = d3Vector::DotProduct( _normal, points[i] );

		if(  ( pt1 < 0.0f && pt2 < 0.0f ) || ( pt1 >= 0.0f && pt2 >= 0.0f )	)
			return i;
	}

	return -1;
}

//-------------------------------------------------------------------	
sInt d3Plane::FirstOnOpositeSide( const d3Point& p, const d3Point* points, sInt count ) const
{
	d3Float pt1 = d3Vector::DotProduct( _normal, p );

	for( sInt i = 0; i < count; i++ )
	{
		d3Float pt2 = d3Vector::DotProduct( _normal, points[i] );

		if(  ( pt1 < 0.0f && pt2 > 0.0f ) || ( pt1 > 0.0f && pt2 < 0.0f ) )
			return i;
	}

	return -1;
}

//-------------------------------------------------------------------	
sInt d3Plane::Classify( const d3AABBox& b ) const
{
	float minD, maxD;

	if( _normal.x > 0.0f )
	{
		minD = _normal.x * b._min.x;
		maxD = _normal.x * b._max.x;
	}
	else
	{
		minD = _normal.x * b._max.x;
		maxD = _normal.x * b._min.x;
	}

	if( _normal.y > 0.0f )
	{
		minD += _normal.y * b._min.y;
		maxD += _normal.y * b._max.y;
	}
	else
	{
		minD += _normal.y * b._max.y;
		maxD += _normal.y * b._min.y;
	}

	if( _normal.z > 0.0f )
	{
		minD += _normal.z * b._min.z;
		maxD += _normal.z * b._max.z;
	}
	else
	{
		minD += _normal.z * b._max.z;
		maxD += _normal.z * b._min.z;
	}

	if( minD >= _d )
		return 1;

	if( maxD <= _d )
		return -1;

	return 0;
}




}
}