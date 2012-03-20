/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d2math_matrix.h
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
 * d2Matrix
 */
class d2Matrix
{
public:
	/**
	 *
	 */
	d2Matrix();
	d2Matrix( d2Float v );

	/**
	 * 
	 */
	void SetRotate( d2Float a );
	
	/**
	 *
	 */
	void SetScale( d2Float x, d2Float y );

	/**
	 * 
	 */
	void SetTranslation( const d2Vector& v );
	void SetTranslationX( d2Float x );
	void SetTranslationY( d2Float y );

	static void Transpose( d2Matrix& r );
	void Transpose();

	/**
	 *
	 */
	static void d2Matrix::Mul( d2Matrix& r, const d2Matrix& a, const d2Matrix& b );
public:
	union {
		struct 
		{
			d2Float _11, _12, _13;
			d2Float _21, _22, _23;
			d2Float _31, _32, _33;
		};
		d2Float m[3][3];
		d2Float v[9];
	}; 
};