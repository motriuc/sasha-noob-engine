/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_texture.cpp
//	Created                 : 31 1 2011   19:58
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
#include "rd3afx.h"
#include "rd3_texture.h"

namespace Rd3
{

/************************************************************************/
/*                                                                      */
/************************************************************************/

Texture::Texture( Render* owner, const sString& objectName, const TextureParams& params ) :
	_BaseClass( owner, objectName, ResourceType::E_TEXTURE ),
	_width( 0 ),
	_height( 0 ),
	_textureType( TextureType::UNKNOWN ),
	_readOnly( sTrue ),
	_params( params )
{
}

}