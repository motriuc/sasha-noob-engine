////////////////////////////////////////////////////////////////////////
//  File Name          : rd3_perf_counters.cpp
//  Created            : 20 1 2012   23:04
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\render3d\include
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
#include "rd3afx.h"
#include "rd3_perf_counters.h"


//-----------------------------------------------------------------------

namespace Rd3
{

//-----------------------------------------------------------------------
sVector<PerformanceCounter>	PerformanceCounter::_counters;

//-----------------------------------------------------------------------
PerformanceCounter::PerformanceCounter()
{
}

//-----------------------------------------------------------------------
PerformanceCounter& PerformanceCounter::Counter( sInt idc )
{
	return _counters[idc];
}
	
//-----------------------------------------------------------------------
PerformanceCounter::PerformanceCounter( const sString& name, const sString& units, const sString& description ):
	_intCounter( 0 ),
	_floatCounter( 0.0f ),
	_doubleCounter( 0.0 ),
	_currentTime( 0.0 ),
	
	_id( -1 ),
	
	_name( name ),
	_units( units ),
	_description( description )
{
}

//-----------------------------------------------------------------------
sInt PerformanceCounter::Register( const PerformanceCounter& perfc )
{
	sInt nid = _counters.Add( perfc );
	_counters[nid]._id  = nid;
	
	return nid;
}

//-----------------------------------------------------------------------
	
}

//-----------------------------------------------------------------------
// Standard render counder definitions
//-----------------------------------------------------------------------

COUNTER_DECLARE(
				rd3_video_memory, 
				_S("rd3.video.memory"),
				_S("bytes"),
				_S("total used video memory")
				)

COUNTER_DECLARE( 
				rd3_video_memory_vb, 
				_S("rd3.video.memory.vb"),
				_S("bytes"),
				_S("total used video memory for vertex buffers")
				)

COUNTER_DECLARE( 
				rd3_vertex_count, 
				_S("rd3.vertex.count"),
				_S(""),
				_S("total used vertex count")
				)

COUNTER_DECLARE( 
				rd3_render_vertex_count, 
				_S("rd3.render.vertex.count"),
				_S(""),
				_S("total vertex count rendered per frame")
				)

COUNTER_DECLARE( 
				rd3_render_primitive_count, 
				_S("rd3.render.primitive.count"),
				_S(""),
				_S("total primitive count rendered per frame")
				)


COUNTER_DECLARE(
				rd3_video_memory_ib,
				_S("rd3.video.memory.ib"),
				_S("bytes"),
				_S("total used video memory for index buffers")
				)

COUNTER_DECLARE( 
				rd3_index_count,
				_S("rd3.index.count"),
				_S(""),
				_S("total index buffer count")
				)

COUNTER_DECLARE( 
				rd3_render_time_frame,
				_S("rd3.render.time.frame"),
				_S(""),
				_S("total frame time")
				)

COUNTER_DECLARE( 
				rd3_render_time_draw,
				_S("rd3.render.time.draw"),
				_S(""),
				_S("total rendering time")
				)
COUNTER_DECLARE( 
				rd3_render_time_lua,
				_S("rd3.render.time.lua"),
				_S(""),
				_S("lua code execution time")
				)

COUNTER_DECLARE( 
				rd3_render_time_physics,
				_S("rd3.render.time.physics"),
				_S(""),
				_S("physics code execution time")
				)

COUNTER_DECLARE( 
				rd3_render_time_rstate,
				_S("rd3.render.time.rstate"),
				_S(""),
				_S("time spent in maintainig render state")
				)

COUNTER_DECLARE( 
				rd3_render_object_total,
				_S("rd3.render.object.total"),
				_S(""),
				_S("total number of objects participating in the rendering")
				)

COUNTER_DECLARE( 
				rd3_render_object_visible,
				_S("rd3.render.object.visible"),
				_S(""),
				_S("number of objects redered")
				)


//-----------------------------------------------------------------------
