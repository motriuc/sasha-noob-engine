/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_math.inl
//	Created                 : 25 6 2007   0:15
//	File path               : C:\Sasha\C++\SLibF\system\Include
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

inline sInt Max( sInt a, sInt b ) { return a > b ? a : b; }
inline sUInt Max( sUInt a, sUInt b ) { return a > b ? a : b; }
inline sFloat Max( sFloat a, sFloat b ) { return a > b ? a : b; }
inline sDouble Max( sDouble a, sDouble b ) { return a > b ? a : b; }

inline sInt Min( sInt a, sInt b ) { return a < b ? a : b; }
inline sUInt Min( sUInt a, sUInt b ) { return a < b ? a : b; }
inline sFloat Min( sFloat a, sFloat b ) { return a < b ? a : b; }
inline sDouble Min( sDouble a, sDouble b ) { return a < b ? a : b; }


inline sInt Min( sInt a, sInt b, sInt c )
{
	a = a < b ? a : b;
	return a < c ? a : c; 
}

inline sInt Clamp( sInt v, sInt min, sInt max )
{
	if( v < min )
		return min;
	if( v > max )
		return max;
		
	return v;
}

inline sFloat Clamp( sFloat v, sFloat min, sFloat max )
{
	if( v < min )
		return min;
	if( v > max )
		return max;
		
	return v;
}

inline sDouble Clamp( sDouble v, sDouble min, sDouble max )
{
	if( v < min )
		return min;
	if( v > max )
		return max;
		
	return v;
}

inline sDouble Fraction( sDouble n )
{
	return fmod( n, 1.0 );
}

inline sFloat Fraction( sFloat n )
{
	return fmod( n, 1.0f );
}

inline sDouble Integer( sDouble n )
{
	return n - fmod( n, 1.0 );
}

inline sFloat Integer( sFloat n )
{
	return n - fmod( n, 1.0f );
}

inline sFloat BigerInt( sFloat n )
{
	sFloat v = Integer( n );

	if( v < n )
		v += 1.0f;

	return v;
}

inline sFloat SmallerInt( sFloat n )
{
	sFloat v = Integer( n );

	if( v > n )
		v -= 1.0f;

	return v;
}

inline sFloat Sqrt( sFloat v )
{
	return sqrtf( v );
}

inline sFloat Sin( sFloat a )
{
    return sinf( a );
}

inline sFloat Cos( sFloat a )
{
    return cosf( a );
}

inline sInt Abs( sInt a )
{
	return a >= 0 ? a : -a;
}

inline sFloat Abs( sFloat a )
{
	return fabsf( a );
}

inline sFloat Tan( sFloat a )
{
	return tanf( a );
}

inline sFloat CoTan( sFloat a )
{
	return 1.0f / tanf( a );
}

inline sFloat Pow2( sFloat a )
{
	return a * a;
}

inline sFloat DegreeToRad( sFloat v )
{
	return ( fPi / 180.0f ) * v;
}

inline sInt Sign( sInt v )
{
	return v < 0 ? -1 : 1;
}

inline sFloat ATan2( sFloat x, sFloat y )
{
	return atan2( y, x );
}

inline sFloat Round( sFloat n )
{
#ifdef _SPL_WIN32
	if( n >= 0.0f )
		return Integer( n + 0.5f );
	return Integer( n - 0.5f );
#else
	return roundf( n );
#endif
}

inline sInt UpperPowOf2Number( sInt v )
{
	sInt n = 1;
	
	while( n < v )
	{
		n <<= 1;
	}
	return n;
}

inline sInt Log2( sInt v )
{
	sInt r = 0;
	while( v >>=1 )
		++r;
		
	return r;
}

inline sInt PowOf2( sInt v )
{
	__S_ASSERT( v >= 0 );
	return 1 << v;
}

inline sBool IsPowOf2( sInt v )
{
	return (v > 0) && ( (v & (v - 1) ) == 0);
}

inline bool CloseToZero( const sFloat& a )
{
	return Abs( a ) <= Limit::sFloat::Precision;
}

//------------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------------

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