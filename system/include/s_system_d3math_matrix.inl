/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_matrix.inl
//  Created                 : 1 12 2007   14:14
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

inline d3Matrix::d3Matrix()
{
}

inline d3Matrix::d3Matrix( d3Float v )
{
	_11 = _22 = _33 = _44 = v;
  
	_12 = _13 = _14 = 
	_21 = _23 = _24 =
	_31 = _32 = _34 =
	_41 = _42 = _43 = 0.0f;
}

inline d3Matrix::d3Matrix( const d3Matrix& m )
{
	Memory::Copy( v, m.v, sizeof(d3Float) * 16 );
}

inline void d3Matrix::operator = ( const d3Matrix& m )
{
	Memory::Copy( v, m.v, sizeof(d3Float) * 16 );
}

inline void d3Matrix::operator *= ( const d3Matrix& m )
{
	d3Matrix t;
	Mul( t, *this, m );
	*this = t;
}

inline void d3Matrix::operator *= ( d3Float k )
{
	Mul( *this, *this, k );
}

inline d3Matrix d3Matrix::operator * ( const d3Matrix& m ) const
{
	d3Matrix t;
	Mul( t, *this, m );
	return t;
}

inline d3Matrix d3Matrix::operator * ( d3Float k ) const
{
	d3Matrix r;
	Mul( r, *this, k );
	return r;
}

inline void d3Matrix::operator += ( const d3Matrix& m )
{
	Add( *this, *this, m );
}

inline void d3Matrix::operator -= ( const d3Matrix& m )
{
	Sub( *this, *this, m );
}


inline void d3Matrix::Mul( d3Matrix& r, const d3Matrix& a, const d3Matrix& b )
{
	__S_ASSERT( &r != &a );
	__S_ASSERT( &r != &b );

	r._11 = a._11 * b._11 + a._12 * b._21 + a._13 * b._31 + a._14 * b._41;
	r._12 = a._11 * b._12 + a._12 * b._22 + a._13 * b._32 + a._14 * b._42;
	r._13 = a._11 * b._13 + a._12 * b._23 + a._13 * b._33 + a._14 * b._43;
	r._14 = a._11 * b._14 + a._12 * b._24 + a._13 * b._34 + a._14 * b._44;

	r._21 = a._21 * b._11 + a._22 * b._21 + a._23 * b._31 + a._24 * b._41;
	r._22 = a._21 * b._12 + a._22 * b._22 + a._23 * b._32 + a._24 * b._42;
	r._23 = a._21 * b._13 + a._22 * b._23 + a._23 * b._33 + a._24 * b._43;
	r._24 = a._21 * b._14 + a._22 * b._24 + a._23 * b._34 + a._24 * b._44;

	r._31 = a._31 * b._11 + a._32 * b._21 + a._33 * b._31 + a._34 * b._41;
	r._32 = a._31 * b._12 + a._32 * b._22 + a._33 * b._32 + a._34 * b._42;
	r._33 = a._31 * b._13 + a._32 * b._23 + a._33 * b._33 + a._34 * b._43;
	r._34 = a._31 * b._14 + a._32 * b._24 + a._33 * b._34 + a._34 * b._44;
  
	r._41 = a._41 * b._11 + a._42 * b._21 + a._43 * b._31 + a._44 * b._41;
	r._42 = a._41 * b._12 + a._42 * b._22 + a._43 * b._32 + a._44 * b._42;
	r._43 = a._41 * b._13 + a._42 * b._23 + a._43 * b._33 + a._44 * b._43;
	r._44 = a._41 * b._14 + a._42 * b._24 + a._43 * b._34 + a._44 * b._44;
}

inline void d3Matrix::Mul( d3Matrix& r, const d3Matrix& a, d3Float k )
{
	r._11 = a._11 * k;
	r._12 = a._12 * k;
	r._13 = a._13 * k;
	r._14 = a._14 * k;
	r._21 = a._21 * k;
	r._22 = a._22 * k;
	r._23 = a._23 * k;
	r._24 = a._24 * k;
	r._31 = a._31 * k;
	r._32 = a._32 * k;
	r._33 = a._33 * k;
	r._34 = a._34 * k;
	r._41 = a._41 * k;
	r._42 = a._42 * k;
	r._43 = a._43 * k;
	r._44 = a._44 * k;
}

inline void d3Matrix::Add( d3Matrix& r, const d3Matrix& a, const d3Matrix& b )
{
	r._11 = a._11 + b._11;
	r._12 = a._12 + b._12;
	r._13 = a._13 + b._13;
	r._14 = a._14 + b._14;

	r._21 = a._21 + b._21;
	r._22 = a._22 + b._22;
	r._23 = a._23 + b._23;
	r._24 = a._24 + b._24;

	r._31 = a._31 + b._31;
	r._32 = a._32 + b._32;
	r._33 = a._33 + b._33;
	r._34 = a._34 + b._34;

	r._41 = a._41 + b._41;
	r._42 = a._42 + b._42;
	r._43 = a._43 + b._43;
	r._44 = a._44 + b._44;
}

inline void d3Matrix::Sub( d3Matrix& r, const d3Matrix& a, const d3Matrix& b )
{
	r._11 = a._11 - b._11;
	r._12 = a._12 - b._12;
	r._13 = a._13 - b._13;
	r._14 = a._14 - b._14;

	r._21 = a._21 - b._21;
	r._22 = a._22 - b._22;
	r._23 = a._23 - b._23;
	r._24 = a._24 - b._24;

	r._31 = a._31 - b._31;
	r._32 = a._32 - b._32;
	r._33 = a._33 - b._33;
	r._34 = a._34 - b._34;

	r._41 = a._41 - b._41;
	r._42 = a._42 - b._42;
	r._43 = a._43 - b._43;
	r._44 = a._44 - b._44;
}

inline d3Float d3Matrix::CoFactor( sInt row, sInt col ) const
{
	sInt r1 = ( row + 1 ) & 3;
	sInt r2 = ( row + 2 ) & 3;
	sInt r3 = ( row + 3 ) & 3;

	sInt c1 = ( col + 1 ) & 3;
	sInt c2 = ( col + 2 ) & 3;
	sInt c3 = ( col + 3 ) & 3;

	return 
	(
		( 
			m[r1][c1] * m[r2][c2] * m[r3][c3] +
			m[r1][c2] * m[r2][c3] * m[r3][c1] +
			m[r1][c3] * m[r2][c1] * m[r3][c2]
		) -  
		(
			m[r3][c1] * m[r2][c2] * m[r1][c3] +
			m[r3][c2] * m[r2][c3] * m[r1][c1] +
			m[r3][c3] * m[r2][c1] * m[r1][c2]
		)
	) * ((row + col) & 1 ? -1.0f : +1.0f); 
}

inline d3Float d3Matrix::Determinant() const
{
	return
		m[0][0] * CoFactor( 0, 0 ) +
		m[0][1] * CoFactor( 0, 1 ) +
		m[0][2] * CoFactor( 0, 2 ) +
		m[0][3] * CoFactor( 0, 3 );   
}

inline sBool d3Matrix::Invert( d3Matrix& r, const d3Matrix& a )
{
	__S_ASSERT( &r != &a );

	d3Float det = a.Determinant();

	if( FMath::Abs( det ) < Limit::d3Float::Precision )
		return sFalse;

	d3Float idet = 1.0f / det;

	r.m[0][0] = a.CoFactor( 0,0 ) * idet;
	r.m[1][0] = a.CoFactor( 0,1 ) * idet;
	r.m[2][0] = a.CoFactor( 0,2 ) * idet;
	r.m[3][0] = a.CoFactor( 0,3 ) * idet;
	r.m[0][1] = a.CoFactor( 1,0 ) * idet;
	r.m[1][1] = a.CoFactor( 1,1 ) * idet;
	r.m[2][1] = a.CoFactor( 1,2 ) * idet;
	r.m[3][1] = a.CoFactor( 1,3 ) * idet;
	r.m[0][2] = a.CoFactor( 2,0 ) * idet;
	r.m[1][2] = a.CoFactor( 2,1 ) * idet;
	r.m[2][2] = a.CoFactor( 2,2 ) * idet;
	r.m[3][2] = a.CoFactor( 2,3 ) * idet;
	r.m[0][3] = a.CoFactor( 3,0 ) * idet;
	r.m[1][3] = a.CoFactor( 3,1 ) * idet;
	r.m[2][3] = a.CoFactor( 3,2 ) * idet;
	r.m[3][3] = a.CoFactor( 3,3 ) * idet;

	return sTrue;
}

inline sBool d3Matrix::Invert()
{
	d3Matrix temp( *this );
	return Invert( *this, temp );
}

inline d3Matrix d3Matrix::operator !() const
{
	d3Matrix temp;
	Invert( temp, *this );

	return temp;
}

inline sBool d3Matrix::InvertRT( d3Matrix& r, const d3Matrix& a )
{
	r._11 = a._11;
	r._21 = a._12; 
	r._31 = a._31;
  
	r._41 = -( a._41 * a._11 + a._42 * a._12 + a._43 * a._13 );

	r._12 = a._21;
	r._22 = a._22;
	r._32 = a._23;
	r._42 = -( a._41 * a._21 + a._42 * a._22 + a._43 * a._23 );

	r._13 = a._31;
	r._23 = a._32;
	r._33 = a._33;
	r._43 = -( a._41 * a._31 + a._42 * a._32 + a._43 * a._33 );

	r._14 = r._24 = r._34 = 0.0f;
	r._44 = 1.0f;
	
	return sTrue;
}


inline void d3Matrix::Transpose( d3Matrix& r )
{
	d3Float temp;

	temp  = r._12;
	r._12 = r._21;
	r._21 = temp;

	temp  = r._13;
	r._13 = r._31;
	r._31 = temp;

	temp  = r._14;
	r._14 = r._41;
	r._41 = temp;

	temp  = r._23;
	r._23 = r._32;
	r._32 = temp;

	temp  = r._24;
	r._24 = r._42;
	r._42 = temp;

	temp  = r._34;
	r._34 = r._43;
	r._43 = temp;
}

inline void d3Matrix::Transpose()
{
	Transpose( *this );
}

inline d3Matrix d3Matrix::operator ~() const
{
	d3Matrix r;

	r._12 = _21;
	r._21 = _12;

	r._13 = _31;
	r._31 = _13;

	r._14 = _41;
	r._41 = _14;

	r._23 = _32;
	r._32 = _23;

	r._24 = _42;
	r._42 = _24;

	r._34 = _43;
	r._43 = _34;
	
	return r;
}

/************************************************************************/
/* Set functions                                                        */
/************************************************************************/
inline void d3Matrix::SetRotateX( d3Float a )
{
	_11 = _44 = 1.0f;

	_12 = _13 = _14 = 
	_21 = _24 = 
	_31 = _34 = 
	_41 = _42 = _43 = 0.0f;

	_22 = _33 = FMath::Cos( a );
	_23 = FMath::Sin( a );
	_32 = - _23;
}

inline void d3Matrix::SetRotateY( d3Float a )
{
	_22 = _44 = 1.0f;

	_12 = _14 = 
	_21 = _23 = _24 =  
	_32 = _34 = 
	_41 = _42 = _43 = 0.0f;

	_11 = _33 = FMath::Cos( a );
	_31 = FMath::Sin( a );
	_13 = - _31;
}

inline void d3Matrix::SetRotateZ( d3Float a )
{
	_33 = _44 = 1.0f;

	_13 = _14 = 
	_23 = _24 =  
	_31 = _32 = _34 =  
	_41 = _42 = _43 = 0.0f;

	_11 = _22 = FMath::Cos( a );
	_12 = FMath::Sin( a );
	_21 = - _12;
}

inline void d3Matrix::SetRotate( const d3Vector& n, d3Float a )
{
	d3Float ca = FMath::Cos( a );
	d3Float sa = FMath::Sin( a );
	d3Float ca1 = 1.0f - ca;

	_11 = n.x * n.x * ca1 + ca;
	_12 = n.x * n.y * ca1 + n.z * sa;
	_13 = n.x * n.z * ca1 - n.y * sa;

	_21 = n.x * n.y * ca1 - n.z * sa;
	_22 = n.y * n.y * ca1 + ca;
	_23 = n.y * n.z * ca1 + n.x * sa;

	_31 = n.x * n.z * ca1 + n.y * sa;
	_32 = n.y * n.z * ca1 - n.x * sa;
	_33 = n.z * n.z * ca1 + ca;

	_14 = _24 = _34 = 
	_41 = _42 = _43 = 0.0f;

	_44 = 1.0f;
}

inline void d3Matrix::SetScale( d3Float x, d3Float y, d3Float z )
{
	_11 = x;
	_22 = y;
	_33 = z;

	_12 = _13 = _14 = 
	_21 = _23 = _24 = 
	_31 = _32 = _34 = 
	_41 = _42 = _43 = 0.0f;

	_44 = 1.0f;
}

inline void d3Matrix::SetScale( const d3Vector& n, d3Float k )
{
	k = 1.0f - k;
  
	_11 = n.x * n.x * k  + 1.0f;
	_12 = n.x * n.y * k;
	_13 = n.x * n.z * k;

	_21 = _12;
	_22 = n.y * n.y * k + 1.0f;
	_23 = n.y * n.z * k;

	_31 = _13;
	_32 = _23;
	_33 = n.z * n.z * k + 1.0f;
  
	_14 = _24 = _34 = 
	_41 = _42 = _43 = 0.0f;

	_44 = 1.0f;
}

inline void d3Matrix::SetProjectToPlane( const d3Vector& n )
{
	_11 = 1.0f - n.x * n.x;
	_12 = - n.x * n.y;
	_13 = - n.x * n.z;

	_21 = _12;
	_22 = 1.0f - n.y * n.y;
	_23 = - n.y * n.z;

	_31 = _13;
	_32 = _23;
	_33 = 1.0f - n.z * n.z;

	_14 = _24 = _34 = 
	_41 = _42 = _43 = 0.0f;

	_44 = 1.0f;
}

inline void d3Matrix::SetTranslation( const d3Vector& v )
{
	_11 = _22 = _33 = _44 = 1.0f;

	_12 = _13 = _14 = 
	_21 = _23 = _24 = 
	_31 = _32 = _34 = 0.0f;

	_41 = v.x;
	_42 = v.y;
	_43 = v.z;
}

inline void d3Matrix::SetTranslationX( d3Float x )
{
	SetTranslation( d3Vector( x, 0.0f, 0.0f ) );
}

inline void d3Matrix::SetTranslationY( d3Float y )
{
  SetTranslation( d3Vector( 0.0f, y, 0.0f ) );
}

inline void d3Matrix::SetTranslationZ( d3Float z )
{
  SetTranslation( d3Vector( 0.0f, 0.0f, z ) );
}

inline void d3Matrix::SetPerspectiveProjection( d3Float d )
{
	_11 = _12 = _13 = 1.0f;

	_12 = _13 = _14 = 
	_21 = _23 = _24 =
	_31 = _32 = 
	_41 = _42 = _43 = _44 = 0.0f;

	_34 = 1.0f / d;
}

inline void d3Matrix::SetLookAtLH( const d3Point& pEye, const d3Vector& vLookAt, const d3Vector& vUp )
{
	d3Vector zaxis = vLookAt.UnitVector();
  
	d3Vector xaxis = ( vUp ^ zaxis ).UnitVector();
  
	d3Vector yaxis( zaxis ^ xaxis );

	_11 = xaxis.x;         _12 = yaxis.x;         _13 = zaxis.x;          _14 = 0.0f;
	_21 = xaxis.y;         _22 = yaxis.y;         _23 = zaxis.y;          _24 = 0.0f;
	_31 = xaxis.z;         _32 = yaxis.z;         _33 = zaxis.z;          _34 = 0.0f;
	_41 = - xaxis * pEye;  _42 = - yaxis * pEye;  _43 = - zaxis * pEye;   _44 = 1.0f;
}

inline void d3Matrix::SetPerspectiveFovLH( d3Float fFov, d3Float fAspect, d3Float fNearPlane, d3Float fFarPlane )
{
	d3Float yScale = FMath::CoTan( fFov / 2.0f );
	d3Float xScale = fAspect * yScale;
	d3Float z = fFarPlane / ( fFarPlane - fNearPlane );

	_11 = xScale;       _12 = 0.0f;         _13 = 0.0f;               _14 = 0.0f;
	_21 = 0.0f;         _22 = yScale;       _23 = 0.0f;               _24 = 0.0f;
	_31 = 0.0f;         _32 = 0.0f;         _33 = z;                  _34 = 1.0f;
	_41 = 0.0f;         _42 = 0.0f;         _43 = - z * fNearPlane;   _44 = 0.0f;
}

inline void d3Matrix::GetNormalMatrix( d3Matrix& m ) const
{
	Invert( m, *this );
	m.Transpose();
}

inline void d3Matrix::GetNormalMatrixRT( d3Matrix& m ) const
{
	InvertRT( m, *this );
	m.Transpose();
}

/************************************************************************/
/* Get functions                                                        */
/************************************************************************/

inline void d3Matrix::GetTranslation( d3Matrix& m ) const
{
	m.SetTranslation( d3Vector( _41, _42, _43 ) );
}

inline void d3Matrix::GetTranslation( d3Vector& v ) const
{
	v.x = _41;
	v.y = _42;
	v.z = _43;
}

inline void d3Matrix::GetNoTranslation( d3Matrix& m ) const
{
	m = *this;
	m.RemoveTranslation();
}

/************************************************************************/
/* Remove functions                                                     */
/************************************************************************/
inline void d3Matrix::RemoveTranslation()
{
	_41 = _42 = _43 = 0.0f;
}
