////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_edata.cpp
//	Created            : 23.1.2011   4:25
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\cpp
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
#include "rd3_edata.h"

//----------------------------------------------------------------------
COUNTER_USE( rd3_render_vertex_count )
COUNTER_USE( rd3_render_primitive_count )
COUNTER_USE( rd3_render_time_frame )
COUNTER_USE( rd3_render_time_draw )
COUNTER_USE( rd3_render_time_lua )
COUNTER_USE( rd3_render_time_physics )

//----------------------------------------------------------------------
static void ResetFrameCounters()
{
	COUNTER_INT_SET( rd3_render_vertex_count, 0 )
	COUNTER_INT_SET( rd3_render_primitive_count, 0 );
	
	COUNTER_TIME_RESET( rd3_render_time_frame );
	COUNTER_TIME_RESET( rd3_render_time_draw );
	COUNTER_TIME_RESET( rd3_render_time_lua );
	COUNTER_TIME_RESET( rd3_render_time_physics );
	
	COUNTER_TIME_START( rd3_render_time_frame );
}
//----------------------------------------------------------------------
static void StopFrameCounters()
{
	COUNTER_TIME_STOP( rd3_render_time_frame );	
}

namespace Rd3
{

//----------------------------------------------------------------------
EngineDataForRender::EngineDataForRender() :
	_totalTime( 0.0f ),
	_deltaTime( 0.0f ),
	_totalTimeD( 0.0 ),
	_deltaTimeD( 0.0 ),
	_lastUpdateTimeD( 0 ),
	_totalFrameCount( 0 ),
	_fps( 0 ),
	_fpsFrameCount( 0 ),
	_fpsChanged( sTrue )
{
	_lastUpdateTimeD = System::Platform::GetTickD();
	_lastFpsUpdateTime = _lastUpdateTimeD;
}

//----------------------------------------------------------------------
EngineDataForRender::EngineDataForRender( const EngineDataForRender& src ) :
	_totalTime( src._totalTime ),
	_deltaTime( src._deltaTime ),
	_totalTimeD( src._totalTimeD ),
	_deltaTimeD( src._deltaTimeD ),
	_lastUpdateTimeD( src._lastUpdateTimeD ),
	_totalFrameCount( src._totalFrameCount ),
	_fps( src._fps ),
	_lastFpsUpdateTime( src._lastFpsUpdateTime ),
	_fpsFrameCount( src._fpsFrameCount ),
	_fpsChanged( sTrue ),
	_commonData( src._commonData )
{
}

//----------------------------------------------------------------------
void EngineDataForRender::operator = ( const EngineDataForRender& src )
{
	_totalTime = src._totalTime;
	_deltaTime = src._deltaTime;
	_totalTimeD = src._totalTimeD;
	_deltaTimeD = src._deltaTimeD;
	_lastUpdateTimeD = src._lastUpdateTimeD;
	_totalFrameCount = src._totalFrameCount;
	_fps = src._fps;
	_lastFpsUpdateTime = src._lastFpsUpdateTime;
	_fpsFrameCount = src._fpsFrameCount;
	_fpsChanged = sTrue;
	_commonData = src._commonData;
}

//----------------------------------------------------------------------
void EngineData::BeginFrame()
{
	sDouble ctime = System::Platform::GetTickD();

	_deltaTimeD = ( ctime - _lastUpdateTimeD );
	_totalTimeD += _deltaTime;
  
	_totalTime = (d3Float)_totalTimeD;
	_deltaTime = (d3Float)_deltaTimeD;
  
	_lastUpdateTimeD = ctime;
	
	ResetFrameCounters();
}

//----------------------------------------------------------------------
void EngineData::EndFrame()
{
	sDouble ctime = System::Platform::GetTickD();

	_totalFrameCount++;
	_fpsFrameCount++;

	if( ctime - _lastFpsUpdateTime >= 0.2 )
	{
		_fps = (sInt)(( _fpsFrameCount ) / ( ctime - _lastFpsUpdateTime ));
		_lastFpsUpdateTime = ctime;
		_fpsFrameCount = 0;
		_fpsChanged = sTrue;
	}
	else
		_fpsChanged = sFalse;
	
	StopFrameCounters();
}

}
