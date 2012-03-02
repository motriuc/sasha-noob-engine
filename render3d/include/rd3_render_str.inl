/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_render_str.inl
//	Created                 : 3 3 2012   19:58
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

inline Render& RenderString::render()
{
	return *(_font().GetOwner());
}

inline const Font& RenderString::font()
{
	return _font();
}

inline d3Float RenderString::RenderHeight() const
{
	return _fontRenderHeight;
}

inline RenderString::RenderString( Font* font ) :
	_font( font ),
	_fontRenderHeight( 0.0f )
{
}
