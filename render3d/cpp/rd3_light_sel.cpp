////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_light_sel.cpp
//	Created            : 5 2 2012   21:53
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
#include "rd3_light_sel.h"
#include "rd3_xml_def.h"

using namespace System;

namespace Rd3
{
//----------------------------------------------------------------------	
LightSelection::LightSelection( sInt maxLights ) :
	_lightSelection( maxLights )
{
	_lightSelection.Reserve( maxLights );
}

//----------------------------------------------------------------------	
void LightSelection::AddLight( const Light* light )
{
	LSel sel;
	sel.pLight = light;
	sel.visibilityFactor = light->GetVisibilityFactor( _position );
	
	_lightSelection.Add( sel );
}	

//----------------------------------------------------------------------	
void LightSelection::AddLight( const LightList& list )
{
	for( sInt i = 0; i < list.Size(); ++i )
	{
		AddLight( &list[i] );
	}
}
	
//----------------------------------------------------------------------	
void LightSelection::SetPosition( const d3Vector& p )
{
	_position = p;
	_lightSelection.RemoveAll();
}
	
}