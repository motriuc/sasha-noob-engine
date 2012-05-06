/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d2math_vector.inl
//  Created                 : 4 2 2011   21:16
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


inline d2Vector::d2Vector() :
	w( 1.0f )
{

}

inline d2Vector::d2Vector( const d2Float* p ) :
	x( p[0] ),
	y( p[1] ),
	w( 1.0f )
{

}

inline d2Vector::d2Vector( d2Float vx, d2Float vy ) :
	x( vx ),
	y( vy ),
	w( 1.0f )
{

}

inline d2Vector::d2Vector( d2Float v ) :
	x( v ),
	y( v ),
	w( 1.0f )
{

}

inline d2Vector::d2Vector( const d2Vector& v ) :
	x( v.x ),
	y( v.y ),
	w( v.w )
{
}

inline void d2Vector::operator = ( const d2Vector& v )
{
	x = v.x;
	y = v.y;
	w = v.w;
}

inline void d2Vector::operator = ( const d2Float* p )
{
	x = p[0];
	y = p[1];
	w = 1.0f;
}

inline d2Float d2Vector::Magnitude() const
{
	return FMath::Sqrt( Magnitude2() );
}

inline d2Float d2Vector::Magnitude2() const
{
	return x*x + y*y;
}


inline void d2Vector::operator += ( d2Float v )
{
	x += v;
	y += v;
}

inline void d2Vector::operator -= ( d2Float v )
{
	x -= v;
	y -= v;
}

inline void d2Vector::operator *= ( d2Float v )
{
	x *= v;
	y *= v;
}

inline void d2Vector::operator /= ( d2Float v )
{
	__S_ASSERT(  FMath::Abs( v ) > Limit::d2Float::Precision );

	v = 1.0f / v;
	x *= v;
	y *= v;
}

inline void d2Vector::operator += ( const d2Vector& v )
{
	x += v.x;
	y += v.y;
}

inline void d2Vector::operator -= ( const d2Vector& v )
{
	x -= v.x;
	y -= v.y;
}

inline void d2Vector::operator *= ( const d2Vector& v )
{
	x *= v.x;
	y *= v.y;
}

inline d2Vector d2Vector::operator + ( const d2Vector& v ) const
{
	d2Vector r;
	Add( r, *this, v );
	return r;
}

inline d2Vector d2Vector::operator - ( const d2Vector& v ) const
{
	d2Vector r;
	Sub( r, *this, v );
	return r;
}

inline d2Vector d2Vector::operator / ( const d2Vector& v ) const
{
	d2Vector r;
	Div( r, *this, v );
	return r;
}

inline d2Vector d2Vector::operator / ( const d2Float f ) const
{
	d2Vector r;
	Div( r, *this, f );
	return r;
}


inline void d2Vector::Add( d2Vector& r, const d2Vector& a, const d2Vector& b )
{
	r.x = a.x + b.x;
	r.y = a.y + b.y;
}

inline void d2Vector::Add( d2Vector* r, sInt count, const d2Vector& a )
{
	for( sInt i = 0; i < count; i++ )
	{
		*r += a;
		r++;
	}
}

inline void d2Vector::Sub( d2Vector& r, const d2Vector& a, const d2Vector& b )
{
	r.x = a.x - b.x;
	r.y = a.y - b.y;
}

inline void d2Vector::Sub( d2Vector* r, sInt count, const d2Vector& a )
{
	for( sInt i = 0; i < count; i++ )
	{
		*r -= a;
		r++;
	}
}

inline void d2Vector::Mul( d2Vector& r, const d2Vector& v, d2Float a )
{
	r.x = v.x * a;
	r.y = v.y * a;
}

inline d2Float d2Vector::DotProduct(  const d2Vector& a, const d2Vector& b )
{
	return a.x * b.x + a.y * b.y; 
}

inline sBool d2Vector::operator == ( const d2Vector& v ) const
{
	return x == v.x && y == v.y;
}

inline sBool d2Vector::operator != ( const d2Vector& v ) const
{
	return x != v.x || y != v.y;
}

inline void d2Vector::Negate( d2Vector& v )
{
	v.x = - v.x;
	v.y = - v.y;
}

inline void d2Vector::Negate( d2Vector* r, sInt count )
{
	for( sInt i = 0; i < count; i++ )
		Negate( r[i] );
}


inline d2Vector d2Vector::operator - () const
{
	d2Vector v;
	v.x = -x;
	v.y = -y;

	return v;
}

inline d2Vector d2Vector::UnitVector() const
{
	d2Float d = Magnitude();

	d2Vector r( *this );

	if( d != 0.0f )
		r /= d;

	return r;
}

inline d2Float d2Vector::GetAngle() const
{
	return System::FMath::ATan2( x, y );
}


inline d2Float d2Vector::operator * ( const d2Vector& v ) const
{
	return DotProduct( *this, v );
}

inline d2Vector d2Vector::operator * ( d2Float v ) const
{
	return d2Vector ( x * v, y * v );
}

inline sBool d2Vector::AngleIsAcute( const d2Vector& a, const d2Vector& b )
{
	return a * b > 0.0f;
}

inline sBool d2Vector::AngleIsRight( const d2Vector& a, const d2Vector& b )
{
	return a * b == 0.0f;
}

inline sBool d2Vector::AngleIsObtuse( const d2Vector& a, const d2Vector& b )
{
	return a * b < 0.0f;
}

inline d2Float d2Vector::GetAngle( const d2Vector& a, const d2Vector& b )
{
	d2Float t = b.GetAngle() - a.GetAngle();
	if( t < 0.0f )
		t += System::FMath::f2Pi;
		
	return t;
}

inline void d2Vector::Project( d2Vector& vn, const d2Vector& v, const d2Vector& n )
{
	d2Float dotp = 1.0f / n.Magnitude2();
  
	dotp *= v*n;

	Mul( vn, n, dotp );
}

inline void d2Vector::Project( d2Vector& vn, d2Vector& vp, const d2Vector& v, const d2Vector& n )
{
	Project( vn, v, n );
	Sub( vp, v, vn );
}

inline d2Float d2Vector::Distance( const d2Vector& a, const d2Vector& b )
{
	return (a-b).Magnitude();
}

inline d2Float d2Vector::DistanceSquared( const d2Vector& a, const d2Vector& b )
{
	return (a-b).Magnitude2();
}

inline d2Float d2Vector::Distance( const d2Vector& v ) const
{
	return Distance( *this, v );
}

inline void d2Vector::Div( d2Vector& r, const d2Vector& a, const d2Vector& b )
{
	r.x = a.x / b.x;
	r.y = a.y / b.y;
}

inline void d2Vector::Div( d2Vector& r, const d2Vector& a, d2Float f )
{
	__S_ASSERT(  FMath::Abs( f ) > Limit::d2Float::Precision );

	f =  1.0f / f;

	r.x = a.x * f;
	r.y = a.y * f;
}
