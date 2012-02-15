////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_cdata.h
//	Created            : 12.4.2006   21:14
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


#if !defined(_RD3_CDATA_H_)
#define _RD3_CDATA_H_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

namespace Rd3
{

class CommonData;

/**
 * CommonDataForRender
 */
class CommonDataForRender
{
public:
	CommonDataForRender();
  
	sBool RenderWireframe() const;

#ifdef _D3_DEBUG_RENDER
	// debug render options
	sBool debug_RenderObjectsBoundingBox() const;
	sBool debug_RenderCulling() const;
	sBool debug_RenderLights() const;
	sBool debug_RenderObjectCenter() const;
	sBool debug_RenderObjects() const;
	sBool debug_RenderAdjacency() const;
  
	//
	sBool debug_TestBoundingBox() const;
#endif
 
private:
	sBool       _bRenderWireframe;

#ifdef _D3_DEBUG_RENDER
	sBool       _debug_RenderBBox;
	sBool       _debug_TestBBox;
	sBool       _debug_Culling;
	sBool       _debug_RenderObjectCenter;
	sBool       _debug_RenderLights;
	sBool       _debug_RenderObjects;
	sBool       _debug_RenderAdjacency;
#endif
	friend class CommonData;
};

/**
 * CommonData
 */
class CommonData : public CommonDataForRender
{
public:
	void SetRenderWireframe( sBool bVal );

#ifdef _D3_DEBUG_RENDER
	void debug_SetRenderObjectsBoundingBox( sBool bVal );
	void debug_SetRenderCulling( sBool bVal );
	void debug_SetRenderObjectCenter( sBool bVal );
	void debug_SetRenderLights( sBool bVal );
	void debug_SetRenderAdjacency( sBool bVal );

	void debug_SetTestBoundingBox( sBool bVal );
	void debug_SetRenderObjects( sBool bVal );
#endif
};

#include "rd3_cdata.inl"

}

#endif // !defined(_RD3_CDATA_H_)
