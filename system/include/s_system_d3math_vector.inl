/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_vector.inl
//  Created                 : 1 12 2007   15:03
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


inline d3Vector::d3Vector() :
	w( 1.0f )
{

}

inline d3Vector::d3Vector( const d3Float* p ) :
	x( p[0] ),
	y( p[1] ),
	z( p[2] ),
	w( 1.0f )
{

}

inline d3Vector::d3Vector( d3Float vx, d3Float vy, d3Float vz ) :
	x( vx ),
	y( vy ),
	z( vz ),
	w( 1.0f )
{

}

inline d3Vector::d3Vector( d3Float v ) :
	x( v ),
	y( v ),
	z( v ),
	w( 1.0f )
{

}

inline d3Vector::d3Vector( const d3Vector& v ) :
	x( v.x ),
	y( v.y ),
	z( v.z ),
	w( v.w )
{
}

inline void d3Vector::operator = ( const d3Vector& v )
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

inline void d3Vector::operator = ( const d3Float* p )
{
	x = p[0];
	y = p[1];
	z = p[2];
	w = 1.0f;
}

inline d3Float d3Vector::Magnitude() const
{
	return FMath::Sqrt( Magnitude2() );
}

inline d3Float d3Vector::Magnitude2() const
{
	return x*x + y*y + z*z;
}


inline void d3Vector::operator += ( d3Float v )
{
	x += v;
	y += v;
	z += v;
}

inline void d3Vector::operator -= ( d3Float v )
{
	x -= v;
	y -= v;
	z -= v;
}

inline void d3Vector::operator *= ( d3Float v )
{
	x *= v;
	y *= v;
	z *= v;
}

inline void d3Vector::operator /= ( d3Float v )
{
	__S_ASSERT(  FMath::Abs( v ) > Limit::d3Float::Precision );

	v = 1.0f / v;
	x *= v;
	y *= v;
	z *= v;
}

inline void d3Vector::operator += ( const d3Vector& v )
{
	x += v.x;
	y += v.y;
	z += v.z;
}

inline void d3Vector::operator -= ( const d3Vector& v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

inline void d3Vector::operator *= ( const d3Vector& v )
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

inline d3Vector d3Vector::operator + ( const d3Vector& v ) const
{
	d3Vector r;
	Add( r, *this, v );
	return r;
}

inline d3Vector d3Vector::operator - ( const d3Vector& v ) const
{
	d3Vector r;
	Sub( r, *this, v );
	return r;
}

inline d3Vector d3Vector::operator / ( const d3Vector& v ) const
{
	d3Vector r;
	Div( r, *this, v );
	return r;
}

inline d3Vector d3Vector::operator / ( const d3Float f ) const
{
	d3Vector r;
	Div( r, *this, f );
	return r;
}


inline void d3Vector::Add( d3Vector& r, const d3Vector& a, const d3Vector& b )
{
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
}

inline void d3Vector::Add( d3Vector* r, sInt count, const d3Vector& a )
{
	for( sInt i = 0; i < count; i++ )
	{
		*r += a;
		r++;
	}
}

inline void d3Vector::Sub( d3Vector& r, const d3Vector& a, const d3Vector& b )
{
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
}

inline void d3Vector::Sub( d3Vector* r, sInt count, const d3Vector& a )
{
	for( sInt i = 0; i < count; i++ )
	{
		*r -= a;
		r++;
	}
}

inline void d3Vector::Mul( d3Vector& r, const d3Vector& v, d3Float a )
{
	r.x = v.x * a;
	r.y = v.y * a;
	r.z = v.z * a;
}

inline void d3Vector::Mul( d3Vector& r, const d3Vector& a, const d3Matrix& m )
{
	d3Float x = a.x * m._11 + a.y * m._21 + a.z * m._31 + a.w * m._41;
	d3Float y = a.x * m._12 + a.y * m._22 + a.z * m._32 + a.w * m._42;
	d3Float z = a.x * m._13 + a.y * m._23 + a.z * m._33 + a.w * m._43;
	d3Float w = a.x * m._14 + a.y * m._24 + a.z * m._34 + a.w * m._44;

	r.x = x / w;
	r.y = y / w;
	r.z = z / w;
}

inline void d3Vector::Apply( const d3Matrix& m )
{
	Mul( *this, *this, m );
}

inline void d3Vector::Mul( d3Vector* r, sInt count, const d3Matrix& m )
{
	for( sInt i = 0; i < count; i++ )
	{
		Mul( *r, *r, m );
		r++;
	}
}

inline d3Float d3Vector::DotProduct(  const d3Vector& a, const d3Vector& b )
{
	return a.x * b.x + a.y * b.y + a.z * b.z; 
}

inline void d3Vector::CrossProduct( d3Vector& v, const d3Vector& a, const d3Vector& b )
{
	d3Float tempx = a.y * b.z - a.z * b.y;
	d3Float tempy = a.z * b.x - a.x * b.z;

	v.z = a.x * b.y - a.y * b.x;
	v.y = tempy;
	v.x = tempx;
}

inline d3Vector d3Vector::operator ^ ( const d3Vector& v ) const
{
	d3Vector r;
	r.x = y * v.z - z * v.y;
	r.y = z * v.x - x * v.z;
	r.z = x * v.y - y * v.x;

	return r;
}

inline sBool d3Vector::operator == ( const d3Vector& v ) const
{
	return x == v.x && y == v.y && z == v.z;
}

inline sBool d3Vector::operator != ( const d3Vector& v ) const
{
	return x != v.x || y != v.y || z != v.z;
}

inline void d3Vector::Negate( d3Vector& v )
{
	v.x = - v.x;
	v.y = - v.y;
	v.z = - v.z;
}

inline void d3Vector::Negate( d3Vector* r, sInt count )
{
	for( sInt i = 0; i < count; i++ )
		Negate( r[i] );
}

inline sBool d3Vector::IsCloseToZero() const
{
	return 
		FMath::CloseToZero( x ) &&
		FMath::CloseToZero( y ) &&
		FMath::CloseToZero( z );
}

inline d3Vector d3Vector::operator - () const
{
	d3Vector v;
	v.x = -x;
	v.y = -y;
	v.z = -z;

	return v;
}

inline d3Vector d3Vector::UnitVector() const
{
	d3Float d = Magnitude();

	d3Vector r( *this );

	if( d != 0.0f )
		r /= d;

	return r;
}

inline d3Float d3Vector::operator * ( const d3Vector& v ) const
{
	return DotProduct( *this, v );
}

inline d3Vector d3Vector::operator * ( d3Float v ) const
{
	return d3Vector ( x * v, y * v, z * v );
}

inline sBool d3Vector::AngleIsAcute( const d3Vector& a, const d3Vector& b )
{
	return a * b > 0.0f;
}

inline sBool d3Vector::AngleIsRight( const d3Vector& a, const d3Vector& b )
{
	return a * b == 0.0f;
}

inline sBool d3Vector::AngleIsObtuse( const d3Vector& a, const d3Vector& b )
{
	return a * b < 0.0f;
}

inline void d3Vector::Project( d3Vector& vn, const d3Vector& v, const d3Vector& n )
{
	d3Float dotp = 1.0f / n.Magnitude2();
  
	dotp *= v*n;

	Mul( vn, n, dotp );
}

inline void d3Vector::Project( d3Vector& vn, d3Vector& vp, const d3Vector& v, const d3Vector& n )
{
	Project( vn, v, n );
	Sub( vp, v, vn );
}

inline d3Float d3Vector::Distance( const d3Vector& a, const d3Vector& b )
{
	return (a-b).Magnitude();
}

inline d3Float d3Vector::DistanceSquared( const d3Vector& a, const d3Vector& b )
{
	return (a-b).Magnitude2();
}

inline d3Float d3Vector::Distance( const d3Vector& v ) const
{
	return Distance( *this, v );
}

inline void d3Vector::Div( d3Vector& r, const d3Vector& a, const d3Vector& b )
{
	r.x = a.x / b.x;
	r.y = a.y / b.y;
	r.z = a.z / b.z;
}

inline void d3Vector::Div( d3Vector& r, const d3Vector& a, d3Float f )
{
	__S_ASSERT(  FMath::Abs( f ) > Limit::d3Float::Precision );

	f =  1.0f / f;

	r.x = a.x * f;
	r.y = a.y * f;
	r.z = a.z * f;
}
