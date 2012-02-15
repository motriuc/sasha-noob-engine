/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_texture.inl
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


inline sInt Texture::GetWidth() const
{
	return _width;
}

inline sInt Texture::GetHeight() const
{
	return _height;
}

inline TextureType::TextureType Texture::GetTextureType() const
{
	return _textureType;
}

inline sBool Texture::ReadOnly() const
{
	return _readOnly;
}


