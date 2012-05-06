/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math.h
//  Created                 : 1 12 2007   13:39
//  File path               : SLibF\system\include
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

namespace d3Math
{	
	using namespace System::Types;
	using namespace System::Cnt;

	
	/**
	 * Forward declarations
	 */
	class d3Matrix;
	class d3Vector;
	class d3Plane;
	class d3AABBox;
	class d3Sphere;
	class d3Quaternion;
	class d3LineSegment;
	class d3Line;

	typedef d3Vector d3Point;

	#include "s_system_d3math_vector.h"
	#include "s_system_d3math_matrix.h"
	#include "s_system_d3math_aabb.h"
	#include "s_system_d3math_sphere.h"
	#include "s_system_d3math_triangle.h"
	#include "s_system_d3math_plane.h"
	#include "s_system_d3math_frustum.h"
	#include "s_system_d3math_camera.h"
	#include "s_system_d3math_quaternion.h"
	#include "s_system_d3math_sline.h"
	#include "s_system_d3math_line.h"

	#include "s_system_d3math_int.h"

	#include "s_system_d3math_matrix.inl"
	#include "s_system_d3math_vector.inl"
	#include "s_system_d3math_aabb.inl"
	#include "s_system_d3math_sphere.inl"
	#include "s_system_d3math_triangle.inl"
	#include "s_system_d3math_plane.inl"
	#include "s_system_d3math_frustum.inl"

	#include "s_system_d3math_camera.inl"
	#include "s_system_d3math_quaternion.inl"
	#include "s_system_d3math_sline.inl"
	#include "s_system_d3math_line.inl"
}