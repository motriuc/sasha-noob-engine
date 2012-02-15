/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_types.inl
//	Created                 : 4 2 2012   0:05
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
	
inline TextureParams::TextureParams():
	_minFilter( TextureFilteringType::E_LINIAR ),
	_magFilter( TextureFilteringType::E_LINIAR ),
	_addressU( TextureAddressingType::E_REPEAT ),
	_addressV( TextureAddressingType::E_REPEAT )
{
}
	
inline TextureFilteringType::TextureFilteringType TextureParams::MinFilter() const
{
	return _minFilter;
}
	
inline TextureFilteringType::TextureFilteringType TextureParams::MagFilter() const
{
	return _magFilter;
}
	
inline TextureAddressingType::TextureAddressingType TextureParams::AddressU() const
{
	return _addressU;
}
	
inline TextureAddressingType::TextureAddressingType TextureParams::AddressV() const
{
	return _addressV;
}

inline void TextureParams::SetMinFilter( TextureFilteringType::TextureFilteringType v )
{
	_minFilter = v;
}

inline void TextureParams::SetMaxFilter( TextureFilteringType::TextureFilteringType v )
{
	_magFilter = v;
}

inline void TextureParams::SetAddressU( TextureAddressingType::TextureAddressingType v )
{
	_addressU = v;
}

inline void TextureParams::SetAddressV( TextureAddressingType::TextureAddressingType v )
{
	_addressV = v;
}

