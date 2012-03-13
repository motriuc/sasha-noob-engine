/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_plane.h
//  Created                 : 3 12 2007   20:01
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
class d3Plane
{
public:
	/**
	 *
	 */
	d3Plane();
	d3Plane( const d3Plane& p );
	d3Plane( const d3Vector& normal, d3Float d );
	d3Plane( const d3Vector& normal, const d3Point& origin );
	d3Plane( const d3Point& p1, const d3Point& p2, const d3Point& p3 );

	/**
	 *
	 */
	void operator = ( const d3Plane& p );
  
	/**
	 *
	 */
	void Project( d3Point& p, const d3Point& s ) const;
	d3Point Project( const d3Point& p ) const;

	/**
	 *
	 */
	d3Float Distance( d3Point& p ) const;

	/**
	 *
	 */
	const d3Vector& Normal() const;
	const d3Float GetD() const;

	/**
	 *
	 */
	sBool OnOpositeSide( const d3Point& p1, const d3Point& p2 ) const;
	
	/**
	 *
	 */
	sInt FirstOnSameSide( const d3Point& p, const d3Point* points, sInt count ) const;
	sInt FirstOnOpositeSide( const d3Point& p, const d3Point* points, sInt count ) const;

	/**
	 * returns true if point is in the plane
	 */
	sInt IsInPlane( const d3Point& p ) const;

	/**
	 * @return
	 *		-1 -> back
	 *		 0 -> middle
	 *		 1 -> front
	 */
	sInt Classify( const d3AABBox& b ) const;

	/**
	 * returns true 
	 * if plane intersects the line 
	 * point is the intersection point
	 */
	sBool Intersect( const d3Line& line, d3Point& point ) const;

	/**
	 * returns true if line intersects the plane
	 */
	sBool Intersect( const d3Line& line ) const;
private:
	d3Vector  _normal;
	d3Float   _d;         // d of plane equation: _normal * coord + _d = 0 
};
