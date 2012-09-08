/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_typetraits.h
//  Created                 : 28 6 2007   23:19
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

/////////////////////////////////////////////////////////////////////
// default type traits
template< typename _TYPE >
class Traits
{
public:

	// some type information options
	enum 
	{
		DefaultTraits = true,   // ture means this is default type traits provided by the library.
		BasicType = false		//  true means that the type is a basic type and it's copy constructor and operator are compiler default 
	};

	// Compare operators
	class Cmp
	{
	public:
		inline static sBool Big( const _TYPE& a, const _TYPE& b )
		{
			return a > b;
		}

		inline static sBool Equal( const _TYPE& a, const _TYPE& b )
		{
			return a == b;
		}

		inline static sBool Small( const _TYPE& a, const _TYPE& b )
		{
			return a < b;
		}

		inline static sInt Compare( const _TYPE& a, const _TYPE& b )
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
		DefaultTraits = false,
		BasicType = true 
	};

	// Compare operators
	class Cmp
	{
	public:
		inline static sBool Big( const sInt& a, const sInt& b )
		{
			return a > b;
		}

		inline static sBool Equal( const sInt& a, const sInt& b )
		{
			return a == b;
		}

		inline static sBool Small( const sInt& a, const sInt& b )
		{
			return a < b;
		}

		inline static sInt Compare( const sInt& a, const sInt& b )
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
		DefaultTraits = false,
		BasicType = true 
	};

	// Compare operators
	class Cmp
	{
	public:
		inline static sBool Big( const sUInt& a, const sUInt& b )
		{
			return a > b;
		}

		inline static sBool Equal( const sUInt& a, const sUInt& b )
		{
			return a == b;
		}

		inline static sBool Small( const sUInt& a, const sUInt& b )
		{
			return a < b;
		}

		inline static sInt Compare( const sUInt& a, const sUInt& b )
		{
			return static_cast<sInt>( a - b );
		}
	};
};


///////////////////////////////////////////////////////////////////////////////////////
// sFloat type traits

template<>
class Traits<System::Types::sFloat>
{
public:

	// some type information options
	enum 
	{
		DefaultTraits = true,   // ture means this is default type traits provided by the library.
		BasicType = true		//  true means that the type is a basic type and it's copy constructor and operator are compiler default 
	};

	// Compare operators
	class Cmp
	{
	public:
		inline static sBool Big( const sFloat& a, const sFloat& b )
		{
			return a > b;
		}

		inline static sBool Equal( const sFloat& a, const sFloat& b )
		{
			return a == b;
		}

		inline static sBool Small( const sFloat& a, const sFloat& b )
		{
			return a < b;
		}

		inline static sInt Compare( const sFloat& a, const sFloat& b )
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
// sFloat type traits

template<>
class Traits<System::Types::sDouble>
{
public:

	// some type information options
	enum 
	{
		DefaultTraits = true,   // ture means this is default type traits provided by the library.
		BasicType = true		//  true means that the type is a basic type and it's copy constructor and operator are compiler default 
	};

	// Compare operators
	class Cmp
	{
	public:
		inline static sBool Big( const sDouble& a, const sDouble& b )
		{
			return a > b;
		}

		inline static sBool Equal( const sDouble& a, const sDouble& b )
		{
			return a == b;
		}

		inline static sBool Small( const sDouble& a, const sDouble& b )
		{
			return a < b;
		}

		inline static sInt Compare( const sDouble& a, const sDouble& b )
		{
			if( a > b )
				return 1;
			if( a == b )
				return 0;
			
			return -1;
		}
	};
};
