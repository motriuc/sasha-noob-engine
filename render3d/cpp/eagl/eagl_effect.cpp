/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_effect.cpp
//	Created                 : 11 1 2012   22:43
//	File path               : SLibF\render3d\cpp\eagl
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
#include "eagl_conf.h"
#include "eagl_effect.h"
#include "eagl_texture.h"
#include "rd3_xml_def.h"

using namespace Rd3;
using namespace System;

/////////////////////////////////////////////////////////////////////////////////////////////
// EAGLEffect Internal
/////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
static GLuint CompileShader( GLenum type, const char* source, const sString& path ) throws_error
{
	__S_ASSERT( source != NULL );
	
	GLuint shader = glCreateShader( type );
	
    glShaderSource( shader, 1, &source, NULL );
    glCompileShader( shader );
    
#ifdef _DEBUG
    GLint logLength;
	
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLength );
	
    if( logLength > 0 )
    {
		sString log( logLength );
        glGetShaderInfoLog( shader, logLength, &logLength, log.GetCharBuffer() );
		log.UpdateLength();
		
        glDeleteShader( shader );
		
		error_throw_arg( System::Errors::StringError ) 
			_S("Compile shader '") + path + ("' error :") + log
		);
    }
#endif
    
    GLint status;
	
    glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
    if (status == 0)
    {
        glDeleteShader( shader );
		
		error_throw_arg( System::Errors::StringError ) 
			_S("Compile shader '") + path + ("' error :")
		);
		
    }
    
    return shader;
}

//-------------------------------------------------------------------------
static GLuint CompileShader( GLenum type, const Streams::StreamArchive& archive, const sString& path ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( path ) );
	
	sUInt length = pStream().GetSize();
	
	ptr_array_unique<char> charBuffer ( new char[length+1] );
	pStream().Read( charBuffer, length );
	charBuffer[length] = 0;
	
	return CompileShader( type, charBuffer, path );
}


/////////////////////////////////////////////////////////////////////////////////////////////
// EAGLEffect::EAGLEffect
/////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
EAGLEffect::EAGLEffect(
		Rd3::Render* owner,  
		const sString& objectName
		) :
	_BaseClass( owner, objectName ),
	_program( 0 ),
	_blendingEnabled( sFalse ),
	_blendingSourceFactor( 0 ),
	_blendingDestinationFactor( 0 )

{
	for( sInt i = 0; i < AttributeParameter::COUNT; ++i )
		_attributeIds[i] = -1;
}

//-------------------------------------------------------------------------
void EAGLEffect::LoadFromFile( const sString& filePath, const Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( filePath ) ); 
	
	sUInt length = pStream().GetSize();
	
	ptr_array_unique<char> charBuffer ( new char[length] );
	pStream().Read( charBuffer, length );
	
	LoadFromString( sString( charBuffer, length ), def, archive );
}

//-------------------------------------------------------------------------
#define ENUM_STRING_TEST( _x ) \
	if( text == _S( #_x ) ) \
		return _x;

GLenum Blending_GetSrcFactor( const sString& text ) throws_error
{
	ENUM_STRING_TEST( GL_ZERO )
	ENUM_STRING_TEST( GL_ONE )
	ENUM_STRING_TEST( GL_DST_COLOR )
	ENUM_STRING_TEST( GL_ONE_MINUS_DST_COLOR )
	ENUM_STRING_TEST( GL_SRC_ALPHA )
	ENUM_STRING_TEST( GL_ONE_MINUS_SRC_ALPHA )
	ENUM_STRING_TEST( GL_DST_ALPHA )
	ENUM_STRING_TEST( GL_ONE_MINUS_DST_ALPHA )
	ENUM_STRING_TEST( GL_SRC_ALPHA_SATURATE )
	
	error_throw_arg( Errors::StringError )
		_S("Invalid blending src factor : ") + text
	);
}

GLenum Blending_GetDstFactor( const sString& text ) throws_error
{
	ENUM_STRING_TEST( GL_ZERO )
	ENUM_STRING_TEST( GL_ONE )
	ENUM_STRING_TEST( GL_SRC_COLOR )
	ENUM_STRING_TEST( GL_ONE_MINUS_SRC_COLOR )
	
	ENUM_STRING_TEST( GL_SRC_ALPHA )
	ENUM_STRING_TEST( GL_ONE_MINUS_SRC_ALPHA )
	ENUM_STRING_TEST( GL_DST_ALPHA )
	ENUM_STRING_TEST( GL_ONE_MINUS_DST_ALPHA )
	
	error_throw_arg( Errors::StringError )
	_S("Invalid blending dst factor : ") + text
	);
}

//-------------------------------------------------------------------------
void EAGLEffect::LoadParams_Blending( const Xml::BaseDomNode& node, const Rd3::Def& def )
{
	_blendingEnabled = sTrue;
	_blendingSourceFactor = Blending_GetSrcFactor( node.GetAttributes()[ATTR_SRC] );
	_blendingDestinationFactor = Blending_GetDstFactor( node.GetAttributes()[ATTR_DST] );
}


//-------------------------------------------------------------------------
void EAGLEffect::LoadParams( const Xml::BaseDomNode& node, const Rd3::Def& def )
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;
	
		if( child.GetName() == ELEMENT_BLENDING )
			LoadParams_Blending( child, def );
	}
}

//-------------------------------------------------------------------------
void EAGLEffect::Apply( Rd3::RenderState& renderState ) const
{
	_BaseClass::Apply( renderState );
	
	if( _blendingEnabled )
	{
		glEnable( GL_BLEND );
		glBlendFunc( _blendingSourceFactor, _blendingDestinationFactor );
	}
	else 
	{
		glDisable( GL_BLEND );
	}

}

//-------------------------------------------------------------------------
void EAGLEffect::LoadFromXml(
							const Xml::BaseDomNode& node, 
							const Rd3::Def& def, 
							const Streams::StreamArchive& archive 
							) throws_error
{
	if( node.GetName() != ELEMENT_EFFECT )
		error_throw_arg( Errors::StringError )
			_S("effect element is missing")
		);
	
	sString vsPath;
	sString psPath;
	
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;

		if( child.GetName() == ELEMENT_DEFAULT )
		{
			vsPath = child.GetAttributes()[ATTR_VS];
			psPath = child.GetAttributes()[ATTR_PS];
			
			LoadParams( child, def );
		}
	}
	
	__S_ASSERT( _program == 0 );
	
	GLuint vertShader = 0;
	GLuint fragShader = 0;
	
    _program = glCreateProgram();
	
	try 
	{
		vertShader = CompileShader( GL_VERTEX_SHADER, archive, vsPath );
		fragShader = CompileShader( GL_FRAGMENT_SHADER, archive, psPath );

		// Attach vertex shader to program.
		glAttachShader( _program, vertShader );
		
		// Attach fragment shader to program.
		glAttachShader( _program, fragShader );
		
		// link the program
		glLinkProgram( _program );
		
#ifdef _DEBUG
		GLint logLength;
		glGetProgramiv( _program, GL_INFO_LOG_LENGTH, &logLength );
		if ( logLength > 0 )
		{			
			sString log( logLength );			
			glGetProgramInfoLog( _program, logLength, &logLength, log.GetCharBuffer() );
			log.UpdateLength();
			
			error_throw_arg( System::Errors::StringError ) 
				_S("Link program error :") + log
			);
		}
#endif
		
		GLint status;
		
		glGetProgramiv( _program, GL_LINK_STATUS, &status );
		
		if( status == 0 )
			error_throw_arg( System::Errors::StringError ) 
				_S("Link program error : Unknown") 
			);
		
		InitParamLinks();		
		BindAttributes();
		
	}
	catch(...)
	{
		if (vertShader)
			glDeleteShader( vertShader );	
		if (fragShader)
			glDeleteShader( fragShader );
		if (_program)
			glDeleteProgram( _program );
		
		throw;		
	}

	if (vertShader)
		glDeleteShader( vertShader );	
	
	if (fragShader)
		glDeleteShader( fragShader );
	
	
}

//-------------------------------------------------------------------------
void EAGLEffect::BindAttributes()
{
	__S_ASSERT( _program != 0 );
	
	GLint attrCount = 0;	
	glGetProgramiv( _program, GL_ACTIVE_ATTRIBUTES, &attrCount );
	
	sString unknownAttr;
	
	for( GLint i = 0; i < attrCount; ++i )
	{
		GLchar nameBuffer[128];
		GLsizei nameSize;
		GLint plength;
		GLenum ptype;
		
		glGetActiveAttrib( _program, i, 128, &nameSize, &plength, &ptype, nameBuffer );
		
		sString paramName( nameBuffer );
	
		AttributeParameter::AttributeParameter p = AttributeParameter::GetType( paramName );
		if( p != AttributeParameter::UNKNOWN )
		{
			__S_ASSERT( _attributeIds[p] == -1 );
			_attributeIds[p] = i;
		}
		else 
			unknownAttr += paramName + _S(";");
	}
	
	if( unknownAttr.Length() > 0 ) 
	{
		System::Platform::ShowWarning( 
			_S("The folowing attributes :[") + unknownAttr + _S("] from '") + GetObjectName() + _S("' are not supported.")
		);
	}
	
}

//-------------------------------------------------------------------------
void EAGLEffect::LoadFromString(
								const sString& effect, 
								const Rd3::Def& def, 
								const Streams::StreamArchive& archive 
								) throws_error
{	
	ptr_unique<Xml::DomDocument> pDocument( Xml::DomDocument::Read( effect ) );
	
	LoadFromXml( pDocument().GetRoot(), def, archive );	
}

//-------------------------------------------------------------------------
EAGLEffect::~EAGLEffect()
{
	if( _program != 0 ) 
	{
		glDeleteProgram(_program);
	}
}

//-------------------------------------------------------------------------
void EAGLEffect::InitParamLinks()
{
	__S_ASSERT( _program != 0 );
	
	GLint activeUniforms = 0;
		
	glGetProgramiv( _program, GL_ACTIVE_UNIFORMS, &activeUniforms );
	
	sString unknownParams;
	
	for (GLint i = 0; i < activeUniforms; ++i ) 
	{
		GLchar nameBuffer[128];
		GLsizei nameSize;
		GLint plength;
		GLenum ptype;
		glGetActiveUniform( _program, i, 128, &nameSize, &plength, &ptype, nameBuffer );
		
		sString paramName( nameBuffer );
	
		GLint hParam = glGetUniformLocation( _program, paramName ) + 1;
		
		switch (ptype) 
		{
			case GL_FLOAT_MAT4:
			{
				MatrixParameter::MatrixParameter p = MatrixParameter::GetType( paramName );

				if( p != MatrixParameter::UNKNOWN )
					SetIndex( p, hParam );
				else
					unknownParams += paramName + _S(";");
			}	
			break;
				
			case GL_FLOAT:
			{
				FloatParameter::FloatParameter p = FloatParameter::GetType( paramName );
				
				if( p != FloatParameter::UNKNOWN )
					SetIndex( p, hParam );
				else
					_floatDynamicParams.Add( paramName, hParam );
			}
			break;
				
			case GL_FLOAT_VEC4:
			{
				VectorParameter::VectorParameter p = VectorParameter::GetType( paramName );
				
				if( p != VectorParameter::UNKNOWN )
					SetIndex( p, hParam );
				else
					unknownParams += paramName + _S(";");
			}
			break;
				
			case GL_SAMPLER_2D:
			{
				TextureParameter::TextureParameter p = TextureParameter::GetType( paramName );
				if ( p != TextureParameter::UNKNOWN ) 
					SetIndex( p, hParam );
				else
					unknownParams += paramName + _S(";");
			}
			break;
								
			default:
				unknownParams += paramName + _S(";");				

		}
	}
	
	if (unknownParams.Length() > 0 ) 
	{
		System::Platform::ShowWarning( 
			_S("The folowing params :[") + unknownParams + _S("] from '") + GetObjectName() + _S("' are not supported.")
		);
	}	
}

//-------------------------------------------------------------------------
void EAGLEffect::Set( sUInt h, const d3Matrix& m ) const
{
	__S_ASSERT( sizeof( sFloat ) == sizeof( GLfloat ) );
	
	glUniformMatrix4fv( h-1, 1, GL_FALSE, m.v );
}

//-------------------------------------------------------------------------
void EAGLEffect::Set( sUInt h, const d3Vector& v ) const
{
	__S_ASSERT( sizeof( sFloat ) == sizeof( GLfloat ) );

	glUniform4fv( h-1, 1, v.v ); 
}

//-------------------------------------------------------------------------
void EAGLEffect::Set( sUInt h, const d3Float f ) const
{
	glUniform1f( h-1, (GLfloat)f );
}

//-------------------------------------------------------------------------
void EAGLEffect::Set( sUInt h, const sBool b ) const
{
	__S_ASSERT( sFalse );
}

//-------------------------------------------------------------------------
void EAGLEffect::Set( sUInt i, sUInt h, const Rd3::Texture* t ) const
{
	__S_ASSERT( t != NULL );
	
	glUniform1i( h-1, i );
	const EAGLTexture* pTexture = reinterpret_cast< const EAGLTexture*>( t );
	
	glActiveTexture( GL_TEXTURE0 + i );	
	glBindTexture( GL_TEXTURE_2D, pTexture->GetHandle() );
}
