/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_random.h
//  Created                 : 15 6 2007   21:54
//  File path               : SLibF\system\include
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

namespace RMath
{

using namespace System::Types;

/**
 * A basic fast random number generator
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

#include "s_system_random.inl"

}
