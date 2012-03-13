/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_line.h
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

/**
 * d3Line
 */
class d3Line
{
public:
	/**
	 *
	 */
	d3Line();

	/**
	 *
	 */
	d3Line( const d3Point& point, const d3Vector& dir );

	/**
	 *
	 */
	const d3Point& GetPoint() const;

	/**
	 *
	 */
	const d3Vector& GetDirection() const;
private:
	d3Point		_point;
	d3Vector	_dir;	// must be unit vector
};