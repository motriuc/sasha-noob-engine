/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_int.h
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


namespace Shape
{

inline sBool Intersect( const d3Sphere& s, const d3AABBox& b )
{
	return d3AABBox::Intersect( b, s );
}

inline sBool Intersect( const d3AABBox& b, const d3Sphere& s )
{
	return d3AABBox::Intersect( b, s );
}

inline sBool Intersect( const d3AABBox& a, const d3AABBox& b )
{
	return d3AABBox::Intersect( a, b );
}

inline sBool Intersect( const d3Frustum& f, const d3AABBox& b )
{
	return f.Intersect( b );
}

inline sBool Intersect( const d3AABBox& b, const d3Frustum& f )
{
	return f.Intersect( b );
}


}