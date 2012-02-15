////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_cdata.inl
//	Created            : 12.4.2006   21:18
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

inline CommonDataForRender::CommonDataForRender() :
	_bRenderWireframe( sFalse )
#ifdef _D3_DEBUG_RENDER
	,
	_debug_RenderBBox( sFalse ),
	_debug_TestBBox( sTrue ),
	_debug_Culling( sTrue ),
	_debug_RenderObjectCenter( sFalse ),
	_debug_RenderLights( sFalse ),
	_debug_RenderObjects( sTrue ),
	_debug_RenderAdjacency( sFalse )
#endif
 {
 }

inline sBool CommonDataForRender::RenderWireframe() const
{
	return _bRenderWireframe;
}

inline void CommonData::SetRenderWireframe( sBool bVal )
{
	_bRenderWireframe = bVal;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

#ifdef _D3_DEBUG_RENDER

inline sBool CommonDataForRender::debug_RenderAdjacency() const
{
	return _debug_RenderAdjacency;
}

inline void CommonData::debug_SetRenderAdjacency( sBool bVal )
{
	_debug_RenderAdjacency = bVal;
}

inline sBool CommonDataForRender::debug_RenderObjects() const
{
	return _debug_RenderObjects;
}

inline void CommonData::debug_SetRenderObjects( sBool bVal )
{
	_debug_RenderObjects = bVal;
}

inline sBool CommonDataForRender::debug_RenderLights() const
{
	return _debug_RenderLights;
}

inline void CommonData::debug_SetRenderLights( sBool bVal )
{
	_debug_RenderLights = bVal;
}

inline sBool CommonDataForRender::debug_RenderObjectCenter() const
{
	return _debug_RenderObjectCenter;
}

inline void CommonData::debug_SetRenderObjectCenter( sBool bVal )
{
	_debug_RenderObjectCenter = bVal;
}

inline sBool CommonDataForRender::debug_RenderCulling() const
{
	return _debug_Culling;
}

inline void CommonData::debug_SetRenderCulling( sBool bVal )
{
	_debug_Culling = bVal;
}

inline sBool CommonDataForRender::debug_RenderObjectsBoundingBox() const
{
	return _debug_RenderBBox;
}

inline void CommonData::debug_SetRenderObjectsBoundingBox( sBool bVal )
{
	_debug_RenderBBox = bVal;
}

inline sBool CommonDataForRender::debug_TestBoundingBox() const
{
	return _debug_TestBBox;
}

inline void CommonData::debug_SetTestBoundingBox( sBool bVal )
{
	_debug_TestBBox = bVal;
}

#endif

