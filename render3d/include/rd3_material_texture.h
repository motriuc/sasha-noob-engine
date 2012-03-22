/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_material_texture.h
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

#ifndef _RD3_MATERIAL_TEXTURE_H_
#define _RD3_MATERIAL_TEXTURE_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_material.h"
#include "rd3_effect.h"
#include "rd3_texture.h"

namespace Rd3
{
	
/**
 * TextureMaterial
 */
class TextureMaterial : public Material
{
private:
	typedef Material _BaseClass;
public:
	/**
	 *
	 */
	TextureMaterial( Render* owner, const sString& objectName );
	
	/**
	 *
	 */
	virtual void LoadFromXml( const System::Xml::BaseDomNode& node, const Def& def ) throws_error;
	
	/**
	 *
	 */
	void SetTexture( Texture* pTexture )	{ _texture = pTexture; }
	
	/**
	 *
	 */
	void SetTexture( const sString& name );

	/**
	 *
	 */
	void SetDiffuze( d3Float v )			{ _co_diffuse = v; }
	void SetSpecular( d3Float v )			{ _co_phong = v; }
	void SetSpecularHardness( d3Float v )	{ _co_phong_exp = v; }
	void SetAmbient( d3Float v )			{ _co_ambient = v; }

	void SetNumberOfLights( sInt num );
	virtual void SetQuality( Quality::Quality quality );
	
public:
	/**
	 * Applies material to render state
	 */
	virtual void Apply( RenderState& renderState ) const;
private:
	sInt					_numberOfLights;			
	use_resource<Texture>	_texture;
	use_resource<Effect>	_effect;
	
	Rd3::Effect::Float		_co_diffuse;
	Rd3::Effect::Float		_co_phong_exp;
	Rd3::Effect::Float		_co_phong;
	Rd3::Effect::Float		_co_ambient;
	
	void UpdateEffect();
};


}

#endif // _RD3_MATERIAL_TEXTURE_H_

