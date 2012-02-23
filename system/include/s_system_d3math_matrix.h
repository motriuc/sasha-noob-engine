/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_matrix.h
//  Created                 : 1 12 2007   14:03
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
 * Matrix
 */
class d3Matrix
{
public:
	/**
	 * Nothing
	 */
	d3Matrix();
	
	/**
	 *
	 */
	explicit d3Matrix( d3Float v );

	/**
	 * 
	 */
	d3Matrix( const d3Matrix& m );

	/**
	 * 
	 */
	void operator = ( const d3Matrix& m );

	/**
	 * 
	 */
	void operator *= ( const d3Matrix& m );

	/**
	 * 
	 */
	void operator *= ( d3Float k );

	/**
	 * 
	 */
	void operator += ( const d3Matrix& m );
  
	/**
	 * 
	 */
	void operator -= ( const d3Matrix& m );

	/**
	 * mul matrix
	 */
	d3Matrix operator * ( const d3Matrix& m ) const;

	/**
	 * 
	 */
	d3Matrix operator * ( d3Float k ) const;

	/**
	 * Invert matrix
	 */
	d3Matrix operator !() const;

	/**
	 * Transpose matrix
	 */
	d3Matrix operator ~() const;
  
	/**
	 *
	 */
	d3Float CoFactor( sInt row, sInt col ) const;
  
	/**
	 * 
	 */
	d3Float Determinant() const;
  
	/**
	 *
	 */
	sBool Invert();

	/**
	 * 
	 */
	void Transpose();

	/**
	 * 
	 */
	void SetRotateX( d3Float a );

	/**
	 * 
	 */
	void SetRotateY( d3Float a );

	/**
	 * 
	 */
	void SetRotateZ( d3Float a );

	/**
	 * 
	 */
	void SetRotate( const d3Vector& n, d3Float a );

	/**
	 * 
	 */
	void SetScale( d3Float x, d3Float y, d3Float z );

	/**
	 * 
	 */
	void SetScale( const d3Vector& n, d3Float k );

	/**
	 * 
	 */
	void SetProjectToPlane( const d3Vector& n );

	/**
	 * 
	 */
	void SetTranslation( const d3Vector& v );

	/**
	 * 
	 */
	void SetTranslationX( d3Float x );
	
	/**
	 * 
	 */
	void SetTranslationY( d3Float y );

	/**
	 * 
	 */
	void SetTranslationZ( d3Float z );

	/**
	 * 
	 */
	void SetPerspectiveProjection( d3Float d );
  
	/**
	 * 
	 */
	void SetLookAtLH( const d3Point& pEye, const d3Vector& vLookAt, const d3Vector& vUp );

	/**
	 * 
	 */
	void SetPerspectiveFovLH( d3Float fFov, d3Float fAspect, d3Float fNearPlane, d3Float fFarPlane );

	/**
	 * get translation matrix component
	 */
	void GetTranslation( d3Matrix& m ) const;

	/**
	 * Get translation vector
	 */
	void GetTranslation( d3Vector& v ) const;
	
	/**
	 *
	 */
	void GetScale( d3Vector& v ) const;

	/**
	 * 
	 */
	void GetNoTranslation( d3Matrix& m ) const;
	
	/**
	 *
	 */
	void GetNormalMatrix( d3Matrix& m ) const;

	/**
	 *
	 */
	void GetNormalMatrixRT( d3Matrix& m ) const;
	
	/**
	 * Remove translation components
	 */
	void RemoveTranslation();

	/**
	 *
	 */
	static sBool Invert( d3Matrix& r, const d3Matrix& a );

	/**
	 * Invert a matrix composed with rotation and translation
	 */
	static sBool InvertRT( d3Matrix& r, const d3Matrix& a );

	/**
	 * 
	 */
	static void Mul( d3Matrix& r, const d3Matrix& a, const d3Matrix& b );

	/**
	 *
	 */
	static void Mul( d3Matrix& r, const d3Matrix& a, d3Float k );

	/**
	 * 
	 */
	static void Add( d3Matrix& r, const d3Matrix& a, const d3Matrix& b );

	/**
	 * 
	 */
	static void Sub( d3Matrix& r, const d3Matrix& a, const d3Matrix& b );
  
	/**
	 * 
	 */
	static void Transpose( d3Matrix& r );

public:
	union {
		struct 
		{
			d3Float _11, _12, _13, _14;
			d3Float _21, _22, _23, _24;
			d3Float _31, _32, _33, _34;
			d3Float _41, _42, _43, _44;
		};
		d3Float m[4][4];
		d3Float v[16];
	}; 
};



