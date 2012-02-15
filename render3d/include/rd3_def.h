////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_def.h
//	Created            : 16.3.2006   21:53
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

#ifndef _RD3_DEF_H_
#define _RD3_DEF_H_


namespace Rd3
{

using namespace System::Types;
using namespace System::Cnt;

/**
 * Macro defines
 */
class Def
{
public:

	/**
	 * constructor
	 */
	Def();

	/**
	 * copy constructor
	 */
	Def( const Def& src );

	/**
	 * copy operator
	 */
	void operator = ( const Def& src );

	/**
	 * Define a macro
     */
	void Define( const sString& d );

	/**
	 * Define a macro
	 */
	void Define( const sString& d, const sString& v );

	/**
	 * Undef a macro
	 */
	void Undef( const sString& d );

	/**
	 * test if macro defined
	 */
	sBool IsDefined( const sString& d ) const;

	/**
	 *
	 */
	sBool IsOneDefined( const sStrings& d ) const;

	/**
	 * 
	 */
	sBool IsAllDefined( const sStrings& d ) const;

	/**
	 * return all defined names
	 */
	void GetAllDefined( sStrings& d ) const;

	/**
     * 
	 */
	const sString operator[] ( sString d ) const;
  
private:
	typedef sMap <sString, sString> Map;
	Map  _defines;
};

}

#endif // _RD3_DEF_H_