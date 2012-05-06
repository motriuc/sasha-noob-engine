/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_sphere.h
//  Created                 : 1 12 2007   15:45
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

/**
 * Sphere
 */
class d3Sphere
{
public:
	
	/**
	 *
	 */
	d3Sphere();
	d3Sphere( const d3Point& p, d3Float d );
	d3Sphere( const d3Sphere& s );

	/**
	 *
	 */
	void operator = ( const d3Sphere& s );
  
	/**
	 *	
	 */
	static void Mul( d3Sphere& r, const d3Sphere& a, const d3Matrix& m );

	/**
	 *
	 */
	void GetAABB( d3AABBox& box ) const;

	/**
	 *
	 */
	d3AABBox GetAABB() const;
public:
	d3Point	_center;
	d3Float	_d;
};
