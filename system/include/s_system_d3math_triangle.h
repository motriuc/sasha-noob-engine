/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_triangle.h
//  Created                 : 3 12 2007   19:49
//  File path               : E:\Sasha\C++\SLibF\system\Include
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

/**
 *
 */
class d3Triangle
{
public:
	
	/**
	 *
	 */
	d3Triangle( const d3Triangle& tr );

	/**
	 *
	 */
	void operator = ( const d3Triangle& tr );

	/**
	 *
	 */
	void GetAABB( d3AABBox& box );

	/**
	 *
	 */
public:
	d3Vector	_a;
	d3Vector	_b;
	d3Vector	_c;
};