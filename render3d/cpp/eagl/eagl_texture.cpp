/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_texture.cpp
//	Created                 : 18 1 2012   0:05
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

#include "rd3afx.h"
#include "eagl_conf.h"
#include "eagl_texture.h"
#include "eagl_font_utils.h"

#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGBitmapContext.h>

// 
GLenum glfilterType[Rd3::TextureFilteringType::COUNT] = 
{
	GL_NEAREST,
	GL_LINEAR
};

//
GLenum gladdressType[Rd3::TextureAddressingType::COUNT] = 
{
	GL_REPEAT,
	GL_CLAMP_TO_EDGE
};


//-------------------------------------------------------------------
EAGLTexture::EAGLTexture( Rd3::Render* owner, const sString& objectName, Rd3::TextureType::TextureType type, const Rd3::TextureParams& params ) :
	_BaseClass( owner, objectName, params ),
	_texture( 0 )
{
	_textureType = type;
}

//-------------------------------------------------------------------
EAGLTexture::EAGLTexture( Rd3::Render* owner, const sString& objectName, Rd3::TextureType::TextureType type, sInt width, sInt height, const Rd3::TextureParams& params ):
	_BaseClass( owner, objectName, params ),
	_texture( 0 )
{
	glGenTextures( 1, &_texture );
	glBindTexture( GL_TEXTURE_2D, _texture );
	
	_width = width;
	_height = height;
	_textureType = type;
	
	_readOnly = sFalse;
	
	// force CLAMP for non power of 2 textures
	if( !FMath::IsPowOf2( _width ) || !FMath::IsPowOf2( _width ) )
	{
		_params.SetAddressU( Rd3::TextureAddressingType::E_CLAMP );
		_params.SetAddressV( Rd3::TextureAddressingType::E_CLAMP );		
	}
	
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, glfilterType[_params.MinFilter()] );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, glfilterType[_params.MagFilter()] );
	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gladdressType[_params.AddressU()] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gladdressType[_params.AddressV()] );
	
	switch( _textureType ) 
	{
		case Rd3::TextureType::E_IMAGE:
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
			break;
		case Rd3::TextureType::E_ALPHA:
			glTexImage2D( GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, 0 );
			break;
		default:
			__S_ASSERT( sFalse );
			break;
	}
	
}

//-------------------------------------------------------------------
EAGLTexture::~EAGLTexture()
{
	if( _texture != 0 )
	{
		glDeleteTextures( 1, &_texture );
	}
}

//-------------------------------------------------------------------
void EAGLTexture::LoadFromImage( CGImageRef image ) throws_error
{
	__S_ASSERT( _texture == 0 );
	
	GLuint width = CGImageGetWidth( image );
	GLuint height = CGImageGetHeight( image );
	
	char *imageData = new char[height * width * 4];
	
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	
    CGContextRef context = CGBitmapContextCreate(
		imageData, 
		width, height, 
		8, 4 * width,
		colorSpace,
		kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big
	);
	
    CGColorSpaceRelease( colorSpace );
	
    CGContextClearRect( context, CGRectMake( 0, 0, width, height ) );
    CGContextDrawImage( context, CGRectMake( 0, 0, width, height ), image );
	
	glGenTextures( 1, &_texture );
	glBindTexture( GL_TEXTURE_2D, _texture );
	
	_height = height;
	_width = width;
	
	// force CLAMP for non power of 2 textures
	if( !FMath::IsPowOf2( _width ) || !FMath::IsPowOf2( _width ) )
	{
		_params.SetAddressU( Rd3::TextureAddressingType::E_CLAMP );
		_params.SetAddressV( Rd3::TextureAddressingType::E_CLAMP );		
	}
	
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, glfilterType[_params.MinFilter()] );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, glfilterType[_params.MagFilter()] );
	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gladdressType[_params.AddressU()] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gladdressType[_params.AddressV()] );
	
	
	switch( _textureType ) 
	{
		case Rd3::TextureType::E_IMAGE:
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData );
			break;
		case Rd3::TextureType::E_ALPHA:
			{
				char* lumData = new char[height * width];
				
				for( sInt i = 0; i < height* width; ++i )
					lumData[i] = imageData[4*i];
				glTexImage2D( GL_TEXTURE_2D, 0, GL_LUMINANCE, _width, _height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, lumData );
				delete[] lumData;
			}
			break;
		default:
			__S_ASSERT( sFalse );
			break;
	}

    CGContextRelease( context );
	
	
    delete[] imageData;
}

//-------------------------------------------------------------------
void EAGLTexture::SetHandle( GLuint textId, sInt width, sInt height )
{
	__S_ASSERT( _texture == 0 );
	
	_texture = textId;
	_width = width;
	_height = height;
}

//-------------------------------------------------------------------
void EAGLTexture::LoadFromPngStream( const Streams::IInputStream& stream ) throws_error
{	
	CGImageRef imageRef;
	{
	
		CGDataProviderRef dataProvider = Streams::IInputStream_To_CGDataProviderRef( &stream );

		imageRef = CGImageCreateWithPNGDataProvider( dataProvider, NULL, false, kCGRenderingIntentDefault );
	
		CGDataProviderRelease( dataProvider );
	}
	
	LoadFromImage( imageRef );
			
	CGImageRelease( imageRef );
}

//-------------------------------------------------------------------
void EAGLTexture::LoadFromFile( const sString& path, const Streams::StreamArchive& arch ) throws_error
{	
	if( path.EndsWith( _S(".png") ) )
	{
		ptr_unique<const Streams::IInputStream> pStream( arch.Open( path ) );
		LoadFromPngStream( pStream() );
	}
	else 
	{
		error_throw_arg( Errors::StringError )
			_S("Unknown texture type: " ) + path
		);
	}
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
