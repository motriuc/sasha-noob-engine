/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_triangle.inl
//  Created                 : 3 12 2007   19:49
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

inline d3Triangle::d3Triangle( const d3Triangle& tr ):
	_a( tr._a ),
	_b( tr._b ),
	_c( tr._c )
{
}

inline void d3Triangle::operator = ( const d3Triangle& tr )
{
	_a = tr._a;
	_b = tr._b;
	_c = tr._c;
}

inline void d3Triangle::GetAABB( d3AABBox& box )
{
	box.SetEmpty();
	box.Add( _a );
	box.Add( _b );
	box.Add( _c );
}
