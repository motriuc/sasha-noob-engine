/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_vector.h
//  Created                 : 1 12 2007   14:48
//  File path               : E:\Sasha\C++\SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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
 * 3D Vector
 */
class  d3Vector
{
public:
	/**
	 * do nothing
	 */
	d3Vector();

	/**
	 * x = y = z = v; 
	 * w = 1.0f
	 */ 
	explicit d3Vector( d3Float v );

	/**
	 * x = vx;
	 * y = vy; 
	 * z = vz;
	 * w = 1.0f;
	 */
	d3Vector( d3Float vx, d3Float vy, d3Float vz );
  
	/**
	 * 
	 */
	explicit d3Vector( const d3Float* p );

	/**
	 * copy constructor
	 */
	d3Vector( const d3Vector& v );

	/**
	 * copy operator
	 */
	void operator = ( const d3Vector& v );
  
	/**
	 * 
	 */
	void operator = ( const d3Float* p );

	/**
	 * 
	 */
	d3Vector operator - () const;

	/**
	 * x += v
	 * y += v
	 * z += v
	*/
	void operator += ( d3Float v );

	/**
	 * x -= v
	 * y -= v
	 * z -= v
	 */
	void operator -= ( d3Float v );

	/**
	 * x *= v
	 * y *= v
	 * z *= v
	 */
	void operator *= ( d3Float v );
  
	/**
	 * x /= v
	 * y /= v
	 * z /= v
	 */
	void operator /= ( d3Float v );

	/**
	 * x += v.x
	 * y += v.y
	 * z += v.z
	 */
	void operator += ( const d3Vector& v );
  
	/**
	 * x -= v.x
	 * y -= v.y
	 * z -= v.z
	 */
	void operator -= ( const d3Vector& v );

	/**
	 * x *= v.x
	 * y *= v.y
	 * z *= v.z
	 */
	void operator *= ( const d3Vector& v );
	
	/**
	 * add to vectors
	 */
	d3Vector operator + ( const d3Vector& v ) const;

	/**
	 * sub to vectors
	 */
	d3Vector operator - ( const d3Vector& v ) const;

	/**
	 * Dot product
	 */
	d3Float operator * ( const d3Vector& v ) const;

	/**
	 * 
	 */
	d3Vector operator * ( d3Float v ) const;

	/**
	 * cross product
	 */
	d3Vector operator ^ ( const d3Vector& v ) const;

	/**
	 * 
	 */
	sBool operator == ( const d3Vector& v ) const;

	/**
	 * 
	 */
	sBool operator != ( const d3Vector& v ) const;

	/**
	 *
	 */
	d3Vector operator / ( const d3Vector& v ) const;

	/**
	 *
	 */
	d3Vector operator / ( const d3Float f ) const;

	/**
	 * returns sqrt( x*x + y*y + z*z )
	 */
	d3Float Magnitude() const;

	/**
	 * return x*x + y*y + z*z
	 */
	d3Float Magnitude2() const;

	/**
	 * 
	 */
	d3Float Distance( const d3Vector& v ) const;

	/**
	 * Normalize
	 */
	d3Vector UnitVector() const;

	/**
	 * Add 2 vectors
	 */
	static void Add( d3Vector& r, const d3Vector& a, const d3Vector& b );

	/**
	 * Add to a list of vectors
	 */
	static void Add( d3Vector* r, sInt count, const d3Vector& a );

	/**
	 * Sub 2 vectors
	 */
	static void Sub( d3Vector& r, const d3Vector& a, const d3Vector& b );

	/**
	 * Div 2 vectors
	 */
	static void Div( d3Vector& r, const d3Vector& a, const d3Vector& b );

	/**
	 * Div 
	 */
	static void Div( d3Vector& r, const d3Vector& a, d3Float f );

	/**
	 * Sub to a list of vectors
	 */
	static void Sub( d3Vector* r, sInt count, const d3Vector& a );

	/**
	 * 
	 */
	static void Mul( d3Vector& r, const d3Vector& v, d3Float a );

	/**
	 * apply matrix
	 */
	static void Mul( d3Vector& r, const d3Vector& a, const d3Matrix& m );

	/**
	 *
	 */
	static void Mul( d3Vector* r, sInt count, const d3Matrix& m );

	/**
	 * 
	 */
	static d3Float DotProduct(  const d3Vector& a, const d3Vector& b );

	/**
	 * 
	 */
	static void CrossProduct( d3Vector& v, const d3Vector& a, const d3Vector& b );

	/**
	 * v = -v;
	 */
	static void Negate( d3Vector& v );

	/**
	 * v = -v;
	 */
	static void Negate( d3Vector* r, sInt count );

	/**
	 * 
	 */
	static sBool AngleIsAcute( const d3Vector& a, const d3Vector& b );
	
	/**
	 * 
	 */
	static sBool AngleIsRight( const d3Vector& a, const d3Vector& b );
  
	/**
	 * 
	 */
	static sBool AngleIsObtuse( const d3Vector& a, const d3Vector& b );

	/**
	 * 
	 */
	static void Project( d3Vector& vn, const d3Vector& v, const d3Vector& n );

	/**
	 * vn + vp = v
	 * vn || n
	 * vp perpendicular n
	*/
	static void Project( d3Vector& vn, d3Vector& vp, const d3Vector& v, const d3Vector& n );

	/**
	 * 
	 */
	static d3Float Distance( const d3Vector& a, const d3Vector& b );

	/**
	 * returns Distance * Distance
	 */
	static d3Float DistanceSquared( const d3Vector& a, const d3Vector& b );

public: 
	union
	{
		struct 
		{
			d3Float x;
			d3Float y;
			d3Float z;
			d3Float w; // not used  
		};
		d3Float v[4];
	};
 };

/////////////////////////////////////////////////////
typedef System::Cnt::sVector<d3Vector>	d3VectorList;
typedef System::Cnt::sVector<sUInt>		d3IndexList;
