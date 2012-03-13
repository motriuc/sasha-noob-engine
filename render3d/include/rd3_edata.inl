////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_edata.inl
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

inline void EngineDataForRender::SetScreenViewCamera( const d3Camera& camera )
{
	_screenViewCamera = camera;
}


inline d3Float EngineDataForRender::GetTime() const
{
	return _totalTime; 
}

inline d3Float EngineDataForRender::GetDeltaTime() const
{
	return _deltaTime;
}

inline sUInt EngineDataForRender::GetFPS() const
{
	return _fps;
}

inline sBool EngineDataForRender::IsFPSChanged() const
{
	return _fpsChanged;
}

inline const CommonDataForRender& EngineDataForRender::GetCommonData() const
{
	return _commonData;
}

inline CommonDataForRender& EngineDataForRender::GetCommonData()
{
	return _commonData;
}

inline CommonData& EngineData::ModifyCommonData()
{
	return _commonData;
}




