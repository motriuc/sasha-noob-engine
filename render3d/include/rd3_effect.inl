/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_effect.inl
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

inline sBool Effect::IsUsed( MatrixParameter::MatrixParameter p ) const
{
	__S_ASSERT( p >= 0 && p < MatrixParameter::COUNT );
	return _matrix_params[p] != 0;
}

inline sBool Effect::IsUsed( VectorParameter::VectorParameter p ) const
{
	__S_ASSERT( p >= 0 && p < VectorParameter::COUNT );
	return _vector_params[p] != 0;
}

inline sBool Effect::IsUsed( FloatParameter::FloatParameter p ) const
{
	__S_ASSERT( p >= 0 && p < FloatParameter::COUNT );
	return _float_params[p] != 0;
}

inline sBool Effect::IsUsed( BoolParameter::BoolParameter p ) const
{
	__S_ASSERT( p >= 0 && p < BoolParameter::COUNT );
	return _bool_params[p] != 0;
}

inline sBool Effect::IsUsed( TextureParameter::TextureParameter p ) const
{
	__S_ASSERT( p >= 0 && p < TextureParameter::COUNT );
	return _texture_params[p] != 0;
}

/////////////////////////////////////////////////////////////////////////////////

inline sUInt Effect::GetIndex( MatrixParameter::MatrixParameter p ) const
{
	__S_ASSERT( p >= 0 && p < MatrixParameter::COUNT );
	return _matrix_params[p];
}

inline sUInt Effect::GetIndex( VectorParameter::VectorParameter p ) const
{
	__S_ASSERT( p >= 0 && p < VectorParameter::COUNT );
	return _vector_params[p];
}

inline sUInt Effect::GetIndex( FloatParameter::FloatParameter p ) const
{
	__S_ASSERT( p >= 0 && p < FloatParameter::COUNT );
	return _float_params[p];
}

inline sUInt Effect::GetIndex( BoolParameter::BoolParameter p ) const
{
	__S_ASSERT( p >= 0 && p < BoolParameter::COUNT );
	return _bool_params[p];
}

inline sUInt Effect::GetIndex( TextureParameter::TextureParameter p ) const
{
	__S_ASSERT( p >= 0 && p < TextureParameter::COUNT );
	return _texture_params[p];
}

///////////////////////////////////////////////////////////////////////////////
inline void Effect::SetIndex( MatrixParameter::MatrixParameter p, sUInt index )
{
	__S_ASSERT( p >= 0 && p < MatrixParameter::COUNT );
	__S_ASSERT( _matrix_params[p] == 0 );

	_matrix_params[p] = index;
	
	_used_matrix_params[_count_matrix_params] = p;
	_count_matrix_params++;
}

inline void Effect::SetIndex( VectorParameter::VectorParameter p, sUInt index )
{
	__S_ASSERT( p >= 0 && p < VectorParameter::COUNT );
	__S_ASSERT( _vector_params[p] == 0 );
	
	_vector_params[p] = index;

	_used_vector_params[_count_vector_params] = p;
	_count_vector_params++;
}

inline void Effect::SetIndex( FloatParameter::FloatParameter p, sUInt index )
{
	__S_ASSERT( p >= 0 && p < FloatParameter::COUNT );
	__S_ASSERT( _float_params[p] == 0 );

	_float_params[p] = index;

	_used_float_params[_count_float_params] = p;
	_count_float_params++;
}

inline void Effect::SetIndex( BoolParameter::BoolParameter p, sUInt index )
{
	__S_ASSERT( p >= 0 && p < BoolParameter::COUNT );
	__S_ASSERT( _bool_params[p] == 0 );

	_bool_params[p] = index;

	_used_bool_params[_count_bool_params] = p;
	_count_bool_params++;
}

inline void Effect::SetIndex( TextureParameter::TextureParameter p, sUInt index )
{
	__S_ASSERT( p >= 0 && p < TextureParameter::COUNT );
	__S_ASSERT( _texture_params[p] == 0 );

	_texture_params[p] = index;

	_used_texture_params[_count_texture_params] = p;
	_count_texture_params++;
}

inline sInt Effect::GetFloatParam( const sString& name ) const
{
	return _floatDynamicParams.GetParamId( name );
}

inline void Effect::SetFloatParam( sInt idParam, d3Float value ) const
{
	_floatDynamicParams.SetValue( idParam, value );
}

template<typename _Type>
inline void Effect::DynamicParameters<_Type>::Add( const sString& name, sUInt hParam )
{
	_paramNames.Add( name );
	_paramHandles.Add( hParam );
	_values.Add( _Type() );
}

template<typename _Type>
inline sInt Effect::DynamicParameters<_Type>::GetParamId( const sString& name ) const
{
	for( sInt i = 0; i < _paramNames.Size(); i++ )
	{
		if( _paramNames[i] == name )
			return i;
	}
			
	return -1;
}

template<typename _Type>
inline void Effect::DynamicParameters<_Type>::SetValue( sInt idParam, const _Type& v )
{
	_values[idParam] = v;
}

template<typename _Type>
inline void Effect::DynamicParameters<_Type>::Apply( const Effect* effect ) const
{
	__S_ASSERT( effect != NULL );
	
	for( sInt i = 0; i < _paramHandles.Size(); ++i )
	{
		effect->Set( _paramHandles[i], _values[i] );
	}
}

inline Effect::Float::Float( d3Float v ) :
	_paramId( -1 ),
	_value( v )
{
}

inline void Effect::Float::operator = ( d3Float v )
{
	_value = v;
}

inline void Effect::Float::Apply( const Effect* pEffect, const sChar* name ) const
{
	if( _paramId < 0 )
	{
		if( _paramId == -2 )
			return;
		_paramId = pEffect->GetFloatParam( name );
		
		if( _paramId < 0 )
		{
			_paramId = -2;
			System::Platform::DebugWarning( _S("Effect : ") + pEffect->GetObjectName() + _S(" parmeter '") + name + _S("' not found") ); 
			return;
		}
	}
	
	pEffect->SetFloatParam( _paramId, _value );
}

