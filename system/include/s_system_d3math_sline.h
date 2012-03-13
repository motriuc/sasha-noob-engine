/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_sline.h
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

/**
 * d3LineSegment
 */
class d3LineSegment
{
public:
	/**
	 *
	 */
	d3LineSegment();

	/**
	 *
	 */
	d3LineSegment( const d3Point& start, const d3Point& end );
private:
	d3Point		_start;
	d3Point		_end;
};