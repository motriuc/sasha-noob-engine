/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_effect.h
//	Created                 : 23 1 2011   21:56
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

#ifndef _RD3_EFFECT_H_
#define _RD3_EFFECT_H_

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
 * Forward declarations
 */
class RenderState;
class Texture;

using namespace System::d3Math;

/**
 *
 */
class Effect : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	class Float
	{
	public:
		Float( d3Float v = 0.0f );
		void operator = ( d3Float v );
		
		void Apply( const Effect* pEffect , const sChar* name ) const;
	private:
		mutable sInt	_paramId;
		d3Float			_value;
	};
	
	/**
	 * Applies render stare to effect
	 */
	 virtual void Apply( RenderState& renderState ) const;
	
	/**
	 * returns fload param id, it is quie slow so it 
	 * must not be used to often 
	 */
	sInt GetFloatParam( const sString& name ) const;
	
	/**
	 * sets the float param
	 */
	void SetFloatParam( sInt idParam, d3Float value ) const;
	
protected:
	Effect( Render* owner, const sString& objectName );

	_PLATFORM void SetIndex( MatrixParameter::MatrixParameter p, sUInt index );
	_PLATFORM void SetIndex( VectorParameter::VectorParameter p, sUInt index );
	_PLATFORM void SetIndex( FloatParameter::FloatParameter p, sUInt index );
	_PLATFORM void SetIndex( BoolParameter::BoolParameter p, sUInt index );
	_PLATFORM void SetIndex( TextureParameter::TextureParameter p, sUInt index );

	_PLATFORM sBool IsUsed( MatrixParameter::MatrixParameter p ) const;
	_PLATFORM sBool IsUsed( VectorParameter::VectorParameter p ) const;
	_PLATFORM sBool IsUsed( FloatParameter::FloatParameter p ) const;
	_PLATFORM sBool IsUsed( BoolParameter::BoolParameter p ) const;
	_PLATFORM sBool IsUsed( TextureParameter::TextureParameter p ) const;

	_PLATFORM sUInt GetIndex( MatrixParameter::MatrixParameter p ) const;
	_PLATFORM sUInt GetIndex( VectorParameter::VectorParameter p ) const;
	_PLATFORM sUInt GetIndex( FloatParameter::FloatParameter p ) const;
	_PLATFORM sUInt GetIndex( BoolParameter::BoolParameter p ) const;
	_PLATFORM sUInt GetIndex( TextureParameter::TextureParameter p ) const;

	_PLATFORM virtual void Set( sUInt h, const d3Matrix& m ) const = 0;
	_PLATFORM virtual void Set( sUInt h, const d3Vector& v ) const = 0;
	_PLATFORM virtual void Set( sUInt h, const d3Float f ) const = 0;
	_PLATFORM virtual void Set( sUInt h, const sBool b ) const = 0;
	_PLATFORM virtual void Set( sUInt i, sUInt h, const Texture* t ) const = 0;
private:
	sUInt	_matrix_params[MatrixParameter::COUNT];
	sUInt	_vector_params[VectorParameter::COUNT];
	sUInt	_float_params[FloatParameter::COUNT];
	sUInt	_bool_params[BoolParameter::COUNT];
	sUInt	_texture_params[TextureParameter::COUNT];
	
	MatrixParameter::MatrixParameter	_used_matrix_params[MatrixParameter::COUNT];
	VectorParameter::VectorParameter	_used_vector_params[VectorParameter::COUNT];
	FloatParameter::FloatParameter		_used_float_params[FloatParameter::COUNT];
	BoolParameter::BoolParameter		_used_bool_params[BoolParameter::COUNT];
	TextureParameter::TextureParameter	_used_texture_params[TextureParameter::COUNT];

	sInt	_count_matrix_params;
	sInt	_count_vector_params;
	sInt	_count_float_params;
	sInt	_count_bool_params;
	sInt	_count_texture_params;
	
protected:
	template<typename _Type>
	class DynamicParameters
	{
	public:
		void Add( const sString& name, sUInt hParam );
		sInt GetParamId( const sString& name ) const;
		void SetValue( sInt idParam, const _Type& v );
		void Apply( const Effect* effect ) const;
	private:
		sVector<sString>	_paramNames;
		sVector<sUInt>		_paramHandles;
		sVector<_Type>		_values;
	};
protected:
	mutable DynamicParameters<d3Float>	_floatDynamicParams;
};

	
#include "rd3_effect.inl"

}


#endif // _RD3_EFFECT_H_
