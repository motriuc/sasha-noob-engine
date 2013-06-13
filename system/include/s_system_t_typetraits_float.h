/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_typetraits_float.h
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
class Traits< sFloat >
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
	typedef sFloat RemoveReference;

	/**
	 * Add reference
	 */
	typedef sFloat& AddReference;

	/**
	 * Add const
	 */
	typedef const sFloat AddConst;

	/**
	 * Remove const
	 */
	typedef sFloat RemoveConst;

	/**
	 * Type as function parameter
	 */
	typedef const sFloat AsInput;

	// Compare operators
	class Cmp
	{
	public:
		static sBool Big( const sFloat a, const sFloat b )
		{
			return a > b;
		}

		static sBool Equal( const sFloat a, const sFloat b )
		{
			return a == b;
		}

		static sBool Small( const sFloat a, const sFloat b )
		{
			return a < b;
		}

		static sInt Compare( const sFloat a, const sFloat b )
		{
			if( a > b )
				return 1;
			if( a == b )
				return 0;
			
			return -1;
		}
	};

};