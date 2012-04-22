/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d2math_rect.inl
//  Created                 : 20 3 2012
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

//-------------------------------------------------------------------
inline d2Rectangle::d2Rectangle()
{
}

//-------------------------------------------------------------------
inline d2Rectangle::d2Rectangle( const d2Point& min, const d2Point& max ):
	_min( min ),
	_max( max )
{
}

//-------------------------------------------------------------------
inline void d2Rectangle::SetEmpty()
{
	_min.x = _min.y = Limit::d2Float::Max;
	_max.x = _max.y = Limit::d2Float::Min;
}

//-------------------------------------------------------------------
inline sBool d2Rectangle::IsEmpty() const
{
	return _min.x > _max.x || _min.y > _max.y;
}

//-------------------------------------------------------------------
inline sBool d2Rectangle::Intersect( const d2Point& p ) const
{
	return Intersect( *this, p );
}

//-------------------------------------------------------------------
inline sBool d2Rectangle::Contains( const d2Rectangle& r ) const
{
	return Intersect( r.Min() ) && Intersect( r.Max() );
}

//-------------------------------------------------------------------
inline sBool d2Rectangle::Intersect( const d2Rectangle& b, const d2Point& p )
{
	return
		p.x >= b._min.x && p.x <= b._max.x &&
		p.y >= b._min.y && p.y <= b._max.y;
}

//-------------------------------------------------------------------
inline sBool d2Rectangle::Intersect( const d2Rectangle& a, const d2Rectangle& b )
{
	return 
		a._min.x <= b._max.x &&
		a._max.x >= b._min.x &&

		a._min.y <= b._max.y &&
		a._max.y >= b._min.y;
}

//-------------------------------------------------------------------
inline void d2Rectangle::Add( const d2Point& v )
{
	if( v.x < _min.x ) _min.x = v.x;
	if( v.y < _min.y ) _min.y = v.y;

	if( v.x > _max.x ) _max.x = v.x;
	if( v.y > _max.y ) _max.y = v.y;
}

//-------------------------------------------------------------------
inline void d2Rectangle::Add( const d2Point* v, sInt count )
{
	for( sInt i = 0; i < count; i++ )
		Add( v[i] );
}

//-------------------------------------------------------------------
inline void d2Rectangle::Add( const d2Rectangle& b )
{
	if( b._min.x < _min.x ) _min.x = b._min.x;
	if( b._max.x > _max.x ) _max.x = b._max.x;

	if( b._min.y < _min.y ) _min.y = b._min.y;
	if( b._max.y > _max.y ) _max.y = b._max.y;
}

//-------------------------------------------------------------------
inline void d2Rectangle::Add( const d2Rectangle* v, sInt count )
{
	for( sInt i = 0; i < count; i++ )
		Add( v[i] );
}

//-------------------------------------------------------------------
inline const d2Point& d2Rectangle::Min() const
{
	return _min;
}

//-------------------------------------------------------------------
inline const d2Point& d2Rectangle::Max() const
{
	return _max;
}