/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_line.inl
//  Created                 : 13 3 2012
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

inline d3Line::d3Line()
{
}

inline d3Line::d3Line( const d3Point& point, const d3Vector& dir ):
	_point( point ),
	_dir( dir )
{
}

inline const d3Point& d3Line::GetPoint() const
{
	return _point;
}

inline const d3Vector& d3Line::GetDirection() const
{
	return _dir;
}
