
/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_aabb.cpp
//  Created                 : 1 12 2007   15:23
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//  Library                 : 
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
#define _use_d3Math_

#include "s_system.h"

namespace System
{
namespace d3Math
{
using namespace System::Types;

//--------------------------------------------------------------------		
void d3AABBox::Mul( d3AABBox& r, const d3AABBox& b, const d3Matrix& m )
{
	if( b.IsEmpty() )
	{
		r.SetEmpty();
		return;
	}

	m.GetTranslation( r._max );
	r._min = r._max;

	// 11
	if( m._11 >= 0.0f )
	{
		r._min.x += m._11 * b._min.x;
		r._max.x += m._11 * b._max.x;
	}
	else
	{
		r._min.x += m._11 * b._max.x;
		r._max.x += m._11 * b._min.x;
	}

	// 12
	if( m._12 >= 0.0f )
	{
		r._min.y += m._12 * b._min.x;
		r._max.y += m._12 * b._max.x;
	}
	else
	{
		r._min.y += m._12 * b._max.x;
		r._max.y += m._12 * b._min.x;
	}

	// 13
	if( m._13 >= 0.0f )
	{
		r._min.z += m._13 * b._min.x;
		r._max.z += m._13 * b._max.x;
	}
	else
	{
		r._min.z += m._13 * b._max.x;
		r._max.z += m._13 * b._min.x;
	}
 
	// 21
	if( m._21 >= 0.0f )
	{
		r._min.x += m._21 * b._min.y;
		r._max.x += m._21 * b._max.y;
	}
	else
	{
		r._min.x += m._21 * b._max.y;
		r._max.x += m._21 * b._min.y;
	}

	// 22
	if( m._22 >= 0.0f )
	{
		r._min.y += m._22 * b._min.y;
		r._max.y += m._22 * b._max.y;
	}
	else
	{
		r._min.y += m._22 * b._max.y;
		r._max.y += m._22 * b._min.y;
	}

	// 23
	if( m._23 >= 0.0f )
	{
		r._min.z += m._23 * b._min.y;
		r._max.z += m._23 * b._max.y;
	}
	else
	{
		r._min.z += m._23 * b._max.y;
		r._max.z += m._23 * b._min.y;
	}

	// 31
	if( m._31 >= 0.0f )
	{
		r._min.x += m._31 * b._min.z;
		r._max.x += m._31 * b._max.z;
	}
	else
	{
		r._min.x += m._31 * b._max.z;
		r._max.x += m._31 * b._min.z;
	}

	// 32
	if( m._32 >= 0.0f )
	{
		r._min.y += m._32 * b._min.z;
		r._max.y += m._32 * b._max.z;
	}
	else
	{
		r._min.y += m._32 * b._max.z;
		r._max.y += m._32 * b._min.z;
	}

	// 33
	if( m._33 >= 0.0f )
	{
		r._min.z += m._33 * b._min.z;
		r._max.z += m._33 * b._max.z;
	}
	else
	{
		r._min.z += m._33 * b._max.z;
		r._max.z += m._33 * b._min.z;
	}
}
	
}
}
