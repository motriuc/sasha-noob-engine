/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_material_flatcolor.h
//	Created                 : 31 1 2011   19:58
//	File path               : SLibF\render3d\include
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

#ifndef _RD3_MATERIAL_FLATCOLOR_H_
#define _RD3_MATERIAL_FLATCOLOR_H_

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
 * FlatColorMaterial
 */
class FlatColorMaterial : public Material
{
private:
	typedef Material _BaseClass;
public:
	/**
	 *
	 */
	FlatColorMaterial( Render* owner, const sString& objectName );
	
	/**
	 *
	 */
	void SetColor( sRGBColor color )		{ _color = color; }
	
	/**
	 *
	 */
	sRGBColor GetColor() const				{ return _color; }
	
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
	sRGBColor				_color;
	use_resource<Effect>	_effect;
	
	Rd3::Effect::Float		_co_diffuse;
	Rd3::Effect::Float		_co_phong_exp;
	Rd3::Effect::Float		_co_phong;
	Rd3::Effect::Float		_co_ambient;
	
};


}

#endif // _RD3_MATERIAL_FLATCOLOR_H_

