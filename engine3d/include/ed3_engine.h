////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_engine.h
//	Created            : 30 1 2012   19:09
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\engine3d\include
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

#ifndef _ED3_ENGINE_INC_
#define _ED3_ENGINE_INC_

#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif

#include "ed3_edata.h"
#include "rd3_def.h"

namespace  Ed3 
{

class d3World;

/**
 * d3Engine
 */
class d3Engine 
{
public:
	/**
	 *
	 */
	d3Engine( Rd3::Render* pRender );
	
	/**
	 *
	 */
	void RenderFrame();
	
	/**
	 *
	 */
	~d3Engine();
	
	/**
	 * 
	 */
	Streams::StreamArchive& Archive()	{ return _archive; }
	
	/**
	 *
	 */
	void LoadWorld( const sString& path ) throws_error;
	
	/**
	 *
	 */
	void SetWorld( d3World* pWorld ) throws_error;
private:
	Rd3::Render*	_pRender;

	d3EngineData			_engineData;
	Streams::StreamArchive	_archive;	
	Rd3::Def				_def;
	
	d3World*				_currentWorld;
};

}

#endif

