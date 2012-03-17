/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_camera.h
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
class d3Camera 
{
public:
	d3Camera();

	/**
	 *
	 */
	void GetView( d3Matrix& view ) const;
	void GetProjection( d3Matrix& prj ) const;
	void GetFrustum( d3Frustum& f ) const;

	/**
	 * returns a ray for camera view point
	 */
	void GetRay( const d3Point& point, d3LineSegment& ray ) const;

	/**
	 * Move transformations
	 */
	void Move( const d3Vector& v );
	void MoveForward( d3Float f );
	void MoveUp( d3Float f );
	void MoveLeft( d3Float f );

	/**
	 * Rotate on Left Up axis
	 */
	void RotateLeft( d3Float f );
	
	/**
	 * 
	 */
	void RotateUp( d3Float f );
  
	/**
	 * 
	 */
	void RotateView( d3Float f );

	/**
	 * 
	 */
	void SetPosition( const d3Point& p );

	/**
	 *
	 */
	void SetLookAt( const d3Vector& v );
	
	/**
	 *
	 */
	void SetUp( const d3Vector& v );
	
	/**
	 * Projection
	 */
	void SetFov( d3Float v );
	void SetAspect( d3Float v );
	void SetNearPlane( d3Float v );
	void SetFarPlane( d3Float v );
	
	/**
	 * Get Projection data
	 */
	d3Float GetNearPlane() const;
	d3Float GetFarPlane() const;
	d3Float GetAspect() const;
	d3Float GetFov() const;

	/**
	 *
	 */
	d3Camera( const d3Camera& src );
	void operator = ( const d3Camera& src );

	/**
	 * 
	 */ 
	const d3Point& GetPosition() const;
  
	/**
	 *
	 */
	sBool ChangedFromLastCommit() const;

	/**
	 * 
	 */
	void CommitChanges() const;
	
	/**
	 *
	 */
	void SetCamera2D();

	/**
	 *
	 */
	d3Vector GetRightVector() const;
	d3Vector GetUpVector() const;

private:

	// View parameters
	d3Point     _pPosition;
	d3Vector    _vLookAt;		// must be unit vector
	d3Vector    _vWorldUp;		// must be unit vector
  
	// Projection parameters
	d3Float     _fAspect;
	d3Float     _fNearPlane;
	d3Float     _fFarPlane;
	
	d3Float     _fFov;

	mutable sBool	_bChanged;

};

