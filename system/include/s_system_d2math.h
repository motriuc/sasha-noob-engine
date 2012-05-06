/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d2math.h
//  Created                 : 4 02 2011   21:00
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

namespace d2Math
{	
	using namespace System::Types;
	using namespace System::Cnt;

	
	/**
	 * Forward declarations
	 */
	class d2Matrix;
	class d2Vector;
	class d2Plane;
	class d2Sphere;

	typedef d2Vector d2Point;

	#include "s_system_d2math_vector.h"
	#include "s_system_d2math_rect.h"
	#include "s_system_d2math_matrix.h"

	#include "s_system_d2math_vector.inl"
	#include "s_system_d2math_rect.inl"
	#include "s_system_d2math_matrix.inl"
}