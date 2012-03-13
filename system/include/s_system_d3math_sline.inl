/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_sline.inl
//  Created                 : 12 3 2012   14:03
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

inline d3LineSegment::d3LineSegment()
{
}

inline d3LineSegment::d3LineSegment( const d3Point& start, const d3Point& end ) :
	_start( start ),
	_end( end )
{
}

inline const d3Point& d3LineSegment::Start() const
{
	return _start;
}

inline const d3Point& d3LineSegment::End() const
{
	return _end;
}

inline d3Line d3LineSegment::GetLine() const
{
	return d3Line( _start, (_end-_start).UnitVector() );
}

inline void d3LineSegment::Apply( const d3Matrix& matrix )
{
	_start.Apply( matrix );
	_end.Apply( matrix );
}
