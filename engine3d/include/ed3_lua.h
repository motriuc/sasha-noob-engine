/////////////////////////////////////////////////////////////////////
//  File Name               : ed3_lua.h
//  Created                 : 18 2 2012   20:02
//  File path               : SLibF\engine3d\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//	Modification History:
//      
/////////////////////////////////////////////////////////////////////

#ifndef _ED3_LUA_INC_
#define _ED3_LUA_INC_

namespace Ed3
{

/**
 *	LuaAccess
 */
class LuaFunctionState : private class_nocopy 
{
public:
	/**
	 *	User ptr set in LuaObjec constructor
	 */
	void* Me() const;

	/**
	 *	Get float value
	 */
	sFloat GetValue( sInt i, d3Float def ) const;
	
	/**
	 * Get int value
	 */
	sInt GetValue( sInt i, sInt def ) const;
	
	/**
	 *
	 */
	sString GetValue( sInt i, const sString& def ) const;

	/**
	 *
	 */
	void* GetInstance() const; 

	/**
	 *	Return float value
	 */
	void Return( d3Float def ) const;
	
	void Return( sInt value ) const;

private:
	LuaFunctionState();
	~LuaFunctionState();
};

/**
 * Lua function
 */
typedef sInt (*LuaFunction) ( const LuaFunctionState *L );

typedef struct
{
	const SBCHAR*	name;
	LuaFunction		f;
} LuaFunctions;

/**
 *	LuaObject
 */
class LuaObject : private class_nocopy 
{
public:
	LuaObject( void* pUserPtr );
	
	~LuaObject();
	

	/**
	 *
	 */
	void LoadFromFile( const sString& path, const Streams::StreamArchive& archive ) throws_error;
	
	/**
	 *	
	 */
	void Register( const SBCHAR* funName, LuaFunction fn );
	void Register( const SBCHAR* table, const SBCHAR* funName, LuaFunction fn );
	
	void RegisterMathLib();
	
	/**
	 *
	 */
	void Exec( const SBCHAR* funName ) throws_error;
	
	/**
	 *
	 */
	void Exec( const SBCHAR* funName, d3Float p ) throws_error; 
	
	/**
	 *
	 */
	void Exec( const SBCHAR* funName, void* pObject, LuaFunctions* pObjectFun ) throws_error;

	/**
	 *
	 */
	sBool HasFunction( const SBCHAR* funName ) const;
private:
	void*	_pLuaHandle;
	void*	_pUserPtr;
	
private:
	/**
	 *
	 */
	void LoadFromString( const char* code ) throws_error;	
};

}

#endif // _ED3_LUA_INC_