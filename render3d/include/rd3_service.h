/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_service.h
//  Created                 : 6 4 2012
//  File path               : SLibF\render3d\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#ifndef _RD3_SERVICE_INC_
#define _RD3_SERVICE_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"

namespace Rd3
{
	
using namespace System;
	
/**
 * Service
 */
class Service : public ResourceObject
{
private:	
	typedef ResourceObject _BaseClass;
public:
	Service( Render* owner, const sString& objectName ) :
		_BaseClass( owner, objectName, ResourceType::E_SERVICE )
	{
	}

	virtual void Process( EngineData& edata ) {}
};

	
}

#endif // _RD3_SERVICE_INC_