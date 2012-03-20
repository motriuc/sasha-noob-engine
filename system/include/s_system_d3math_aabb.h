/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_aabb.h
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

/**
 * BA Box
 */
class d3AABBox
{
public:
	d3AABBox();
	d3AABBox( const d3Vector vmin, const d3Vector vmax );

	void SetEmpty();
	sBool IsEmpty() const;
	static d3AABBox GetEmpty(); 

	void GetSize( d3Vector& v ) const;
	d3Vector GetSize() const;

	d3Float GetSizeX() const;
	d3Float GetSizeY() const;
	d3Float GetSizeZ() const;

	/**
	 *	return AABB volume
	 */
	d3Float GetVolume() const;

	/**
	 *	Return center
	 */
	void GetCenter( d3Vector& v );

	/** 
	 *      6           7
	 *     /-----------/
	 * 2 / |      3  / |
	 * /---------- /   |        +Y
	 * |   |      |    |         |
	 * |   |      |    |         |       +Z
	 * |  4|-----------| 5       |     /
	 * |  /       |   /          |   /
	 * |/         | /            | /
	 * -----------/              |-------- +X
	 * 0          1
	 */
	void GetCorner( d3Point& v, sInt i ) const;
	d3Point GetCorner( sInt i ) const;

	void operator += ( const d3Point& v );
	void operator += ( const d3AABBox& b );

	/**
	 *	
	 */
	void operator *= ( const d3Matrix& m );
	d3AABBox operator * ( const d3Matrix& m ) const;

	/**
	 *
	 */
	void Add( const d3Point& v );
	void Add( const d3Point* v, sInt count );

	void Add( const d3AABBox& b );
	void Add( const d3AABBox* v, sInt count );

	/**
	 *
	 */
	void SplitByX( d3AABBox& a, d3AABBox& b ) const;
	void SplitByY( d3AABBox& a, d3AABBox& b ) const;
	void SplitByZ( d3AABBox& a, d3AABBox& b ) const;

	void SplitById( sInt id, d3AABBox& a, d3AABBox& b ) const;

	/**
	 * return closest point on this box to another point
	 */
	void ClosestTo( d3Vector& r, const d3Vector& a ) const;

	sBool Intersect( const d3AABBox& b ) const;
	sBool Intersect( const d3Point& v ) const;
  
	static void Mul( d3AABBox& r, const d3AABBox& b, const d3Matrix& m );

	/**
	 *	Intersect functions
	 */
	static sBool Intersect( const d3AABBox& a, const d3AABBox& b );
	static sBool Intersect( d3AABBox& r, const d3AABBox& a, const d3AABBox& b );
	static sBool Intersect( const d3AABBox& b, const d3Point& v );
	static sBool Intersect( const d3AABBox& b, const d3Sphere& s );
public:
	d3Vector  _min;
	d3Vector  _max;
};
