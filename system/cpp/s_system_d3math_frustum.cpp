/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_frustum.cpp
//  Created                 : 22 1 2011   22:28
//  File path               : SLibF\system\Include
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

#define _use_d3Math_

#include "s_system.h"

namespace System { namespace d3Math {
	
using namespace System::Types;

sBool d3Frustum::Intersect( const d3AABBox& b ) const
{
	for( sInt i = 0; i < _planes.Size(); i++ )
	{
		// < 0 means back
		if( _planes[i].Classify( b ) < 0 )
			return sFalse;
	}
	return sTrue;
}


}}
