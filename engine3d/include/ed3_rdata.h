/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_rdata.h
//  Created             : 20 1 2012
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

#ifndef _ED3_RDATA_H_
#define _ED3_RDATA_H_

#ifndef _ED3_CONF_H_
#error ed3_conf.h must be included
#endif

#include "ed3_obj_class.h"

namespace  Ed3 
{

/**
 * d3RenderData
 */
class d3RenderData
{
public:
	/**
	 *
	 */
	d3RenderData( Rd3::RenderState* renderState, const d3ObjectClass& renderObjectClass );
	
	/**
	 *
	 */
	Rd3::RenderState& rstate() const { return *_renderState; }
	
	
	sBool RenderObject( const d3ObjectClass& cls ) const			{ return _renderObjectsClass.Contain( cls ); }
private:
	Rd3::RenderState*	_renderState;
	d3ObjectClass		_renderObjectsClass;
	
};

}

#endif // _ED3_RDATA_H_