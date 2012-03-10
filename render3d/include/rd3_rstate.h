/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_rstate.h
//  Created                 : 23 01 2011   1:40
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

#include "rd3_edata.h"
#include "rd3_font.h"
#include "rd3_render.h"

namespace Rd3
{

using namespace System::d3Math;
using namespace System::d2Math;

/**
 * RenderState
 */
class RenderState
{
protected:
	RenderState( Render* owner );

public:
	virtual ~RenderState() {}

	/**
	 * Set object transformation
	 */
	const d3Matrix* SetTransformation( const d3Matrix* m );
	
	/**
	 *
	 */
	const d3Matrix* AddTransformation( d3Matrix* m );
	
	/**
	 *
	 */
	const d3Matrix& GetTransformation() const;

	/**
	 *
	 */
	void SetEffect( const Effect* effect );

	/**
	 *
	 */
	void SetEffect( const sString& effectName );

	/**
	 *
	 */
	void SetTexture( TextureParameter::TextureParameter id, const Texture* tx );

	/**
	 *
	 */
	void SetTexture( TextureParameter::TextureParameter id, const sString& textureName );
	
	/**
	 *
	 */
	void SetParam_Color1( const d3Vector& color );
	void SetParam_Color1( sRGBColor color );
	
	/**
	 *
	 */
	void SetParam_ColorDiffuse( const d3Vector& color );
	void SetParam_ColorDiffuse( const sRGBColor color );

	/**
	 *
	 */
	void SetParam_ColorSpecular( const d3Vector& color );
	void SetParam_ColorSpecular( const sRGBColor color );
	
	/**
	 *
	 */
	void SetParam_ColorAmbient( const d3Vector& color );
	void SetParam_ColorAmbient( const sRGBColor color );
	
	/**
	 *
	 */
	void SetLight( sInt v, const LightPoint& light );
	
	/**
	 *
	 */
	void SetLight( sInt v, const Light& light );
	
	/**
	 *
	 */
	sInt MaxLightCount() const;
	
	/**
	 *
	 */
	const EngineDataForRender& GetData() const;

	/**
	 * Function called before staring rendering an object
	 */
	virtual void BeginRenderObject();

	/**
	 * Function after rendering the object
	 */
	virtual void EndRenderObject();

	/**
	 *
	 */
	virtual void RenderPrimitive( const VertexBuffer* vb, PrimitiveType::PrimitiveType type ) = 0;
	virtual void RenderPrimitive( const VertexBuffer* vb, const IndexBuffer* ib, PrimitiveType::PrimitiveType type ) = 0;
	virtual void RenderPrimitive( const DynamicVertexBuffer* vb, PrimitiveType::PrimitiveType type ) = 0;

	void RenderMesh( const Mesh* pMesh );
		
	/**
	 *
	 */
	const d3Frustum& GetFrustum() const;
	
	/**
	 *
	 */
	d2Vector GetRenderTarger_SizeInPixels() const				{ return _renderTargetSizeInPixels; }

protected:
	Render* GetOwner();
	const Effect* GetEffect();
	const AfterEffect* GetAfterEffect();
	
	void SetAfterEffect( const AfterEffect* effect );

	void SetCamera( const d3Camera& camera );
	void SetRenderTarget( Texture* pTexture );
	Texture* GetRenderTarget();

	const EngineDataForRender*	_engineData;


	// Update utils
	void UpdateCamera();
	void UpdateTime();

	void UpdateTransformation();
	void Update2dTransformation();
private:
	RenderState( const RenderState& );
	void operator = ( const RenderState& );
private:
	Render*		_pOwner;

	// view
	d3Camera		_camera;
	const d3Matrix*	_transformation;

	// data
	const Effect*			_effect;
	const AfterEffect*		_pAfterEffect;
	Texture*				_pRenderTarget;
	d2Vector				_renderTargetSizeInPixels;


	// params
	d3Matrix		_matrix_params[MatrixParameter::COUNT];
	d3Vector		_vector_params[VectorParameter::COUNT];
	d3Float			_float_params[FloatParameter::COUNT];
	sBool			_bool_params[BoolParameter::COUNT];
	const Texture*	_texture_params[TextureParameter::COUNT];
	
	// change track

	// view
	sBool		_changed_camera;
	sBool		_changed_transformation;

	// data
	sBool		_changed_vertexBuffer;
	sBool		_changed_indexBuffer;
	sBool		_changed_effect;

	// params
	sBool		_changed_matrix_params[MatrixParameter::COUNT];
	sBool		_changed_vector_params[VectorParameter::COUNT];
	sBool		_changed_float_params[FloatParameter::COUNT];
	sBool		_changed_bool_params[BoolParameter::COUNT];
	sBool		_changed_texture_params[TextureParameter::COUNT];
	
	// tmp data
	d3Frustum	_frustum;
	d3Matrix	_defaultTransform;

#ifdef _DEBUG
	sBool		_bIsRenderingObject;	// true when rendering step is executed
#endif

	friend class Effect;
};


/**
 * WorldRenderState
 */
class WorldRenderState : public RenderState
{
private:
	typedef RenderState _BaseClass;
public:
	WorldRenderState( Render* owner );

	using RenderState::SetCamera;
	using RenderState::SetRenderTarget;
	using RenderState::SetAfterEffect;

	/**
	 * EngineDataForRender must exist during BeginWorldRender and EndWorldRender calls
	 */
	virtual void BeginWorldRender( const EngineDataForRender& edata );

	/**
	 *
	 */
	virtual void EndWorldRender();

	/**
	 *
	 */
	virtual void Clear( System::Types::sRGBColor color ) = 0;
	
	/**
	 *
	 */
	~WorldRenderState();
protected:
	/**
	 *
	 */
	void PostRender();
	
private:
	
#ifdef _D3_DEBUG_RENDER_COUNTERS
	use_resource<Font>	_renderFont;
	RenderString*		_debugTextRender;
	void debug_RenderStats();
#endif
	
};

#include "rd3_rstate.inl"

}