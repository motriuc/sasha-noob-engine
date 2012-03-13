/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_edata.h
//  Created             : 19 1 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\include
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////

#ifndef _ED3_EDATA_H_
#define _ED3_EDATA_H_

#ifndef _ED3_CONF_H_
#error ed3_conf.h must be included
#endif

#include "ed3_edata.h"
#include "rd3_edata.h"

namespace Ed3 
{

/**
 * d3EngineData
 */
class d3EngineData : public Rd3::EngineData
{
public:
	/**
	 *
	 */
	d3EngineData();
	
	using EngineData::BeginFrame;
	using EngineData::EndFrame;
	using EngineData::SetScreenViewCamera;

};
	
}

#endif // _ED3_EDATA_H_