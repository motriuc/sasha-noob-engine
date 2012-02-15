/////////////////////////////////////////////////////////////////////
//  File Name               : buble.h
//	Created                 : 30 1 2012   0:05
//	File path               : games/buble/include
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

#ifndef _BUBLE_INC_
#define _BUBLE_INC_

#include "ed3_object.h"
#include "rd3_resobj.h"


/**
 *
 */
class BubleMaterial : public Rd3::Material
{
public:
private:	
	Rd3::use_resource<Rd3::Texture>			_tileTexture;
};

/**
 * Buble
 */
class Buble : public Ed3::d3Object
{
private:
	typedef Ed3::d3Object _BaseClass;
public:
	/**
	 *
	 */
	Buble();
protected:
	/**
	 *
	 */
	virtual void LoadFromXML( const Xml::BaseDomNode& element, Ed3::LoadDataParams& loadParams ) throws_error;
	
	/**
	 *
	 */
	virtual void Initialize( Rd3::Render& render ) throws_error;
	
	/**
	 *
	 */
	virtual void Render( const Ed3::d3RenderData& renderData );
	
private:
	Rd3::use_resource<BubleMaterial>		_material;
	Rd3::use_resource<Rd3::Mesh>			_mesh;
	Rd3::Effect::Float						_radius;
};


#endif // _BUBLE_INC_