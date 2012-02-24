/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_rstate.inl
//	Created                 : 23 01 2011   1:40
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

inline const d3Frustum& RenderState::GetFrustum() const
{
	return _frustum;
}

inline const d3Matrix* RenderState::SetTransformation( const d3Matrix* m )
{
	__S_ASSERT( _bIsRenderingObject == sFalse );
	__S_ASSERT( m != NULL );

	const d3Matrix* tmp = _transformation;
	_transformation = m;
	_changed_transformation = sTrue;

	return tmp;
}
	
inline const d3Matrix* RenderState::AddTransformation( d3Matrix* m )
{
	__S_ASSERT( m != NULL );

	(*m) *= *_transformation;
	
	return SetTransformation( m );
}

inline void RenderState::SetTexture( TextureParameter::TextureParameter id, const Texture* tx )
{
	__S_ASSERT( id >= 0 && id < TextureParameter::COUNT );

	if( _texture_params[id] != tx )
	{
		_texture_params[id] = tx;
		_changed_texture_params[id] = sTrue;
	}
}

inline void RenderState::SetEffect( const Effect* effect )
{
	if( _effect != effect )
	{
		_effect = effect;
		_changed_effect = true;
	}
}

inline const Effect* RenderState::GetEffect()
{
	return _effect;
}

inline void RenderState::SetAfterEffect( const AfterEffect* effect )
{
	_pAfterEffect = effect;
}

inline const AfterEffect* RenderState::GetAfterEffect()
{
	return _pAfterEffect;
}

inline void RenderState::SetCamera( const d3Camera& camera )
{
	__S_ASSERT( _bIsRenderingObject == sFalse );

	_camera = camera;
	_changed_camera = sTrue;
}

inline const CommonDataForRender& RenderState::GetCommonData() const
{
	__S_ASSERT( _engineData != NULL );
	return _engineData->GetCommonData();
}

inline Render* RenderState::GetOwner()
{
	__S_ASSERT( _pOwner != NULL );
	return _pOwner; 
}

inline void RenderState::SetParam_Color1( sRGBColor color )
{
	d3Vector vc;
	RGBColorToVector( color, vc );

	SetParam_Color1( vc );
}

inline void RenderState::SetParam_Color1( const d3Vector& color )
{	
	if( color != _vector_params[VectorParameter::E_COLOR1] )
	{
		_vector_params[VectorParameter::E_COLOR1] = color;
		_changed_vector_params[VectorParameter::E_COLOR1] = sTrue;
	}
}

inline void RenderState::SetParam_ColorDiffuse( const sRGBColor color )
{
	d3Vector vc;
	RGBColorToVector( color, vc );

	SetParam_ColorDiffuse( vc );
}

inline void RenderState::SetParam_ColorDiffuse( const d3Vector& color )
{
	if( color != _vector_params[VectorParameter::E_COLOR_DIFFUSE] )
	{
		_vector_params[VectorParameter::E_COLOR_DIFFUSE] = color;
		_changed_vector_params[VectorParameter::E_COLOR_DIFFUSE] = sTrue;
	}
}

inline void RenderState::SetParam_ColorSpecular( const sRGBColor color )
{
	d3Vector vc;
	RGBColorToVector( color, vc );

	SetParam_ColorSpecular( vc );
}

inline void RenderState::SetParam_ColorSpecular( const d3Vector& color )
{
	if( color != _vector_params[VectorParameter::E_COLOR_SPECULAR] )
	{
		_vector_params[VectorParameter::E_COLOR_SPECULAR] = color;
		_changed_vector_params[VectorParameter::E_COLOR_SPECULAR] = sTrue;
	}
}

inline void RenderState::UpdateTime()
{
	__S_ASSERT( _engineData != NULL );

	_float_params[FloatParameter::E_TIME] = _engineData->GetTime();
	_float_params[FloatParameter::E_DELTA_TIME] = _engineData->GetDeltaTime();

	_changed_float_params[FloatParameter::E_TIME] = sTrue;
	_changed_float_params[FloatParameter::E_DELTA_TIME] = sTrue;
}

inline const d3Matrix& RenderState::GetTransformation() const
{
	return *_transformation;
}

inline sInt RenderState::MaxLightCount() const
{
	return _D3_MAX_RENDER_LIGHTS;
}

inline void RenderState::SetRenderTarget( Texture* pTexture )
{
	_pRenderTarget = pTexture;
}

inline Texture* RenderState::GetRenderTarget()
{
	return _pRenderTarget;
}


