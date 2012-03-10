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
#include "eagl_render.h"

#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGBitmapContext.h>
#include <CoreFoundation/CoreFoundation.h>

//-------------------------------------------------------------------
GLenum glfilterType[Rd3::TextureFilteringType::COUNT] = 
{
	GL_NEAREST,
	GL_LINEAR
};

//-------------------------------------------------------------------
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
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glfilterType[_params.MinFilter()] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glfilterType[_params.MagFilter()] );
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
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glfilterType[_params.MinFilter()] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glfilterType[_params.MagFilter()] );
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
	else if( path.EndsWith( _S(".pvr") ) )
	{
		ptr_unique<const Streams::IInputStream> pStream( arch.Open( path ) );
		LoadFromPvrStream( pStream(), path );
	}			
	else 
	{
		error_throw_arg( Errors::StringError )
			_S("Unknown texture type: " ) + path
		);
	}
}

//-------------------------------------------------------------------
// PVR File definition
//-------------------------------------------------------------------

namespace PVRTexture
{
	/**
	 * PVR Typess
	 */
	typedef uint32_t PVRTuint32;

	typedef struct
	{
		PVRTuint32 dwHeaderSize;		/*!< size of the structure */
		PVRTuint32 dwHeight;			/*!< height of surface to be created */
		PVRTuint32 dwWidth;				/*!< width of input surface */
		PVRTuint32 dwMipMapCount;		/*!< number of mip-map levels requested */
		PVRTuint32 dwpfFlags;			/*!< pixel format flags */
		PVRTuint32 dwTextureDataSize;	/*!< Total size in bytes */
		PVRTuint32 dwBitCount;			/*!< number of bits per pixel  */
		PVRTuint32 dwRBitMask;			/*!< mask for red bit */
		PVRTuint32 dwGBitMask;			/*!< mask for green bits */
		PVRTuint32 dwBBitMask;			/*!< mask for blue bits */
		PVRTuint32 dwAlphaBitMask;		/*!< mask for alpha channel */
		PVRTuint32 dwPVR;				/*!< magic number identifying pvr file */
		PVRTuint32 dwNumSurfs;			/*!< the number of surfaces present in the pvr */
	} Header;
	
	/**
	 * the pvr identifier is the characters 'P','V','R'
	 */
	static const PVRTuint32 IDENTIFIER = 0x21525650;
	
	/**
	 *  pixel type is always in the last 16bits of the flags
	 */
	static const PVRTuint32 PIXELTYPE = 0xff;		
	
	enum PixelType
	{
		// OpenGL version of pixel types
		OGL_RGBA_4444= 0x10,
		OGL_RGBA_5551,
		OGL_RGBA_8888,
		OGL_RGB_565,
		OGL_RGB_555,
		OGL_RGB_888,
		OGL_I_8,
		OGL_AI_88,
		OGL_PVRTC2,
		OGL_PVRTC4,
		OGL_BGRA_8888,
		OGL_A_8,
		OGL_PVRTCII4,	//Not in use
		OGL_PVRTCII2	//Not in use		
	};
}
	
//-------------------------------------------------------------------
void EAGLTexture::LoadFromPvrStream( const Streams::IInputStream& stream, const sString& path ) throws_error
{
	PVRTexture::Header header;
	
	if( stream.Read( &header, sizeof( header ) ) != sizeof( header ) )
		error_throw_arg( Errors::StringError )
			_S("Invalid Pvr texture : " ) + path
		);
		
	if( header.dwPVR != PVRTexture::IDENTIFIER || header.dwHeaderSize != sizeof(PVRTexture::Header) )
	{
		error_throw_arg( Errors::StringError )
			_S("Invalid Pvr texture : " ) + path
		);		
	}
	
	PVRTexture::PVRTuint32 type = header.dwpfFlags & PVRTexture::PIXELTYPE;
	
	if( type != PVRTexture::OGL_PVRTC2 && type != PVRTexture::OGL_PVRTC4 )
	{
		error_throw_arg( Errors::StringError )
			_S("Unsupported Pvr pixel type : " ) + path
		);		
	}
	
	if( !FMath::IsPowOf2( header.dwHeight ) || !FMath::IsPowOf2( header.dwWidth ) )
	{
		error_throw_arg( Errors::StringError )
			_S("Pvr must have power of 2 size :" ) + path
		);		
	}
	
	sInt dataLength = header.dwTextureDataSize;
	sInt fileSize = stream.GetSize();
	
	if( dataLength + sizeof(PVRTexture::Header) > fileSize )
	{
		error_throw_arg( Errors::StringError )
			_S("Pvr texture is not compleate :" ) + path
		);		
	}
		
	GLuint internalFormat;
	
	if( type == PVRTexture::OGL_PVRTC4 )
		internalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
	else if( type == PVRTexture::OGL_PVRTC2 )
		internalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
		
	glGenTextures( 1, &_texture );
	glBindTexture( GL_TEXTURE_2D, _texture );
	
	_height = header.dwHeight;
	_width = header.dwWidth;
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glfilterType[_params.MinFilter()] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glfilterType[_params.MagFilter()] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gladdressType[_params.AddressU()] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gladdressType[_params.AddressV()] );
	
	ptr_array_unique<SBYTE> dataBuffer( new SBYTE[dataLength] );
	stream.Read( dataBuffer, dataLength );
	if( header.dwMipMapCount == 1 )
	{
		
	}
	else
	{
		sInt width = _width;
		sInt height = _height;
		sInt dataOffset = 0;
		
		for( sInt i = 0; i < header.dwMipMapCount; ++i )
		{
			sInt blockSize;
			sInt widthBlocks;
			sInt heightBlocks;
			sInt bpp;
			
			switch ( type )
			{
			case PVRTexture::OGL_PVRTC4:
				blockSize = 4 * 4;
				widthBlocks = width / 4;
				heightBlocks = height / 4;
				bpp = 4;
				break;
					
			case PVRTexture::OGL_PVRTC2:
				blockSize = 8 * 4;
				widthBlocks = width / 8;
				heightBlocks = height / 4;
				bpp = 2;
				break;
					
			default:
				__S_ASSERT( sFalse );
				break;
			}
			
			// Clamp to minimum number of blocks
			if( widthBlocks < 2 )
				widthBlocks = 2;
			if( heightBlocks < 2 )
				heightBlocks = 2;
			
			sInt dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);
			
			glCompressedTexImage2D(
				GL_TEXTURE_2D, i, 
				internalFormat,
				width, height, 0,
				dataSize, 
				dataBuffer.ptr( dataOffset )
			);
			
			GLenum err = glGetError();
			if( err != GL_NO_ERROR )
			{
				error_throw_arg( Errors::StringError )
					_S("Error uploading the texture :" ) + path
				);				
			}
			
			dataOffset += dataSize;
			
			width = FMath::Max( width >> 1, 1 );
			height = FMath::Max( height >> 1, 1 );
		}
	}

}

