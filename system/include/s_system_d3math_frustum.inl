/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_frustum.inl
//  Created                 : 22 1 2011   22:28
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independents   : 0%
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

inline d3Frustum::d3Frustum()
{
}

inline d3Frustum::d3Frustum( const d3Frustum& f ) :
	_planes( f._planes )
{

}

inline void d3Frustum::ClearPlanes()
{
	_planes.RemoveAll();
}

inline void d3Frustum::AddPlane( const d3Plane& p )
{
	_planes.Add( p );
}

inline void d3Frustum::operator = ( const d3Frustum& f )
{
	_planes = f._planes;
}
