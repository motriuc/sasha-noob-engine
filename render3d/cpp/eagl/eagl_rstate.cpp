/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_rstate.cpp
//  Created                 : 18 1 2012   0:05
//  File path               : SLibF\render3d\cpp\eagl
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
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

#include "eagl_conf.h"
#include "eagl_rstate.h"
#include "eagl_render.h"
#include "eagl_vertexbuffer.h"
#include "eagl_effect.h"
#include "eagl_indexbuffer.h"
#include "eagl_texture.h"
#include "rd3_after_effect.h"


#include "rd3_aef_blur.h"

using namespace System::d3Math;
using namespace System::d2Math;

//-----------------------------------------------------------------------
COUNTER_USE( rd3_render_vertex_count )
COUNTER_USE( rd3_render_primitive_count )
COUNTER_USE( rd3_render_time_draw )

//-----------------------------------------------------------------------
namespace PrimitiveType
{
	inline GLenum GetEAGLType( Rd3::PrimitiveType::PrimitiveType p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < Rd3::PrimitiveType::COUNT );
		
		GLenum vals[Rd3::PrimitiveType::COUNT] = 
		{
			GL_POINTS,
			GL_LINES,
			GL_LINE_STRIP,
			GL_TRIANGLES,
			GL_TRIANGLE_STRIP,
			GL_TRIANGLE_FAN
		};
		
		return vals[p];
	}
}

//-----------------------------------------------------------------------
#ifdef _DEBUG

void ValidateProgram( const EAGLEffect* pEffect )
{
	GLint logLength, status;
	GLuint prog = pEffect->GetHandle();

	glValidateProgram( prog );
	glGetProgramiv( prog, GL_INFO_LOG_LENGTH, &logLength );
	
	if( logLength > 0 )
	{
		sString log( logLength );
		
		glGetProgramInfoLog( prog, logLength, &logLength, log.GetCharBuffer() );
		log.UpdateLength();
		
		Platform::ShowWarning( _S("Invalid effect ") + pEffect->GetObjectName() + _S("' : ") + log  );
	}


	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	if( status == 0 )
	{
		Platform::ShowWarning( _S("Invalid effect '") + pEffect->GetObjectName() + _S("'") );		
	}
}

#endif // _DEBUG

//-----------------------------------------------------------------------
EAGLRenderState::EAGLRenderState( Rd3::Render* owner ) :
	_BaseClass( owner ),
	_afterEffectVb( NULL )
{
	_afterEffectTextures[0] = NULL;
	_afterEffectTextures[1] = NULL;	
}

//-----------------------------------------------------------------------
EAGLRenderState::~EAGLRenderState()
{
	if( _afterEffectTextures[0] != NULL )
		_afterEffectTextures[0]->UnuseResource();
	if( _afterEffectTextures[1] != NULL )
		_afterEffectTextures[1]->UnuseResource();
	
	if( _afterEffectVb != NULL )
		_afterEffectVb->UnuseResource();
}

//-----------------------------------------------------------------------
void EAGLRenderState::InitAfterEffectData()
{
	if( _afterEffectTextures[0] != NULL )
		return;
	
	
	Rd3::Render* render = GetOwner();	
	
	__S_ASSERT( render != NULL );
	
	d2Vector size = render->GetScreen_SizeInPixels();
	
	sInt width = (sInt)size.x;
	sInt height = (sInt)size.y;

	
	Rd3::TextureParams params;
	params.SetMinFilter( Rd3::TextureFilteringType::E_NEAREST );
	params.SetMaxFilter( Rd3::TextureFilteringType::E_NEAREST );
	params.SetAddressU( Rd3::TextureAddressingType::E_CLAMP );
	params.SetAddressV( Rd3::TextureAddressingType::E_CLAMP );
	
	_afterEffectTextures[0] = render->CreateTexture( _S(""), width, height, Rd3::TextureType::E_IMAGE, params );
	_afterEffectTextures[1] = render->CreateTexture( _S(""), width, height, Rd3::TextureType::E_IMAGE, params );
	
	
	Rd3::VertexPList	points;
	Rd3::VertexTxCoord	txCoord;
	
	points.Add( d3Vector( -1.0f,  1.0f, 0.0f ) );
	points.Add( d3Vector(  1.0f, -1.0f, 0.0f ) );
	points.Add( d3Vector( -1.0f, -1.0f, 0.0f ) );

	points.Add( d3Vector( -1.0f,  1.0f, 0.0f ) );
	points.Add( d3Vector(  1.0f,  1.0f, 0.0f ) );
	points.Add( d3Vector(  1.0f, -1.0f, 0.0f ) );
	
	txCoord.Add( d2Vector( 0.0f, 1.0f ) );
	txCoord.Add( d2Vector( 1.0f, 0.0f ) );
	txCoord.Add( d2Vector( 0.0f, 0.0f ) );

	txCoord.Add( d2Vector( 0.0f, 1.0f ) );
	txCoord.Add( d2Vector( 1.0f, 1.0f ) );
	txCoord.Add( d2Vector( 1.0f, 0.0f ) );
	
	
	_afterEffectVb = render->CreateVertexBuffer( _S(""), points, txCoord );
	
	
	_effect = render->UseEffect( _S("system.after.effect.none") );
}

//-----------------------------------------------------------------------
void EAGLRenderState::Clear( System::Types::sRGBColor color )
{
	COUNTER_TIME_START( rd3_render_time_draw );
	
    glClearColor( 
				 RGBColor::GetFloatR( color ),
				 RGBColor::GetFloatG( color ),
				 RGBColor::GetFloatB( color ),
				 RGBColor::GetFloatA( color )
	);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );	

	COUNTER_TIME_STOP( rd3_render_time_draw );	
}

//-----------------------------------------------------------------------
void EAGLRenderState::BeginAfterEffect()
{	
	EAGLRender* pRender = reinterpret_cast<EAGLRender*> ( GetOwner() );
	__S_ASSERT( pRender != NULL );
	
	// support affter effects only for screen target
	__S_ASSERT( GetRenderTarget() == NULL );
	
	InitAfterEffectData();
	pRender->EaglSetRenderTarget( reinterpret_cast<EAGLTexture*>( _afterEffectTextures[0] ) );
}

//-----------------------------------------------------------------------
void EAGLRenderState::EndAfterEffect()
{
	__S_ASSERT( GetAfterEffect() != NULL );
	__S_ASSERT( GetOwner() != NULL );

	EAGLRender& render = *reinterpret_cast<EAGLRender*>(GetOwner());	
	const Rd3::AfterEffect& aeffect = *GetAfterEffect();
	
	
	sInt srcTexture = 0;
	sInt dstTexture = 1;
	
	for( sInt i = 0; i < aeffect.ElementCount(); ++i )
	{
		glDisable( GL_DEPTH_TEST );
		glDisable( GL_CULL_FACE );
		glDisable( GL_BLEND );
		
		if( i == aeffect.ElementCount() - 1 )
		{
			render.EaglSetRenderTarget( NULL );
			render.SetAsCurrentContext();
		}
		else
			render.EaglSetRenderTarget( (EAGLTexture*)_afterEffectTextures[dstTexture] );

		SetTexture( Rd3::TextureParameter::E_TEX1, _afterEffectTextures[srcTexture] );
		aeffect.GetElement( i ).Apply( *this );
		RenderPrimitive( _afterEffectVb, Rd3::PrimitiveType::E_TRIANGLE_LIST );
		
		srcTexture = ( srcTexture + 1 ) % 2;
		dstTexture = ( dstTexture + 1 ) % 2;
	}
}

//-----------------------------------------------------------------------
void EAGLRenderState::BeginNoAfterEffect()
{
	EAGLRender* pRender = reinterpret_cast<EAGLRender*> ( GetOwner() );
	
	__S_ASSERT( pRender != NULL );
	
	
	if( GetRenderTarget() != NULL )
		pRender->EaglSetRenderTarget( (EAGLTexture*)GetRenderTarget() );
	else 
		pRender->SetAsCurrentContext();
}

//-----------------------------------------------------------------------
void EAGLRenderState::BeginWorldRender( const Rd3::EngineDataForRender& edata )
{	
	_BaseClass::BeginWorldRender( edata );

	COUNTER_TIME_START( rd3_render_time_draw );

	if( GetAfterEffect() != NULL && GetAfterEffect()->ElementCount() > 0 )
		BeginAfterEffect();
	else
		BeginNoAfterEffect();	
	
	glClearColor( 0.8f, 0.8f, 0.0f, 1.0f );
	glClearDepthf( 1.0f );
	glClearStencil( 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );	

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	
	COUNTER_TIME_STOP( rd3_render_time_draw );
	
	if( !GetCommonData().RenderWireframe() )
	{
	}
	else
	{
	}
	
}

//-----------------------------------------------------------------------
void EAGLRenderState::EndWorldRender()
{	
	EAGLRender* pRender = reinterpret_cast<EAGLRender*> ( GetOwner() );
	
	if( GetAfterEffect() != NULL && GetAfterEffect()->ElementCount() > 0 )
		EndAfterEffect();
	
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_CULL_FACE );
	
	if( GetRenderTarget() == NULL )
		PostRender();
	
	
	COUNTER_TIME_START( rd3_render_time_draw );	
	{
		if( GetRenderTarget() != NULL )
			pRender->EaglSetRenderTarget( NULL );
		else 
			pRender->SetPresent();
	}
	
	COUNTER_TIME_STOP( rd3_render_time_draw );		
	
	
	_BaseClass::EndWorldRender();	
}

//-----------------------------------------------------------------------
void EAGLRenderState::RenderPrimitive( const Rd3::VertexBuffer* vb, Rd3::PrimitiveType::PrimitiveType type )
{
	__S_ASSERT( vb!= NULL );
	__S_ASSERT( GetOwner() == vb->GetOwner() );
	__S_ASSERT( GetEffect() != NULL );
	__S_ASSERT( GetOwner() ==  GetEffect()->GetOwner() );

	const EAGLEffect* pEffect = reinterpret_cast<const EAGLEffect*>( GetEffect() );
	const EAGLVertexBuffer* pVertexBuffer = reinterpret_cast<const EAGLVertexBuffer*>( vb );
	
	__S_ASSERT( pEffect->GetHandle() != 0 );
	
	COUNTER_TIME_START( rd3_render_time_draw );
	
	glUseProgram( pEffect->GetHandle() );
	
	// Set effect params
	pEffect->Apply( *this );
	pVertexBuffer->SetAttributes( pEffect->AttributeIds() );
	
#ifdef _DEBUG
	ValidateProgram( pEffect );
#endif	

	glDrawArrays( PrimitiveType::GetEAGLType( type ), 0, pVertexBuffer->GetCount() );
	
	COUNTER_TIME_STOP( rd3_render_time_draw );
	
	COUNTER_INT_INC( rd3_render_vertex_count, pVertexBuffer->GetCount() );
	COUNTER_INT_INC( rd3_render_primitive_count, 
		Rd3::PrimitiveType::GetNumberOfPrimitives( pVertexBuffer->GetCount(), type ) 
	);
}

//-----------------------------------------------------------------------
void EAGLRenderState::RenderPrimitive( const Rd3::VertexBuffer* vb, const Rd3::IndexBuffer* ib, Rd3::PrimitiveType::PrimitiveType type )
{
	__S_ASSERT( vb!= NULL );
	__S_ASSERT( GetOwner() == vb->GetOwner() );
	__S_ASSERT( GetEffect() != NULL );
	__S_ASSERT( GetOwner() ==  GetEffect()->GetOwner() );
	__S_ASSERT( ib != NULL );
	__S_ASSERT( GetOwner() == ib->GetOwner() );


	const EAGLEffect* pEffect = reinterpret_cast<const EAGLEffect*>( GetEffect() );
	const EAGLVertexBuffer* pVertexBuffer = reinterpret_cast<const EAGLVertexBuffer*>( vb );
	const EAGLIndexBuffer* pIndexBuffer = reinterpret_cast<const EAGLIndexBuffer*>( ib );
	
	__S_ASSERT( pEffect->GetHandle() != 0 );
	
	COUNTER_TIME_START( rd3_render_time_draw );
	
	glUseProgram( pEffect->GetHandle() );
	
	// Set effect params
	pEffect->Apply( *this );
	pVertexBuffer->SetAttributes( pEffect->AttributeIds() );
	
#ifdef _DEBUG
	ValidateProgram( pEffect );
#endif	
	
	glDrawElements( 
		PrimitiveType::GetEAGLType( type ), 
		pIndexBuffer->GetCount(), 
		pIndexBuffer->GetBufferType(), 
		pIndexBuffer->GetBuffer()
	);
		
	COUNTER_TIME_STOP( rd3_render_time_draw );
	
	COUNTER_INT_INC( rd3_render_vertex_count, pIndexBuffer->GetCount() );
	COUNTER_INT_INC( rd3_render_primitive_count, 
		Rd3::PrimitiveType::GetNumberOfPrimitives( pIndexBuffer->GetCount(), type ) 
	);
}


