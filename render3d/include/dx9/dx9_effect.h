/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_effect.h
//	Created                 : 23 1 2011   22:43
//	File path               : SLibF\render3d\include\dx9
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
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

#ifndef _DX9_EFFECT_H_
#define _DX9_EFFECT_H_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_effect.h"

/**
 * forward declarations
 */
namespace Rd3
{
	class Render;
	class Def;
	class Texture;
}

/**
 *
 */
class Dx9Effect : public Rd3::Effect
{
private:
	typedef Rd3::Effect _BaseClass;
public:
	/**
	 * create effect from string code
	 */
	Dx9Effect(
		Rd3::Render* owner,  
		const sString& objectName
	) throws_error;

	/**
	 *
	 */
	void LoadFromString( const sString& effect, const Rd3::Def& def ) throws_error;

	/**
	 *
	 */
	void LoadFromFile( const sString& filePath, const Rd3::Def& def ) throws_error;

	/**
	 *
	 */
	virtual ~Dx9Effect();

	/**
	 *
	 */
	virtual void Set( sUInt i, const d3Matrix& m );
	virtual void Set( sUInt i, const d3Vector& v );
	virtual void Set( sUInt i, const d3Float f );
	virtual void Set( sUInt i, const sBool b );
	virtual void Set( sUInt i, const Rd3::Texture* t );

	LPD3DXEFFECT GetHandle() const		{ return _pEffect; }
private:
	void InitParamsLinks() throws_error;
private:
	LPD3DXEFFECT _pEffect;
};

#endif // _DX9_EFFECT_H_