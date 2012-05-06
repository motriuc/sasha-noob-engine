/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_sphere.inl
//  Created                 : 1 12 2007   15:49
//  File path               : C++\SLibF\system\Include
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

inline d3Sphere::d3Sphere()
{
}

inline d3Sphere::d3Sphere( const d3Point& p, d3Float d ) :
	_center( p ),
	_d( d )
{
	__S_ASSERT( _d > Limit::d3Float::Precision );
}

inline d3Sphere::d3Sphere( const d3Sphere& s ) :
	_center( s._center ),
	_d( s._d )
{

}

inline void d3Sphere::operator = ( const d3Sphere& s )
{
	_center = s._center;
	_d = s._d;
}

inline void d3Sphere::Mul( d3Sphere& r, const d3Sphere& a, const d3Matrix& m )
{
	d3Point::Mul( r._center, a._center, m );
}

inline void d3Sphere::GetAABB( d3AABBox& box ) const
{
	box._min = _center;
	box._max = _center;

	d3Vector v( _d, _d, _d );

	box._min -= v;
	box._max += v;
}

inline d3AABBox d3Sphere::GetAABB() const
{
	d3AABBox box;
	GetAABB( box );
	return box;
}
