/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_typetraits_uint.h
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
class Traits< sUInt >
{
public:
	// some type information options
	enum 
	{
		IsDefault = false,		// true if this is default type definition.
		IsBasicType = true,		// true if the type is a basic type and it's copy constructor and = operator are compiler default
		IsReference = false,	// true if type is referene type
		IsConst = false,		// true if type is const
		IsNumber = true,		// true is type is a number
	};

	/**
	 * Remove reference
	 */
	typedef sUInt RemoveReference;

	/**
	 * Add reference
	 */
	typedef sUInt& AddReference;

	/**
	 * Add const
	 */
	typedef const sUInt AddConst;

	/**
	 * Remove const
	 */
	typedef sUInt RemoveConst;

	/**
	 * Type as function parameter
	 */
	typedef const sUInt AsInput;

	// Compare operators
	class Cmp
	{
	public:
		static sBool Big( const sUInt a, const sUInt b )
		{
			return a > b;
		}

		static sBool Equal( const sUInt a, const sUInt b )
		{
			return a == b;
		}

		static sBool Small( const sUInt a, const sUInt b )
		{
			return a < b;
		}

		static sInt Compare( const sUInt a, const sUInt b )
		{
			return a - b;
		}
	};
};

