/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_random.inl
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

inline Random::Random( sUInt seed ) :
	_seed( (SDWORD)seed )
{
}

inline void Random::SetRandomSeed()
{
	_seed = (SDWORD)System::Platform::GetTick();
}

inline void Random::SetRand( sUInt seed )
{
	_seed = (SDWORD)seed;
}

inline sInt Random::Rand()
{
	return (((_seed = _seed * 214013L + 2531011L) >> 16) & 0x7fff);
}

inline sInt Random::GetMaxRand()
{
	return 32767;
}

inline sBool Random::RandBool()
{
	return Rand() > 16383;
}

inline sFloat Random::Rand( sFloat MaxRand, sFloat MinRand )
{
  __S_ASSERT( MaxRand >= MinRand );

  return MinRand + ( MaxRand - MinRand ) * Rand() / GetMaxRand();
}

inline sInt Random::Rand( sInt MaxRand, sInt MinRand )
{
	__S_ASSERT( MaxRand >= MinRand );

	return  MinRand + ( ( MaxRand - MinRand ) * Rand() + GetMaxRand() / 2 ) / GetMaxRand();
}
