/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_aabb.inl
//  Created                 : 1 12 2007   15:29
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

/************************************************************************/
/* constructors                                                         */
/************************************************************************/

inline d3AABBox::d3AABBox()
{

}

inline d3AABBox::d3AABBox( const d3Vector vmin, const d3Vector vmax ) :
	_min( vmin ),
	_max( vmax )
{
}


/************************************************************************/
/* operators                                                            */
/************************************************************************/

inline void d3AABBox::operator += ( const d3Point& v )
{
	Add( v );
}

inline void d3AABBox::operator += ( const d3AABBox& b )
{
	Add( b );
}

inline void d3AABBox::operator *= ( const d3Matrix& m )
{
	d3AABBox b;
	Mul( b, *this, m );
	*this = b;
}

inline d3AABBox d3AABBox::operator * ( const d3Matrix& m ) const
{
	d3AABBox b;
	Mul( b, *this, m );
	return b;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
 
inline d3AABBox d3AABBox::GetEmpty()
{
	d3AABBox empty;
	empty.SetEmpty();
	return empty;
} 

inline void d3AABBox::SetEmpty()
{
	_min.x = _min.y = _min.z = Limit::d3Float::Max;
	_max.x = _max.y = _max.z = Limit::d3Float::Min;
}

inline sBool d3AABBox::IsEmpty() const
{
	return 
		_min.x > _max.x || 
		_min.y > _max.y || 
		_min.z > _max.z;
}


inline void d3AABBox::Add( const d3Point& v )
{
	if( v.x < _min.x ) _min.x = v.x;
	if( v.y < _min.y ) _min.y = v.y;
	if( v.z < _min.z ) _min.z = v.z;

	if( v.x > _max.x ) _max.x = v.x;
	if( v.y > _max.y ) _max.y = v.y;
	if( v.z > _max.z ) _max.z = v.z;
}

inline void d3AABBox::Add( const d3Point* v, sInt count )
{
	for( sInt i = 0; i < count; i++ )
		Add( v[i] );
}

inline void d3AABBox::Add( const d3AABBox& b )
{
	if( b._min.x < _min.x ) _min.x = b._min.x;
	if( b._max.x > _max.x ) _max.x = b._max.x;

	if( b._min.y < _min.y ) _min.y = b._min.y;
	if( b._max.y > _max.y ) _max.y = b._max.y;

	if( b._min.z < _min.z ) _min.z = b._min.z;
	if( b._max.z > _max.z ) _max.z = b._max.z;
}

inline void d3AABBox::Add( const d3AABBox* v, sInt count )
{
	for( sInt i = 0; i < count; i++ )
		Add( v[i] );
}

/************************************************************************/
/* Size                                                                 */
/************************************************************************/

inline void d3AABBox::GetSize( d3Vector& v ) const
{
	v = _max - _min;
}

inline d3Vector d3AABBox::GetSize() const
{
	return _max - _min;
}

inline d3Float d3AABBox::GetSizeX() const
{
	return _max.x - _min.x;
}

inline d3Float d3AABBox::GetSizeY() const
{
	return _max.y - _min.y;
}

inline d3Float d3AABBox::GetSizeZ() const
{
	return _max.z - _min.z;
}

inline void d3AABBox::GetCenter( d3Vector& v )
{
	v = ( _min + _max ) * 0.5f;
}

inline d3Float d3AABBox::GetVolume() const
{
	return GetSizeX() * GetSizeY() * GetSizeZ();
}

inline void d3AABBox::GetCorner( d3Point& v, sInt i ) const
{
	__S_ASSERT( i >= 0 );
	__S_ASSERT( i <= 7 );

	v.x = ( i & 1 )  ? _max.x : _min.x;
	v.y = ( i & 2 )  ? _max.y : _min.y;
	v.z = ( i & 4 )  ? _max.z : _min.z;
}

inline d3Point d3AABBox::GetCorner( sInt i ) const
{
	d3Vector v;
	GetCorner( v, i );

	return v;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
inline void d3AABBox::ClosestTo( d3Vector& r, const d3Vector& a ) const
{
	if( a.x < _min.x )
		r.x = _min.x;
	else if( a.x > _max.x )
		r.x = _max.x;
	else
		r.x = a.x;
  
	if( a.y < _min.y )
		r.y = _min.y;
	else if( a.y > _max.y )
		r.y = _max.y;
	else
		r.y = a.y;

	if( a.z < _min.z )
		r.z = _min.z;
	else if( a.z > _max.z )
		r.z = _max.z;
	else
		r.z = a.z;
}

/************************************************************************/
/* intersection                                                         */
/************************************************************************/
inline sBool d3AABBox::Intersect( const d3AABBox& b ) const
{
	return Intersect( *this, b );
}

inline sBool d3AABBox::Intersect( const d3Point& v ) const
{
	return Intersect( *this, v );
}

inline sBool d3AABBox::Intersect( const d3AABBox& a, const d3AABBox& b )
{
	return 
		a._min.x <= b._max.x &&
		a._max.x >= b._min.x &&

		a._min.y <= b._max.y &&
		a._max.y >= b._min.y &&

		a._min.z <= b._max.z &&
		a._max.z >= b._min.z;
}

inline sBool d3AABBox::Intersect( d3AABBox& r, const d3AABBox& a, const d3AABBox& b )
{
	if( Intersect( a, b ) )
	{
		r._min.x = FMath::Max( a._min.x, b._min.x );
		r._max.x = FMath::Min( a._max.x, b._max.x );

		r._min.y = FMath::Max( a._min.y, b._min.y );
		r._max.y = FMath::Min( a._max.y, b._max.y );

		r._min.z = FMath::Max( a._min.z, b._min.z );
		r._max.z = FMath::Min( a._max.z, b._max.z );

		return sTrue;
	}
  
	return sFalse;
}

inline sBool d3AABBox::Intersect( const d3AABBox& b, const d3Point& v )
{
	return 
		v.x >= b._min.x && v.x <= b._max.x &&
		v.y >= b._min.y && v.y <= b._max.y &&
		v.z >= b._min.z && v.z <= b._max.z;
}

inline sBool d3AABBox::Intersect( const d3AABBox& b, const d3Sphere& s )
{
	d3Vector closestPoint;
	b.ClosestTo( closestPoint, s._center );

	return d3Vector::DistanceSquared( closestPoint, s._center ) < s._d * s._d;
}

inline void d3AABBox::SplitByX( d3AABBox& a, d3AABBox& b ) const
{
	a = *this;
	b = *this;

	b._min.x = a._max.x = ( _min.x + _max.x ) * 0.5f;
}

inline void d3AABBox::SplitByY( d3AABBox& a, d3AABBox& b ) const
{
	a = *this;
	b = *this;

	b._min.y = a._max.y = ( _min.y + _max.y ) * 0.5f;
}

inline void d3AABBox::SplitByZ( d3AABBox& a, d3AABBox& b ) const
{
	a = *this;
	b = *this;

	b._min.z = a._max.z = ( _min.z + _max.z ) * 0.5f;
}

inline void d3AABBox::SplitById( sInt id, d3AABBox& a, d3AABBox& b ) const
{
	__S_ASSERT( id >= 0 );
	__S_ASSERT( id < 3 );

	a = *this;
	b = *this;

	b._min.v[id] = a._max.v[id] = ( _min.v[id] + _max.v[id] ) * 0.5f;
}


