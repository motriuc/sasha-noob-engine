#include "rd3afx.h"

#include "eagl_conf.h"
#include "eagl_rstate.h"
#include "eagl_render.h"
#include "eagl_vertexbuffer.h"
#include "eagl_effect.h"
#include "eagl_indexbuffer.h"
#include "eagl_texture.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

COUNTER_USE( rd3_render_vertex_count )
COUNTER_USE( rd3_render_primitive_count )
COUNTER_USE( rd3_render_time_draw )

/************************************************************************/
/*                                                                      */
/************************************************************************/

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

/************************************************************************/
/*                                                                      */
/************************************************************************/

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

/************************************************************************/
/*                                                                      */
/************************************************************************/

EAGLRenderState::EAGLRenderState( Rd3::Render* owner ) :
	_BaseClass( owner )
{
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
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

/************************************************************************/
/*                                                                      */
/************************************************************************/

void EAGLRenderState::BeginWorldRender( const Rd3::EngineDataForRender& edata )
{
	_BaseClass::BeginWorldRender( edata );
	
	COUNTER_TIME_START( rd3_render_time_draw );
	
	EAGLRender* pRender = reinterpret_cast<EAGLRender*> ( GetOwner() );
	pRender->SetAsCurrentContext();			
	
	{
		Rd3::Texture* pRenderTarget = GetOwner()->GetTexture_RenderTarget();
		
		if( pRenderTarget != NULL )
			pRender->EaglSetRenderTarget( (EAGLTexture*)pRenderTarget );
	}

	
	glClearColor( 0.8f, 0.8f, 0.0f, 1.0f );
	glClearDepthf( 1.0f );
	glClearStencil( 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );	

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_FRONT );
	
	COUNTER_TIME_STOP( rd3_render_time_draw );
	
	if( !GetCommonData().RenderWireframe() )
	{
	}
	else
	{
	}
	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void EAGLRenderState::EndWorldRender()
{	
	EAGLRender* pRender = reinterpret_cast<EAGLRender*> ( GetOwner() );
	Rd3::Texture* pRenderTarget = pRender->GetTexture_RenderTarget();
	
	if( pRenderTarget == NULL )
		PostRender();
	
	
	COUNTER_TIME_START( rd3_render_time_draw );	
	{
		if( pRenderTarget != NULL )
			pRender->EaglSetRenderTarget( NULL );
		else 
			pRender->SetPresent();
	}
	
	COUNTER_TIME_STOP( rd3_render_time_draw );
	
	_BaseClass::EndWorldRender();	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

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

/************************************************************************/
/*                                                                      */
/************************************************************************/

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


