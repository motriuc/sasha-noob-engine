////////////////////////////////////////////////////////////////////////
//  File Name          : rd3_resloadparams.h
//  Created            : 3 3 2012   19:09
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//  Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

#ifndef _RD3_RESLOAD_PARAM_H_
#define _RD3_RESLOAD_PARAM_H_

#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_types.h"

namespace Rd3 
{

/**
 * ResLoadParams
 */
class ResLoadParams
{
public:
	/**
	 *
	 */
	ResLoadParams( const Def& idef, const Streams::StreamArchive& iarchive, Render& irender ) :
		def( idef ),
		archive( iarchive ),
		render( irender )
	{
	}
	
public:	
	const Rd3::Def& def;
	const Streams::StreamArchive& archive;
	Render& render;
};
	
	
}


#endif // _RD3_RESLOAD_PARAM_H_
