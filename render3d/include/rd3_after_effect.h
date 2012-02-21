/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_after_effect.h
//  Created                 : 20 2 2012 
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

#ifndef _RD3_AFTER_EFEECT_INC_
#define _RD3_AFTER_EFEECT_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"

namespace  Rd3
{

using namespace System;
	
class AfterEffectElement;
	
/**
 * IAfterEffectElementFactory
 */
typedef System::T::IClassFactory1<AfterEffectElement, Render&> IAfterEffectElementFactory;

/**
 * AfterEffect
 */
class AfterEffectElement
{
public:	
	/**
	 *
	 */
	virtual void Apply( RenderState& render ) const = 0;
	
	/**
	 *
	 */
	virtual void LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error = 0;
	
	/**
	 *
	 */
	virtual sBool SetParam( const sString& name, d3Float value ) { return sFalse; } 
};

/**
 * AfterEffect
 */
class AfterEffect : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	/**
	 *
	 */
	AfterEffect( Render* owner, const sString& objectName );
	
	/**
	 *
	 */
	void Add( AfterEffectElement* element ) { _elements.Add( element ); }

	/**
	 *
	 */
	sInt ElementCount() const { return _elements.Size(); }
		
	/**
	 *
	 */
	const AfterEffectElement& GetElement( sInt i ) const { return *_elements[i]; }
	AfterEffectElement& GetElement( sInt i ) { return *_elements[i]; }
	
	/**
	 *
	 */
	void LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error;
	void LoadFromFile( const sString& path, const Def& def, const Streams::StreamArchive& archive ) throws_error;
public:
	/**
	 *
	 */
	static void Register( const sString& name, IAfterEffectElementFactory* pFactory );
	
	/**
	 *
	 */
	static AfterEffectElement* Create( const sString& name, Render& render );
private:
	sVector<AfterEffectElement*>	_elements;
};
	
}

#define AUTO_REGISTER_AFTER_EFFECT_FACTORY( _name, _class ) \
class Factory_Register_after_effect_##_class \
{ \
public: \
	Factory_Register_after_effect_##_class( ) \
	{ \
		static System::T::ClassFactory1<_class, Rd3::AfterEffectElement, Rd3::Render&> obj; \
		Rd3::AfterEffect::Register( _name, &obj ); \
	} \
}; \
Factory_Register_after_effect_##_class register_after_effect_##_class;

#endif // _RD3_AFTER_EFEECT_INC_
