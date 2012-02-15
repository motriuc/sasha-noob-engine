////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_light_sel.h
//	Created            : 5 2 2012   17:25
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
#ifndef _RD3_LIGHT_SEL_INC_
#define _RD3_LIGHT_SEL_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_light.h"

namespace Rd3
{

/**
 * LightSelection
 */
class LightSelection
{
public:
	LightSelection( sInt maxLights );
		
	/**
	 *
	 */
	void AddLight( const Light* light );
	
	/**
	 *
	 */
	void SetPosition( const d3Vector& p );
	
	/*
	 *
	 */
	void AddLight( const LightList& list );
	
	/**
	 *
	 */
	sInt Size() const { return _lightSelection.Size(); }
	
	/**
	 *
	 */
	const Light& operator[]( sInt i ) const { return *_lightSelection[i].pLight; }
	
private:
	class LSel
	{
	public:	
		const Light*	pLight;
		d3Float			visibilityFactor;
	};
	
	class Cmp_LSel
	{
	public:
		inline static sBool Big( const LSel& a, const LSel& b )
		{
			return a.visibilityFactor > b.visibilityFactor;
		}
		
		inline static sBool Equal( const LSel& a, const LSel& b )
		{
			return a.visibilityFactor == b.visibilityFactor;
		}
		
		inline static sBool Small( const LSel& a, const LSel& b )
		{
			return a.visibilityFactor < b.visibilityFactor;
		}
	};
	
	d3Vector				_position;
	sSorted<LSel,Cmp_LSel>	_lightSelection;
};
	
}

#endif // _RD3_LIGHT_SEL_INC_