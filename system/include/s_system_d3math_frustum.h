/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_frustum.h
//  Created                 : 22 1 2011   22:28
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
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
class d3Frustum
{
public:
	/**
	 *
	 */
	d3Frustum( );

	/**
	 *
	 */
	d3Frustum( const d3Frustum& f );

	/**
	 *
	 */
	void operator = ( const d3Frustum& f );
	
	/**
	 *
	 */
	void AddPlane( const d3Plane& p );

	/**
	 *
	 */
	void ClearPlanes();

	/**
	 *
	 */
	sBool Intersect( const d3AABBox& b ) const;

private:
	sVector<d3Plane>	_planes;
};

