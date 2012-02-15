/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_limit.h
//	Created                 : 24 6 2007   23:47
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
#ifndef _S_SYSTEM_LIMIT_INC_
#define _S_SYSTEM_LIMIT_INC_

/**
 *	Limits
 */
namespace Limit
{
	/**
	 *	SDWORD
	 */
	namespace SDWORD
	{
		/**
		 *	Max SDWORS
		 */
		const Types::SDWORD Max			= 0xFFFFFFFF;

		/**
		 *	Min SDWORD
		 */
		const Types::SDWORD Min			= 0x00000000;
	}

	/**
	 *	SWORD
	 */
	namespace SWORD
	{
		const Types::SWORD Max			= 0xFFFF;
		const Types::SWORD Min			= 0x0000;
	}

	namespace SBYTE
	{
		const Types::SBYTE Max			= 0xFF;
		const Types::SBYTE Min			= 0x00;
	}

	namespace SINT32
	{
		const Types::SINT32 Max			= 2147483647;
		const Types::SINT32 Min			= (-2147483647 - 1);
	}

	namespace sInt
	{
#if defined( _SPL_WIN32 ) || defined ( _SPL_MAC )
		const Types::sInt Max			= SINT32::Max;
		const Types::sInt Min			= SINT32::Min;
#endif
	}

	namespace sUInt
	{
#if defined( _SPL_WIN32 ) || defined ( _SPL_MAC )
		const Types::sUInt Max			= SDWORD::Max;
		const Types::sUInt Min			= SDWORD::Min;
#endif
	}
	
	namespace SUINT64  
	{
		const Types::SUINT64 Max		= 0xFFFFFFFFFFFFFFFFLL;
		const Types::SUINT64 Min		= 0x0000000000000000LL;
	}

	namespace sFloat
	{
		const Types::sFloat Max			= 3.402823466e+38F;
		const Types::sFloat Min			= -3.402823466e+38F;
	}

#ifdef _use_d3Math_
	namespace d3Float
	{
		const Types::d3Float Max			= sFloat::Max;
		const Types::d3Float Min			= sFloat::Min;
		const Types::d3Float Precision		= 1.0e-5f;
	}
#endif

#ifdef _use_d2Math_
	namespace d2Float
	{
		const Types::d2Float Max			= sFloat::Max;
		const Types::d2Float Min			= sFloat::Min;
		const Types::d2Float Precision		= 1.0e-5f;
	}
#endif

}

#endif // _S_SYSTEM_LIMIT_INC_
