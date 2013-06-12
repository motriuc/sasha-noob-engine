/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_typetraits_char.h
//  Created                 : 11 6 2013   23:19
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

template<>
class Traits< sChar >
{
public:
	// some type information options
	enum 
	{
		IsDefault = false,		// true if this is default type definition.
		IsBasicType = true,		// true if the type is a basic type and it's copy constructor and = operator are compiler default
		IsReference = false,	// true if type is referene type
		IsConst = false,		// true if type is const
		IsNumber = false,		// true is type is a number
	};

	/**
	 * Remove reference
	 */
	typedef sChar RemoveReference;

	/**
	 * Add reference
	 */
	typedef sChar& AddReference;

	/**
	 * Add const
	 */
	typedef const sChar AddConst;

	/**
	 * Remove const
	 */
	typedef sChar RemoveConst;

	// Compare operators
	class Cmp
	{
	public:
		static sBool Big( const sChar a, const sChar b )
		{
			return a > b;
		}

		static sBool Equal( const sChar a, const sChar b )
		{
			return a == b;
		}

		static sBool Small( const sChar a, const sChar b )
		{
			return a < b;
		}

		static sInt Compare( const sChar a, const sChar b )
		{
			return static_cast<sInt>(a - b);
		}
	};

};

