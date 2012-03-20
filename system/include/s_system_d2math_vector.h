/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_vector.h
//  Created                 : 4 02 2011   21:03
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
 * 2D Vector
 */
class  d2Vector
{
public:
	/**
	 * do nothing
	 */
	d2Vector();

	/**
	 * x = y = v; 
	 * w = 1.0f
	 */ 
	explicit d2Vector( d2Float v );

	/**
	 * x = vx;
	 * y = vy; 
	 * w = 1.0f;
	 */
	d2Vector( d2Float vx, d2Float vy );
  
	/**
	 * 
	 */
	explicit d2Vector( const d2Float* p );

	/**
	 * copy constructor
	 */
	d2Vector( const d2Vector& v );

	/**
	 * copy operator
	 */
	void operator = ( const d2Vector& v );
  
	/**
	 * 
	 */
	void operator = ( const d2Float* p );

	/**
	 * 
	 */
	d2Vector operator - () const;

	/**
	 * x += v
	 * y += v
	*/
	void operator += ( d2Float v );

	/**
	 * x -= v
	 * y -= v
	 */
	void operator -= ( d2Float v );

	/**
	 * x *= v
	 * y *= v
	 */
	void operator *= ( d2Float v );
  
	/**
	 * x /= v
	 * y /= v
	 */
	void operator /= ( d2Float v );

	/**
	 * x += v.x
	 * y += v.y
	 */
	void operator += ( const d2Vector& v );
  
	/**
	 * x -= v.x
	 * y -= v.y
	 */
	void operator -= ( const d2Vector& v );

	/**
	 * x *= v.x
	 * y *= v.y
	 */
	void operator *= ( const d2Vector& v );

	/**
	 * add to vectors
	 */
	d2Vector operator + ( const d2Vector& v ) const;

	/**
	 * sub to vectors
	 */
	d2Vector operator - ( const d2Vector& v ) const;

	/**
	 * Dot product
	 */
	d2Float operator * ( const d2Vector& v ) const;

	/**
	 * 
	 */
	d2Vector operator * ( d2Float v ) const;

	/**
	 * 
	 */
	sBool operator == ( const d2Vector& v ) const;

	/**
	 * 
	 */
	sBool operator != ( const d2Vector& v ) const;

	/**
	 *
	 */
	d2Vector operator / ( const d2Vector& v ) const;

	/**
	 *
	 */
	d2Vector operator / ( const d2Float f ) const;

	/**
	 * return sqrt( x*x + y*y )
	 */
	d2Float Magnitude() const;

	/**
	 * return x*x + y*y
	 */
	d2Float Magnitude2() const;

	/**
	 * returns angle relativ to x axis
	 */
	d2Float GetAngle() const;

	/**
	 * 
	 */
	d2Float Distance( const d2Vector& v ) const;

	/**
	 * Normalize
	 */
	d2Vector UnitVector() const;

	/**
	 * Add 2 vectors
	 */
	static void Add( d2Vector& r, const d2Vector& a, const d2Vector& b );

	/**
	 * Add to a list of vectors
	 */
	static void Add( d2Vector* r, sInt count, const d2Vector& a );

	/**
	 * Sub 2 vectors
	 */
	static void Sub( d2Vector& r, const d2Vector& a, const d2Vector& b );

	/**
	 * Div 2 vectors
	 */
	static void Div( d2Vector& r, const d2Vector& a, const d2Vector& b );

	/**
	 * Div 
	 */
	static void Div( d2Vector& r, const d2Vector& a, d2Float f );

	/**
	 * Sub to a list of vectors
	 */
	static void Sub( d2Vector* r, sInt count, const d2Vector& a );

	/**
	 * 
	 */
	static void Mul( d2Vector& r, const d2Vector& v, d2Float a );

	/**
	 * 
	 */
	static d2Float DotProduct(  const d2Vector& a, const d2Vector& b );

	/**
	 * v = -v;
	 */
	static void Negate( d2Vector& v );

	/**
	 * v = -v;
	 */
	static void Negate( d2Vector* r, sInt count );

	/**
	 * 
	 */
	static sBool AngleIsAcute( const d2Vector& a, const d2Vector& b );
	
	/**
	 * 
	 */
	static sBool AngleIsRight( const d2Vector& a, const d2Vector& b );
  
	/**
	 * 
	 */
	static sBool AngleIsObtuse( const d2Vector& a, const d2Vector& b );

	/**
	 * returns angle 
	 */
	static d2Float GetAngle( const d2Vector& a, const d2Vector& b );

	/**
	 * 
	 */
	static void Project( d2Vector& vn, const d2Vector& v, const d2Vector& n );

	/**
	 * vn + vp = v
	 * vn || n
	 * vp perpendicular n
	*/
	static void Project( d2Vector& vn, d2Vector& vp, const d2Vector& v, const d2Vector& n );

	/**
	 * 
	 */
	static d2Float Distance( const d2Vector& a, const d2Vector& b );

	/**
	 * returns Distance * Distance
	 */
	static d2Float DistanceSquared( const d2Vector& a, const d2Vector& b );

public: 
	union
	{
		struct 
		{
			d2Float x;
			d2Float y;
			d2Float w; // not used  
		};
		d2Float v[3];
	};
 };

/////////////////////////////////////////////////////
typedef System::Cnt::sVector<d2Vector>	d2VectorList;
typedef System::Cnt::sVector<sUInt>		d2IndexList;
