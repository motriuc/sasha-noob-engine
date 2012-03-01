////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_engine.cpp
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

#include "ed3afx.h"
#include "ed3_engine.h"
#include "ed3_world.h"
#include "ed3_types.h"
#include "ed3_rdata.h"

#include "rd3_render.h"
#include "rd3_rstate.h"


namespace Ed3 
{

//----------------------------------------------------------------------
d3Engine::d3Engine( Rd3::Render* pRender ) :
	_pRender( pRender ),
	_currentWorld( NULL )
{
	// set name aliases
	_archive.AddProvider( new Streams::ResourceArchiveProvider() );
	_archive.SetNameAlias( _S("engine"), _S("//res:/") );

	_pRender->Initialize( _def, _archive );
	
	/**
	_archive.SetNameAlias( _S("gameres"), _S("//res:/") );
	**/
/*	_currentWorld = new d3World();
	
	LoadDataParams loadParams( _def, _archive, *_pRender );
	
	_currentWorld->DoLoadFromXMLFile( _S("%gameres%/world.xml"), loadParams );
	_currentWorld->DoInitialize( *_pRender );*/
}

//----------------------------------------------------------------------
void d3Engine::RenderFrame()
{
	// do the AI
	if( _currentWorld == NULL )
		return;

	_engineData.BeginFrame();
	
	_currentWorld->DoAI( _engineData );
	_currentWorld->RenderWorld( *_pRender->RenderState(), _engineData );
	
	_engineData.EndFrame();	
}

//----------------------------------------------------------------------
d3Engine::~d3Engine()
{
	delete _currentWorld;
}

}