/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_material_solid.h
//  Created                 : 24 2 2012   19:58
//  File path               : SLibF\render3d\include
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

#ifndef _RD3_MATERIAL_SOLID_H_
#define _RD3_MATERIAL_SOLID_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_material.h"
#include "rd3_effect.h"

namespace Rd3
{
	
/**
 * SolidMaterial
 */
class SolidMaterial : public Material
{
private:
	typedef Material _BaseClass;
public:
	/**
	 *
	 */
	SolidMaterial( Render* owner, const sString& objectName );
	
	/**
	 *
	 */
	virtual void LoadFromXml( const System::Xml::BaseDomNode& node, const Def& def ) throws_error;
	
public:
	/**
	 * Applies material to render state
	 */
	virtual void Apply( RenderState& renderState ) const;
private:
	use_resource<Effect>	_effect;
	d3Vector				_difColor;
	d3Vector				_specularColor;
	d3Vector				_ambientColor;
	
	Rd3::Effect::Float		_co_diffuse;
	Rd3::Effect::Float		_co_phong_exp;
	Rd3::Effect::Float		_co_phong;
};


}

#endif // _RD3_MATERIAL_SOLID_H_

