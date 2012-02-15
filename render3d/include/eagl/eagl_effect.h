/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_effect.h
//	Created                 : 11 1 2012   22:43
//	File path               : SLibF\render3d\include\eagl
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

#ifndef _EAGL_EFFECT_H_
#define _EAGL_EFFECT_H_

#ifndef _EAGL_CONF_H_
	#error eagl_conf.h must be included
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
 * EAGLEffect
 */
class EAGLEffect : public Rd3::Effect
{
private:
	typedef Rd3::Effect _BaseClass;
public:
	/**
	 * create effect from string code
	 */
	EAGLEffect( Rd3::Render* owner, const sString& objectName ) throws_error;

	/**
	 *
	 */
	void LoadFromXml( const Xml::BaseDomNode& node, const Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error;
	
	/**
	 *
	 */
	void LoadFromString( const sString& effect, const Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error;

	/**
	 *
	 */
	void LoadFromFile( const sString& filePath, const Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error;

	/**
	 *
	 */
	virtual void Set( sUInt i, const d3Matrix& m ) const;
	virtual void Set( sUInt i, const d3Vector& v ) const;
	virtual void Set( sUInt i, const d3Float f ) const;
	virtual void Set( sUInt i, const sBool b ) const;
	virtual void Set( sUInt i, sUInt h, const Rd3::Texture* t ) const;
	
	/**
	 *
	 */
	virtual void Apply( Rd3::RenderState& renderState ) const;
	
	/**
	 *
	 */
	_PLATFORM GLuint GetHandle() const { return _program; }
	
	/**
	 *
	 */
	_PLATFORM const sInt* AttributeIds() const { return _attributeIds; }
protected:	
	/**
	 *
	 */
	virtual ~EAGLEffect();	
private:
	GLuint	_program;
	sInt	_attributeIds[Rd3::AttributeParameter::COUNT];
	
	// blending
	sBool	_blendingEnabled;
	GLenum	_blendingSourceFactor;
	GLenum	_blendingDestinationFactor;
	
private:	
	void InitParamLinks();
	void BindAttributes();
	
	void LoadParams( const Xml::BaseDomNode& node, const Rd3::Def& def );
	void LoadParams_Blending( const Xml::BaseDomNode& node, const Rd3::Def& def );
	
};

#endif // _EAGL_EFFECT_H_