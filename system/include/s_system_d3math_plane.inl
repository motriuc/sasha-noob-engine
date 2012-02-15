/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_plane.inl
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
inline d3Plane::d3Plane()
{
}

inline d3Plane::d3Plane( const d3Plane& p ) :
	_normal( p._normal ),
	_d( p._d )
{
}

inline void d3Plane::operator = ( const d3Plane& p )
{
	_normal = p._normal;
	_d = p._d;
}

inline d3Plane::d3Plane( const d3Vector& normal, d3Float d ) :
	_normal( normal.UnitVector() ),
	_d( d )
{
}

inline d3Plane::d3Plane( const d3Vector& normal, const d3Point& origin ) :
	_normal( normal.UnitVector() )
{
	_d = d3Vector::DotProduct( _normal, origin );
}

inline d3Plane::d3Plane( const d3Point& p1, const d3Point& p2, const d3Point& p3 )
{
	d3Point::CrossProduct( _normal, p2 - p1, p3 - p1 );
	_normal = _normal.UnitVector();

	_d = d3Vector::DotProduct( _normal, p1 );
}

inline void d3Plane::Project( d3Point& p, const d3Point& s ) const
{
	d3Float t = d3Point::DotProduct( _normal, s ) - _d;

	d3Vector::Sub( p, s, _normal * t );
}

inline d3Point d3Plane::Project( const d3Point& s ) const
{ 
	d3Point p;
	Project( p, s );
	return p;
}

inline d3Float d3Plane::Distance( d3Point& p ) const
{
	return p.Distance( Project( p ) );
}

inline const d3Vector& d3Plane::Normal() const
{
	return _normal;
}

inline const d3Float d3Plane::GetD() const
{
	return _d;
}

inline sBool d3Plane::OnOpositeSide( const d3Point& p1, const d3Point& p2 ) const
{
	d3Float pt1 = d3Vector::DotProduct( _normal, p1 );
	d3Float pt2 = d3Vector::DotProduct( _normal, p2 );
  
	return
		( pt1 < 0.0f && pt2 > 0.0f ) ||
		( pt1 > 0.0f && pt2 < 0.0f );
}

inline sBool d3Plane::IsInPlane( const d3Point& p ) const
{
	d3Float pt = d3Vector::DotProduct( _normal, p ) - _d;

	return FMath::Abs( pt ) < Limit::d3Float::Precision;
}


