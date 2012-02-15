/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_typetraits.h
//	Created                 : 28 6 2007   23:19
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

/////////////////////////////////////////////////////////////////////
// default type traits
template< typename _TYPE >
class Traits
{
public:

	// some type information options
	enum 
	{
		DefaultTraits = true,   // means that default this is default traits true must be only here
		BasicType = false		//  true means it is part of basic system types and dosn't need consturctos to operate 
	};

	// Compare operators
	class Cmp
	{
	public:
		inline static System::Types::sBool Big( const _TYPE& a, const _TYPE& b )
		{
			return a > b;
		}

		inline static System::Types::sBool Equal( const _TYPE& a, const _TYPE& b )
		{
			return a == b;
		}

		inline static System::Types::sBool Small( const _TYPE& a, const _TYPE& b )
		{
			return a < b;
		}

		inline static System::Types::sInt Compare( const _TYPE& a, const _TYPE& b )
		{
			if( a > b )
				return 1;
			if( a == b )
				return 0;
			
			return -1;
		}
	};
};

///////////////////////////////////////////////////////////////////////////////////////
// sInt type traits
template<>
class Traits<System::Types::sInt>
{
public:
	// some type information options
	enum 
	{
		DefaultTraits = false,   // means that default this is default traits true must be only here
		BasicType = true		//  true means it is part of basic system types and dosn't need consturctos to operate 
	};

	// Compare operators
	class Cmp
	{
	public:
		inline static System::Types::sBool Big( const System::Types::sInt& a, const System::Types::sInt& b )
		{
			return a > b;
		}

		inline static System::Types::sBool Equal( const System::Types::sInt& a, const System::Types::sInt& b )
		{
			return a == b;
		}

		inline static System::Types::sBool Small( const System::Types::sInt& a, const System::Types::sInt& b )
		{
			return a < b;
		}

		inline static System::Types::sInt Compare( const System::Types::sInt& a, const System::Types::sInt& b )
		{
			return a - b;
		}
	};

};

///////////////////////////////////////////////////////////////////////////////////////
// sUInt type traits
template<>
class Traits<System::Types::sUInt>
{
public:
	// some type information options
	enum 
	{
		DefaultTraits = false,   // means that default this is default traits true must be only here
		BasicType = true		//  true means it is part of basic system types and dosn't need consturctos to operate 
	};

	// Compare operators
	class Cmp
	{
	public:
		inline static System::Types::sBool Big( const System::Types::sUInt& a, const System::Types::sUInt& b )
		{
			return a > b;
		}

		inline static System::Types::sBool Equal( const System::Types::sUInt& a, const System::Types::sUInt& b )
		{
			return a == b;
		}

		inline static System::Types::sBool Small( const System::Types::sUInt& a, const System::Types::sUInt& b )
		{
			return a < b;
		}

		inline static System::Types::sInt Compare( const System::Types::sUInt& a, const System::Types::sUInt& b )
		{
			return (System::Types::sInt)( a - b );
		}
	};
};
