/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_math.h
//	Created                 : 24 6 2007   2:05
//	File path               : SLibF\system\Include
//	Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//	Library                 : 
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
#ifndef _SYSTEM_MATH_INC_
#define _SYSTEM_MATH_INC_

/**
 *	Math functions
 */
namespace FMath
{
using namespace Types;

/**
 *	Pi values
 */
const sFloat  fPi  = 3.141592654f;
const sFloat  f2Pi = 2.0f * fPi;
const sDouble dPi  = 3.1415926535897932384626433832795;
const sDouble d2Pi  = 2.0 * d2Pi;

/**
 *	Max functions
 */
sInt Max( sInt a, sInt b );
sUInt Max( sUInt a, sUInt b );
sFloat Max( sFloat a, sFloat b );
sDouble Max( sDouble a, sDouble b );

/**
 *	Min functons
 */
sInt Min( sInt a, sInt b );
sUInt Min( sUInt a, sUInt b );
sFloat Min( sFloat a, sFloat b );
sDouble Min( sDouble a, sDouble b );
	
sInt Min( sInt a, sInt b, sInt c );

sInt Clamp( sInt v, sInt min, sInt max );
sFloat Clamp( sFloat v, sFloat min, sFloat max );
sDouble Clamp( sDouble v, sDouble min, sDouble max );
	
/**
 *	Abs functions
 */
sInt Abs( sInt v );
sFloat Abs( sFloat v );
sDouble Abs( sDouble v );

/**
 *	Sgn Functions
 *	@return -1 if v < 0, 1 if v >= 0
 */
sInt Sign( sInt v );
sFloat Sign( sFloat v );
sDouble Sign( sDouble v );

/**
 *	gets the fraction part from number
 */
sFloat Fraction( sFloat n );
sDouble Fraction( sDouble n );

/**
 * The round functions return the integral value nearest to n 
 * rounding half-way cases away from zero, regardless of the current rounding direction
 */
sFloat Round( sFloat n );
sDouble Round( sDouble n );
	
/**
 * get integer part from number
 */
sFloat Integer( sFloat n );
sDouble Integer( sDouble n );

/**
 * Returns first biggest integer from n 
 * 2.0 -> 2
 * 2.1 -> 3
 * 2.9 -> 3
 *
 * -2.0 -> 2
 * -2.1 -> 2
 * -2.9 -> 2
 */
sFloat BigerInt( sFloat n );
sDouble BigerInt( sDouble n );

/**
 * Returns smallest biggest integer from n 
 * 2.0 -> 2
 * 2.1 -> 2
 * 2.9 -> 2
 *
 * -2.0 -> 2
 * -2.1 -> 3
 * -2.9 -> 3
 */
sFloat SmallerInt( sFloat n );
sDouble SmallerInt( sDouble n );

/**
 *
 */
sFloat Sqrt( sFloat v );
sDouble Sqrt( sDouble v );

/**
 * Sin
 */
sFloat Sin( sFloat a );
sDouble Sin( sDouble a );

/**
 * Cos
 */
sFloat Cos( sFloat a );
sDouble Cos( sDouble a );

/**
 *
 */
sFloat Tan( sFloat a );
sDouble Tan( sDouble a );
	
/**
 *	returns 1/tan(a)
 */
sFloat CoTan( sFloat a );
sDouble CoTan( sDouble a );

/**
 * This function computes the angle, in the range [-Pi..Pi] radians, 
 * whose tangent is y/x. In other words, it computes the angle, in radians, 
 * of the vector (x,y) with respect to the +x axis, reckoning the 
 * counterclockwise direction as positive, and returning the value in the range [-Pi, Pi].
 */
sFloat ATan2( sFloat x, sFloat y );
sDouble ATan2( sDouble x, sDouble y ); 

/**
 * power of a^2
 */
sFloat Pow2( sFloat a );	
sDouble Pow2( sDouble a );
	
/**
 *	Converts Degree to Radian
 */
sFloat DegreeToRad( sFloat v );
sDouble DegreeToRad( sDouble v ); 

/**
 * Log2(v)
 */
sInt Log2( sInt v );
sFloat Log2( sFloat v );
sDouble Log2( sDouble v );	

/**
 * returns 2^v
 */
sInt PowOf2( sInt v );
sFloat PowOf2( sFloat v );
sDouble PowOf2( sDouble v );
	

/**
 * returns truw if number is 2^n
 */
sBool IsPowOf2( sInt v );
	
/**
 * returns the closest and bigest number of type 2^n
 */
sInt UpperPowOf2Number( sInt v );

/**
 * Random
 */
class Random
{
public:
	Random( sUInt seed = 0 );

	/**
	 * Set Rand seed
	 */
	void SetRand( sUInt seed );

	/**
	 *
	 */
	void SetRandomSeed();

	/**
	 * Randomize number from 0..MaxRand
	 */
	sInt Rand();

	/**
	 * Returns randmax
	 */
	sInt GetMaxRand();

	/**
	 * Randomize a number
	 */
	sInt Rand( sInt MaxRand, sInt MinRand = 0 );

	/**
	 * Randomize a float number
	 */
	sFloat Rand( sFloat MaxRand, sFloat MinRand = 0.0f );

	/**
	 * Bool Randomize
	 */
	sBool RandBool();

private:
	SDWORD	_seed;
};


#include "s_system_math.inl"

}

#endif // _SYSTEM_MATH_INC_
