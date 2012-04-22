/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_macro.h
//  Created                 : 23 6 2007   22:33
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      SLib wide used macros
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////
#ifndef _SYSTEM_MACRO_INC_
#define _SYSTEM_MACRO_INC_

/**
 *	SLIB Name
 */
#define _SLIB_LIB_NAME						        _S("SLIB")

/**
 *	SLIB version
 */
#define _SLIB_LIB_VERSION					        3.1

/**
 *	__S_FILE__ file name
 */
#ifdef _SLIB_WCHAR
	#define ___BUG_COMPILER(X)				_S(X)
	#define __S_FILE__						___BUG_COMPILER( __FILE__ )
#else
	#define __S_FILE__						__FILE__
#endif

/**
 * used internally by the library to indicate platfrom dependend functionality 
 */
#define _PLATFORM

/**
 *	avoid to used the functionality for this marked with this macro
 */
#define _NOT_SAFE

/**
 *	Runtime string
 */
#define _SLIB_RUNTIME_STRING( X )  _S( X )

/**
 *	Class type
 */
#define TYPE( __CLASS )		__CLASS::ClassType()

/**
 *	debug info
 */
#ifdef _DEBUG 
	#define _DEBUG_INFO_	__S_FILE__, __LINE__
	#define _DEBUG_INFO		__S_FILE__, __LINE__,
#else
	#define _DEBUG_INFO_
	#define _DEBUG_INFO
#endif

/**
 * exeption handling macros
 */
#define error_throw_arg( _X )			throw new _X( _DEBUG_INFO NULL,
#define error_throw( _X )				throw new _X( _DEBUG_INFO NULL )

#define error_throw_chain_arg( _X )		throw new _X( _DEBUG_INFO error,
#define error_throw_chain( _X )			throw new _X( _DEBUG_INFO error )

#define error_catch( _X )				catch ( _X* error )
#define error_free						delete error

#define throws_error
#define error_catch_all					catch( System::Errors::Error* error ) { delete error } 

/**
 *	Runtime macros
 */
#define _SLIB_RUNTIME( __NAMESPACE, __CLASS, __BASE_CLASS ) \
	_SLIB_RUNTIME_CLASS_IMP( __NAMESPACE, __CLASS, __BASE_CLASS::ClassType()	) \
	_SLIB_BASE_CLASS( __BASE_CLASS )


#define _SLIB_RUNTIME_BASE( __NAMESPACE, __CLASS ) \
	_SLIB_RUNTIME_CLASS_IMP( __NAMESPACE, __CLASS, NULL )


/**
 *	Definition of the base class type
 */
#define _SLIB_BASE_CLASS( c ) private: typedef c _BaseClass;

/**
 * Definition of the class runtime
 */
#define _SLIB_RUNTIME_CLASS_IMP( __NAMESPACE, __CLASS, __BASE ) \
	private: \
	class Type : public System::Obj::IType \
	{ \
	private: \
		Type() {} \
		Type( const Type& ); \
		void operator = ( const Type& ); \
	public: \
		static Type* Instance() \
		{ \
			static Type t; \
			return &t; \
		} \
	public: \
		virtual const System::Types::sChar* GetClassName() const \
		{ \
			return _SLIB_RUNTIME_STRING( #__CLASS ); \
		} \
		virtual const System::Types::sChar* GetNamespace() const \
		{ \
			return _SLIB_RUNTIME_STRING( #__NAMESPACE ); \
		} \
		virtual System::Obj::IType* GetParent() \
		{ \
			return __BASE; \
		} \
		virtual const System::Obj::IType* GetParent() const \
		{ \
			return __BASE; \
		} \
	}; \
	public:\
		inline static System::Obj::IType* ClassType() \
		{ \
			return Type::Instance(); \
		} \
		virtual System::Obj::IType* ObjectType() \
		{ \
			return Type::Instance(); \
		} \
		virtual const System::Obj::IType* ObjectType() const \
		{ \
			return Type::Instance(); \
		}



#endif // _SYSTEM_MACRO_INC_
