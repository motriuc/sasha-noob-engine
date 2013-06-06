/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_formaters.h
//  Created                 : 28 4 2012   4:28
//  File path               : SLibF\system\include
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
 * Default formater which will give a compilation error
 */
template< typename _Type >
class StringFormater
{
};

/**
 * sInt formater
 */
template<>
class StringFormater< Types::sInt >
{
public:
	static Types::sInt EstimateSize( const Types::sInt& v )
	{
		if( v >= 0 )
		{
			if( v < 10 )
				return 1;

			if( v < 100 )
				return 2;

			if( v < 1000 )
				return 3;

			if( v < 10000 )
				return 4;
		}
		else
		{
			if( v > -10 )
				return 2;

			if( v > -100 )
				return 3;

			if( v > -1000 )
				return 4;
		}

		return 11;
	}

	static Types::sInt Convert( const Types::sInt& v, Types::sChar* chars )
	{
		Chars::FromInt( chars, v );
		return Chars::Length( chars );
	}
};

/**
 * sInt formater
 */
template<>
class StringFormater< Types::sUInt >
{
public:
	static Types::sInt EstimateSize( const Types::sUInt& v )
	{
        if( v < 10 )
            return 1;

        if( v < 100 )
            return 2;

        if( v < 1000 )
            return 3;

        if( v < 10000 )
            return 4;
        
        if( v < 100000 )
            return 5;

        if( v < 1000000 )
            return 6;

		return 11;
	}

	static Types::sInt Convert( const Types::sInt& v, Types::sChar* chars )
	{
		Chars::FromUInt( chars, v );
		return Chars::Length( chars );
	}
};

/**
 * Float formater
 */
template<>
class StringFormater< Types::sFloat >
{
public:
	static Types::sInt EstimateSize( const Types::sFloat& v )
	{
		return 18;
	}

	static Types::sInt Convert( const Types::sFloat& v, Types::sChar* chars )
	{
		Chars::FromFloat( chars, v );
		return Chars::Length( chars );
	}
};

/**
 * Double formater
 */
template<>
class StringFormater< Types::sDouble >
{
public:
	static Types::sInt EstimateSize( const Types::sDouble& v )
	{
		return 24;
	}

	static Types::sInt Convert( const Types::sDouble& v, Types::sChar* chars )
	{
		Chars::FromDouble( chars, v );
		return Chars::Length( chars );
	}
};

