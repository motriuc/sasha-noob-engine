/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d2math_rect.h
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

/**
 * d2Rectangle
 */
class d2Rectangle
{
public:
	/**
	 *
	 */
	d2Rectangle();

	/**
	 *
	 */
	d2Rectangle( const d2Point& min, const d2Point& max );

	/**
	 *
	 */
	void SetEmpty();
	sBool IsEmpty() const;

	void Add( const d2Point& v );
	void Add( const d2Point* v, sInt count );

	void Add( const d2Rectangle& b );
	void Add( const d2Rectangle* v, sInt count );

	/**
	 *
	 */
	sBool Intersect( const d2Point& p ) const;

	/**
	 * Intersect functions
	 */
	static sBool Intersect( const d2Rectangle& b, const d2Point& p );
	static sBool Intersect( const d2Rectangle& a, const d2Rectangle& b );

	const d2Point& Min() const;
	const d2Point& Max() const;

private:
	d2Point	_min;
	d2Point	_max;
};