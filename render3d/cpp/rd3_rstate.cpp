/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_rstate.cpp
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
#include "rd3afx.h"
#include "rd3_rstate.h"
#include "rd3_render.h"
#include "rd3_light.h"
#include "rd3_mesh.h"
#include "rd3_material.h"
#include "rd3_render_str.h"
#include "rd3_texture.h"

COUNTER_USE( rd3_render_vertex_count )
COUNTER_USE( rd3_render_primitive_count )
COUNTER_USE( rd3_render_time_frame )
COUNTER_USE( rd3_render_time_draw )
COUNTER_USE( rd3_render_time_lua )
COUNTER_USE( rd3_render_time_physics )
COUNTER_USE( rd3_render_object_total )
COUNTER_USE( rd3_render_object_visible )
COUNTER_USE( rd3_render_time_rstate )

namespace Rd3
{

//---------------------------------------------------------------------------
RenderState::RenderState( Render* owner ) :
	_pOwner( owner ),

	_camera(),
	_transformation( &_defaultTransform ),

	_effect( NULL ),
	_pAfterEffect( NULL ),
	_pRenderTarget( NULL ),
	_defaultTransform( 1.0f ),

	_changed_camera( sTrue ),
	_changed_transformation( sTrue ),

	_changed_effect( sTrue ),
	
	_enabledState( 0 ),
	_changedEnabledState( 0 ),

#ifdef _DEBUG
	_bIsRenderingObject( sFalse ),
#endif
	_engineData( NULL )
{
	for( sInt i = 0; i < MatrixParameter::COUNT; i++ )
		_matrix_params[i] = _defaultTransform;

	for( sInt i = 0; i < VectorParameter::COUNT; i++ )
		_vector_params[i] = d3Vector( 0.0f );

	for( sInt i = 0; i < FloatParameter::COUNT; i++ )
		_float_params[i] = 0.0f;

	for( sInt i = 0; i < BoolParameter::COUNT; i++ )
		_bool_params[i] = sFalse;

	for( sInt i = 0; i < TextureParameter::COUNT; i++ )
		_texture_params[i] = NULL;

	
	/////////////////////////////////////////////////////
	for( sInt i = 0; i < MatrixParameter::COUNT; i++ )
		_changed_matrix_params[i] = sFalse;

	for( sInt i = 0; i < VectorParameter::COUNT; i++ )
		_changed_vector_params[i] = sFalse;

	for( sInt i = 0; i < FloatParameter::COUNT; i++ )
		_changed_float_params[i] = sFalse;

	for( sInt i = 0; i < BoolParameter::COUNT; i++ )
		_changed_bool_params[i] = sFalse;

	for( sInt i = 0; i < TextureParameter::COUNT; i++ )
		_changed_texture_params[i] = sFalse;

	// Set the 2d Transformation
	Update2dTransformation();
}
//---------------------------------------------------------------------------
void RenderState::Update2dTransformation()
{
	d3Camera camera;
	camera.SetCamera2D();

	d3Matrix mv;
	d3Matrix mp;

	camera.GetView( mv );
	camera.GetProjection( mp );

	d3Matrix::Mul( _matrix_params[MatrixParameter::E_D2_VIEW], mv, mp );

	_changed_matrix_params[MatrixParameter::E_D2_VIEW] = sTrue;
}

//---------------------------------------------------------------------------
void RenderState::UpdateCamera()
{
	COUNTER_TIME_START( rd3_render_time_rstate );
	
	if( _changed_camera )
	{
		_camera.GetView( _matrix_params[MatrixParameter::E_VIEW] );
		_changed_matrix_params[MatrixParameter::E_VIEW] = sTrue;
			
		_camera.GetProjection( _matrix_params[MatrixParameter::E_PROJ] );
		_changed_matrix_params[MatrixParameter::E_PROJ] = sTrue;
			
		d3Matrix::Mul(
			_matrix_params[MatrixParameter::E_VIEW_PROJ],
			_matrix_params[MatrixParameter::E_VIEW],
			_matrix_params[MatrixParameter::E_PROJ]
		);
		
		_changed_matrix_params[MatrixParameter::E_VIEW_PROJ] = sTrue; 
			
		_vector_params[VectorParameter::E_CAMERA_POS] = _camera.GetPosition();
		_changed_vector_params[VectorParameter::E_CAMERA_POS] = sTrue;
			
		_frustum.ClearPlanes();
		_camera.GetFrustum( _frustum );
		
		_changed_camera = sFalse;
	}
	
	COUNTER_TIME_STOP( rd3_render_time_rstate );
}

//---------------------------------------------------------------------------
void RenderState::SetEffect( const sString& effectName )
{
	SetEffect( _pOwner->GetEffect( effectName ) );
}

//---------------------------------------------------------------------------
void RenderState::SetTexture( TextureParameter::TextureParameter id, const sString& textureName )
{
	SetTexture( id, _pOwner->GetTexture( textureName ) );
}

//---------------------------------------------------------------------------
void RenderState::SetLight( sInt i, const LightPoint& light )
{
	__S_ASSERT( i >= 0 );
	__S_ASSERT( i < MaxLightCount() );
			   
	COUNTER_TIME_START( rd3_render_time_rstate );

	_vector_params[VectorParameter::E_LIGHT1_POS + i ] = light.GetPosition();
	_changed_vector_params[VectorParameter::E_LIGHT1_POS + i ] = sTrue;

	RGBColorToVector( light.GetDiffuzeColor(), _vector_params[VectorParameter::E_LIGHT1_DIFFUSE + i ] );
	RGBColorToVector( light.GetAmbientColor(), _vector_params[VectorParameter::E_LIGHT1_AMBIENT + i ] );
	RGBColorToVector( light.GetSpecularColor(), _vector_params[VectorParameter::E_LIGHT1_SPECULAR + i ] );

	_changed_vector_params[VectorParameter::E_LIGHT1_DIFFUSE + i] = sTrue;
	_changed_vector_params[VectorParameter::E_LIGHT1_AMBIENT + i] = sTrue;
	_changed_vector_params[VectorParameter::E_LIGHT1_SPECULAR + i] = sTrue;

	_float_params[FloatParameter::E_LIGHT1_ATENUATION + i] = light.GetAttenuation();
	_changed_float_params[FloatParameter::E_LIGHT1_ATENUATION +i] = sTrue;

	_bool_params[BoolParameter::E_LIGHT1_ON + i] = sTrue;
	_changed_bool_params[BoolParameter::E_LIGHT1_ON +i] = sTrue;
	
	COUNTER_TIME_STOP( rd3_render_time_rstate );	
}

//---------------------------------------------------------------------------
void RenderState::SetLight( sInt i, const Light& light )
{
	switch( light.GetType() )
	{
		case LightType::E_POINT:
			SetLight( i, light.lightPoint() );
			break;
			
		default:
			__S_ASSERT( sFalse );
			break;
	}
}
	
//---------------------------------------------------------------------------
void RenderState::BeginRenderObject()
{
	UpdateTransformation();

#ifdef _D3_DEBUG_RENDER
	const Rd3::CommonDataForRender& data = GetData().GetCommonData();

	if( !data.debug_RenderCulling() )
		SetState( RenderState::Culling, sFalse );

#endif

#ifdef _DEBUG
	_bIsRenderingObject = sTrue;
#endif
}

//---------------------------------------------------------------------------
void RenderState::UpdateTransformation()
{
	COUNTER_TIME_START( rd3_render_time_rstate );
	
	if( _changed_transformation )
	{
		_matrix_params[MatrixParameter::E_WORLD] = *_transformation;
		_changed_matrix_params[MatrixParameter::E_WORLD] = sTrue;
	}
	
	if( _changed_matrix_params[MatrixParameter::E_WORLD] )
	{
		_matrix_params[MatrixParameter::E_WORLD].GetNormalMatrix(
			_matrix_params[MatrixParameter::E_WORLD_NORMAL]
		);
		
		_changed_matrix_params[MatrixParameter::E_WORLD_NORMAL] = sTrue;
	}
		
	if( _changed_matrix_params[MatrixParameter::E_WORLD] || _changed_matrix_params[MatrixParameter::E_VIEW] )
	{
		d3Matrix::Mul(
			_matrix_params[MatrixParameter::E_WORLD_VIEW],
			_matrix_params[MatrixParameter::E_WORLD],
			_matrix_params[MatrixParameter::E_VIEW]
		);
			
		_changed_matrix_params[MatrixParameter::E_WORLD_VIEW] = sTrue;
	}
		
	if( _changed_matrix_params[MatrixParameter::E_WORLD_VIEW] || _changed_matrix_params[MatrixParameter::E_PROJ] )
	{
		d3Matrix::Mul(
			_matrix_params[MatrixParameter::E_WORLD_VIEW_PROJ],
			_matrix_params[MatrixParameter::E_WORLD_VIEW],
			_matrix_params[MatrixParameter::E_PROJ]
		);
		_changed_matrix_params[MatrixParameter::E_WORLD_VIEW_PROJ] = sTrue;
	}
	
	COUNTER_TIME_STOP( rd3_render_time_rstate );	
}

//---------------------------------------------------------------------------
void RenderState::RenderMesh( const Mesh* pMesh )
{
	__S_ASSERT( pMesh != NULL );

	pMesh->GetMaterial().Apply( *this );
	RenderPrimitive( &pMesh->GetVb(), &pMesh->GetIb(), pMesh->GetPrimitiveType() );
}	

//---------------------------------------------------------------------------
void RenderState::EndRenderObject()
{
#ifdef _DEBUG
	_bIsRenderingObject = sFalse;
#endif
	
	_changed_matrix_params[MatrixParameter::E_WORLD_NORMAL] = sFalse;	
	_changed_matrix_params[MatrixParameter::E_WORLD_VIEW] = sFalse;	
	_changed_matrix_params[MatrixParameter::E_WORLD_VIEW_PROJ] = sFalse;
	_changed_matrix_params[MatrixParameter::E_WORLD] = sFalse;
	_changed_matrix_params[MatrixParameter::E_D2_VIEW] = sFalse;
	
	_changed_transformation = sFalse;

}
///////////////////////////////////////////////////////////////////////////////
// WorldRenderState
///////////////////////////////////////////////////////////////////////////////
 
WorldRenderState::WorldRenderState( Render* owner ) :
	_BaseClass( owner )
{

}

//---------------------------------------------------------------------------
WorldRenderState::~WorldRenderState()
{
}

//---------------------------------------------------------------------------
void RenderState::SetRenderTarget( Texture* pTexture )
{
	_pRenderTarget = pTexture;

	if( _pRenderTarget != NULL )
	{
		_renderTargetSizeInPixels = d2Vector( (d3Float)pTexture->GetWidth(), (d3Float)pTexture->GetHeight() );
	}
	else
	{
		_renderTargetSizeInPixels = _pOwner->GetScreen_SizeInPixels();
	}

	if( _float_params[FloatParameter::E_RENDER_WIDTH] != _renderTargetSizeInPixels.x )
	{
		_float_params[FloatParameter::E_RENDER_WIDTH] = _renderTargetSizeInPixels.x;
		_changed_float_params[FloatParameter::E_RENDER_WIDTH] = sTrue;
	}

	if( _float_params[FloatParameter::E_RENDER_HEIGHT] != _renderTargetSizeInPixels.y )
	{
		_float_params[FloatParameter::E_RENDER_HEIGHT] = _renderTargetSizeInPixels.y;
		_changed_float_params[FloatParameter::E_RENDER_HEIGHT] = sTrue;
	}
}

//---------------------------------------------------------------------------
void WorldRenderState::BeginWorldRender( const EngineDataForRender& edata )
{
	_engineData = & edata;

	UpdateCamera();
	UpdateTime();
}

//---------------------------------------------------------------------------
void WorldRenderState::PostRender()
{
#ifdef _D3_DEBUG_RENDER_COUNTERS
	debug_RenderStats();
#endif	
}
	
//---------------------------------------------------------------------------
void WorldRenderState::EndWorldRender()
{	
	_engineData = NULL;
}

#ifdef _D3_DEBUG_RENDER_COUNTERS
	
//---------------------------------------------------------------------------
void WorldRenderState::debug_RenderStats()
{	
#ifdef _D3_DEBUG_RENDER_ENABLE_COUNTERS
	sInt ivCount = COUNTER_INT_VALUE( rd3_render_vertex_count );
	sInt ivPrimCount = COUNTER_INT_VALUE( rd3_render_primitive_count );
	
	sDouble renderProp = 
		100.0 * COUNTER_DOUBLE_VALUE( rd3_render_time_draw ) / COUNTER_DOUBLE_VALUE( rd3_render_time_frame );
	
	sDouble luaProp = 
		100.0 * COUNTER_DOUBLE_VALUE( rd3_render_time_lua ) / COUNTER_DOUBLE_VALUE( rd3_render_time_frame );
	
	sDouble phProp = 
		100.0 * COUNTER_DOUBLE_VALUE( rd3_render_time_physics ) / COUNTER_DOUBLE_VALUE( rd3_render_time_frame );
	
	sDouble renProp = 
		100.0 * COUNTER_DOUBLE_VALUE( rd3_render_time_rstate ) / COUNTER_DOUBLE_VALUE( rd3_render_time_frame );
	
	
#endif
	
	if ( !_renderFont ) 
		_renderFont = GetOwner()->UseFont( _S("system.font.default") );

	d2Vector pos( 0.01f, 0.01f );
	d2Vector screenSize = GetOwner()->GetScreen_SizeInPixels();
	
	BeginRenderObject();

	sString fsp = _S("Fps: ") + sString::IntToString( _engineData->GetFPS() ) + _S(" [") + 
		sString::IntToString( static_cast<sInt>( screenSize.x ) ) + _S("x") + 
		sString::IntToString( static_cast<sInt>( screenSize.y ) ) + _S("]");
	
	pos.y += _renderFont().ScreenRenderText( *this , fsp, pos, RGBColor::White );

#ifdef _D3_DEBUG_RENDER_ENABLE_COUNTERS
	
	sString rnd = _S("Render %: ") + sString::DoubleToString( renderProp );
	pos.y += _renderFont().ScreenRenderText( *this , rnd, pos, RGBColor::White );

	sString lnd = _S("Lua %: ") + sString::DoubleToString( luaProp );
	pos.y += _renderFont().ScreenRenderText( *this , lnd, pos, RGBColor::White );

	sString phs = _S("Physics %: ") + sString::DoubleToString( phProp );
	pos.y += _renderFont().ScreenRenderText( *this , phs, pos, RGBColor::White );

	sString rns = _S("Render State %: ") + sString::DoubleToString( renProp );
	pos.y += _renderFont().ScreenRenderText( *this , rns, pos, RGBColor::White );
	
	sString objs = _S("Objects : ") + 
		sString::IntToString( COUNTER_INT_VALUE( rd3_render_object_visible ) ) +
		_S("/") +
		sString::IntToString( COUNTER_INT_VALUE( rd3_render_object_total ) );
	
	pos.y += _renderFont().ScreenRenderText( *this , objs, pos, RGBColor::White );
	
	sString vbPrimCount = _S("Render Primitive count: ") + sString::IntToString( ivPrimCount );
	
	pos.y += _renderFont().ScreenRenderText( *this , vbPrimCount, pos, RGBColor::White );
	
	sString vbCount = _S("Render Vertex count: ") + sString::IntToString( ivCount );
	
	pos.y += _renderFont().ScreenRenderText( *this , vbCount, pos, RGBColor::White );
#endif
	EndRenderObject();

}

#endif // _D3_DEBUG_RENDER
	
}