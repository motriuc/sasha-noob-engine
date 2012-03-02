/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_material.h
//  Created                 : 31 1 2011   19:58
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

#ifndef _RD3_MATERIAL_H_
#define _RD3_MATERIAL_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"

namespace Rd3
{

/**
 * IMaterialFactory
 */
typedef System::T::IClassFactory2< Material, Render*, const sString& > IMaterialFactory;
	
/**
 * Material
 */
class Material : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
protected:
	/**
	 *
	 */
	Material( Render* owner, const sString& objectName );
public:	
	/**
	 *
	 */
	static void Register( const sString& name, IMaterialFactory* pFactory );
	static Material* Create( const sString& name, Render* owner, const sString& objectName );
	
	/**
	 *
	 */
	virtual void LoadFromXml( const System::Xml::BaseDomNode& node, const Def& def ) throws_error {}	
public:
	/**
	 * Applies material to render state
	 */
	virtual void Apply( RenderState& renderState ) const = 0;
};

}

/////////////////////////////////////////////////////////////////////
// Material factory register
/////////////////////////////////////////////////////////////////////

#define AUTO_REGISTER_MATERIAL_FACTORY( _name, _class ) \
	static class Factory_Material_Register_##_class :\
		public System::T::ClassFactory2<_class, Rd3::Material, Rd3::Render*, const sString& > \
	{ \
	public: \
		Factory_Material_Register_##_class( ) \
		{ \
			Rd3::Material::Register( _name, this ); \
		} \
	} register_material_##_class;

#endif // _RD3_MATERIAL_H_

