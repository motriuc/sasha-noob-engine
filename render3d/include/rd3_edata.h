////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_edata.h
//	Created            : 23.1.2011   4:25
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
#ifndef _RD3_EDATA_H_
#define _RD3_EDATA_H_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_cdata.h"

namespace Rd3
{
	
class EngineData;

/**
 * EngineDataForRender
 */
class EngineDataForRender
{
public:
	EngineDataForRender();

	d3Float GetTime() const;
	d3Float GetDeltaTime() const;

	sUInt GetFPS() const;
	sBool IsFPSChanged() const;

	const CommonDataForRender& GetCommonData() const;
	CommonDataForRender& GetCommonData();

protected:
	EngineDataForRender( const EngineDataForRender& src );
	void operator = ( const EngineDataForRender& src );
private:
	sDouble     _totalTimeD;
	sDouble     _deltaTimeD;
	d3Float     _totalTime;
	d3Float     _deltaTime;

	sUInt       _totalFrameCount;
	sDouble     _lastUpdateTimeD;

	sUInt       _fps;
	sDouble     _lastFpsUpdateTime;
	sUInt       _fpsFrameCount;
	sBool       _fpsChanged;

protected:
	CommonData	_commonData;
	
	friend class EngineData;
};

/**
 * EngineData
 */
class EngineData : public EngineDataForRender
{
public:
	/**
	 *
	 */
	void BeginFrame();

	/**
	 *
	 */
	void EndFrame();

	/**
	 *
	 */
	CommonData& ModifyCommonData();
};

#include "rd3_edata.inl"

}

#endif // _RD3_EDATA_H_