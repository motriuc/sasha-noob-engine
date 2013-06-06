/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_quaternion.h
//  Created                 : 9 3 2012   14:03
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 * d3Quaternion
 */
class d3Quaternion
{
public:
	/**
	 *
	 */
	d3Quaternion();

	/**
	 * 
	 */
	d3Quaternion( d3Float vx, d3Float vy, d3Float vz, d3Float vw );

	/**
	 * From Euler
	 * @param ax Rotation in radians around the x axis 
	 * @param ay Rotation in radians around the y axis 
	 * @param az Rotation in radians around the z axis 
	 */
	d3Quaternion( d3Float ax, d3Float ay, d3Float az );

	/**
	 * Returns the magnitude of a quaternion
	 * sqrt( x*x + y*x + z*z )
	 */
	d3Float Magnitude() const;

	/**
	 * Multiplies two quaternions
	 */
	d3Quaternion operator * ( const d3Quaternion& b );

	/**
	 * Multiplies two quaternions
	 */
	static void Mul( d3Quaternion& r, const d3Quaternion& a, const d3Quaternion& b );
public:
	union
	{
		struct 
		{
			d3Float x;
			d3Float y;
			d3Float z;
			d3Float w;  
		};
		d3Float v[4];
	};
};

typedef System::Cnt::sVector<d3Quaternion>	d3QuaternionList;
