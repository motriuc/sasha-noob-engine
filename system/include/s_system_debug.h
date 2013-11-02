/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_debug.h
//  Created                 : 23 6 2007   23:18
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
#ifndef _SYSTEM_DEBUG_INC_
#define _SYSTEM_DEBUG_INC_


#ifdef _DEBUG

	///////////////////////////////////////////
	// verify execution
	#define __S_VERIFY( X )		__S_ASSERT( X )


	// WIN32 version
	#ifdef _SPL_WIN32

		_PLATFORM extern bool __slib_AssertMessage( const char* message, const char* file, int line );

		///////////////////////////////////////////
		// assert execution
		#define __S_ASSERT( X ) \
			do \
			{ \
				if( !( X ) ) \
				{ \
					\
					if( __slib_AssertMessage( #X ,  __FILE__ , __LINE__ ) ) \
						_ASSERT_BREAK(); \
				} \
			} while( false )

		#if defined( _X86_ ) 
			#define _ASSERT_BREAK()		_asm { int 3 }
		#elif defined( _M_X64 )
			#define _ASSERT_BREAK()		__debugbreak()
		#else
			#error not implemented _ASSERT_BREAK
		#endif

		#include<MMSYSTEM.H>
		#define __S_DEBUG_PRINT( X )  OutputDebugStringA( X )
	
	#endif // _SPL_WIN32

	// MAC version
	#ifdef _SPL_MAC
		#define __S_ASSERT( X ) assert( X )
	#endif // _SPL_MAC 

#else // _DEBUG
	#define __S_VERIFY( X )					X
	#define __S_ASSERT( X )
	#define __S_DEBUG_PRINT( X ) 
#endif // _DEBUG

#endif // _SYSTEM_DEBUG_INC_

