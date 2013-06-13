/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_typetraits_default.h
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

template< typename _Type >
class Traits
{
public:

	// some type information options
	enum 
	{
		IsDefault = true,		// true if this is default type definition.
		IsBasicType = false,	// true if the type is a basic type and it's copy constructor and = operator are compiler default
		IsReference = false,	// true if type is referene type
		IsConst = false,		// true if type is const
		IsNumber = false		// true if type is a number
	};

	/**
	 * Remove reference
	 */
	typedef _Type RemoveReference;

	/**
	 * Add reference
	 */
	typedef _Type& AddReference;

	/**
	 * Add const
	 */
	typedef const _Type AddConst;

	/**
	 * Remove const
	 */
	typedef _Type RemoveConst;

	/**
	 * Type as function parameter
	 */
	typedef const _Type& AsInput;

	// Compare operators
	class Cmp
	{
	public:
		static sBool Big( const _Type& a, const _Type& b )
		{
			return a > b;
		}

		static sBool Equal( const _Type& a, const _Type& b )
		{
			return a == b;
		}

		static sBool Small( const _Type& a, const _Type& b )
		{
			return a < b;
		}

		static sInt Compare( const _Type& a, const _Type& b )
		{
			if( a > b )
				return 1;
			if( a == b )
				return 0;
			
			return -1;
		}
	};
};

