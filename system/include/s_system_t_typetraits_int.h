/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_typetraits_int.h
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
class Traits< sInt >
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
	typedef sInt RemoveReference;

	/**
	 * Add reference
	 */
	typedef sInt& AddReference;

	/**
	 * Add const
	 */
	typedef const sInt AddConst;

	/**
	 * Remove const
	 */
	typedef sInt RemoveConst;

	// Compare operators
	class Cmp
	{
	public:
		static sBool Big( const sInt a, const sInt b )
		{
			return a > b;
		}

		static sBool Equal( const sInt a, const sInt b )
		{
			return a == b;
		}

		static sBool Small( const sInt a, const sInt b )
		{
			return a < b;
		}

		static sInt Compare( const sInt a, const sInt b )
		{
			return a - b;
		}
	};

};

