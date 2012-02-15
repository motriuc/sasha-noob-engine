/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_effect.cpp
//	Created                 : 23 1 2011   21:56
//	File path               : SLibF\render3d\cpp
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

#include "rd3afx.h"
#include "rd3_effect.h"
#include "rd3_rstate.h"

namespace Rd3
{

/************************************************************************/
/*                                                                      */
/************************************************************************/
Effect::Effect( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName, ResourceType::E_EFFECT ),
	_count_matrix_params( 0 ),
	_count_vector_params( 0 ),
	_count_float_params( 0 ),
	_count_bool_params( 0 ),
	_count_texture_params( 0 )
{
	for( sInt i = 0; i < MatrixParameter::COUNT; i++ )
		_matrix_params[i] = 0;

	for( sInt i = 0; i < VectorParameter::COUNT; i++ )
		_vector_params[i] = 0;

	for( sInt i = 0; i < FloatParameter::COUNT; i++ )
		_float_params[i] = 0;

	for( sInt i = 0; i < BoolParameter::COUNT; i++ )
		_bool_params[i] = 0;

	for( sInt i = 0; i < TextureParameter::COUNT; i++ )
		_texture_params[i] = 0;

}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void Effect :: Apply( RenderState& renderState ) const
{
	// Apply matrix params
	for( sInt i = 0; i < _count_matrix_params; i++ )
	{
		MatrixParameter::MatrixParameter p = _used_matrix_params[i];

		if( renderState._changed_effect || renderState._changed_matrix_params[p] )
			Set( _matrix_params[p], renderState._matrix_params[p] );
	}

	// Apply vector params
	for( sInt i = 0; i < _count_vector_params; i++ )
	{
		VectorParameter::VectorParameter p = _used_vector_params[i];

		if( renderState._changed_effect || renderState._changed_vector_params[p] )
			Set( _vector_params[p], renderState._vector_params[p] );
	}

	// Apply float params
	for( sInt i = 0; i < _count_float_params; i++ )
	{
		FloatParameter::FloatParameter p = _used_float_params[i];

		if( renderState._changed_effect || renderState._changed_float_params[p] )
			Set( _float_params[p], renderState._float_params[p] );
	}

	// Apply bool params
	for( sInt i = 0; i < _count_bool_params; i++ )
	{
		BoolParameter::BoolParameter p = _used_bool_params[i];

		if( renderState._changed_effect || renderState._changed_bool_params[p] )
			Set( _bool_params[p], renderState._bool_params[p] );
	}

	// Apply texture params
	for( sInt i = 0; i < _count_texture_params; i++ )
	{
		TextureParameter::TextureParameter p = _used_texture_params[i];

		if( renderState._changed_effect || renderState._changed_texture_params[p] )
			Set( i, _texture_params[p], renderState._texture_params[p] );
	}
	
	// Apply dynamic params
	_floatDynamicParams.Apply( this );
}



}

