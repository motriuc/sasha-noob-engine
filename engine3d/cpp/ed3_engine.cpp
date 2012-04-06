////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_engine.cpp
//  Created            : 30 1 2012   19:09
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
extern void RegisterEngineTypes();
//----------------------------------------------------------------------
d3Engine::d3Engine( Rd3::Render* pRender ) :
	_pRender( pRender ),
	_currentWorld( NULL )
{
	RegisterEngineTypes();

	// set name aliases
	_archive.AddProvider( new Streams::ResourceArchiveProvider() );
	_archive.SetNameAlias( _S("engine"), _S("//res:/") );

	_pRender->Initialize( _def, _archive );
}

//----------------------------------------------------------------------
void d3Engine::LoadWorld( const sString& path ) throws_error
{
	d3World* world = new d3World();
	
	LoadDataParams loadParams( _def, _archive, *_pRender );
	
	try 
	{
		world->DoLoadFromXMLFile( path, loadParams );
		SetWorld( world );
	}
	catch (...) 
	{
		delete world;
		throw;
	}
}

//----------------------------------------------------------------------
void d3Engine::SetWorld( d3World* pWorld ) throws_error
{
	if( _currentWorld != NULL )
	{
		_currentWorld->DoUninitalize( *_pRender ); 
		delete _currentWorld;
	}
	
	_currentWorld = NULL;
	
	if( pWorld != NULL )
	{
		pWorld->DoInitialize( *_pRender );
		_currentWorld = pWorld;

		UpdateCameraAspect();
	}
}

//----------------------------------------------------------------------
void d3Engine::RenderFrame()
{
	// do the AI
	if( _currentWorld == NULL )
		return;

	try
	{
		_engineData.BeginFrame();
		_engineData.SetScreenViewCamera( _currentWorld->GetCamera() );
		
		_pRender->ProcessMessages( _engineData );
		_pRender->ProcessServces( _engineData );
		
		_currentWorld->DoAI( _engineData );
		_currentWorld->RenderWorld( *_pRender->RenderState(), _engineData );
	}
	catch( Errors::Error* e )
	{
		Platform::DebugWarning( e->Description() );
		delete e;
	}

	_engineData.EndFrame();	
}

//----------------------------------------------------------------------
d3Engine::~d3Engine()
{
	if( _currentWorld != NULL )
	{
		_currentWorld->DoUninitalize( *_pRender );
		delete _currentWorld;
	}
}

//----------------------------------------------------------------------
void d3Engine::UpdateCameraAspect()
{
	if( _pRender != NULL && _currentWorld != NULL )
	{
		d2Vector size = _pRender->GetScreen_SizeInPixels();
		_currentWorld->GetCamera().SetAspect( size.y / size.x );
	}
}

}