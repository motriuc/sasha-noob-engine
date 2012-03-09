#include "rd3afx.h"
#include "rd3_render_c.h"
#include "rd3_render.h"
#include "rd3_create_rparam.h"
#include "ed3_conf.h"
#include "ed3_engine.h"
#include "rd3_msg_gestureq.h"

using namespace System;
using namespace Rd3;
using namespace Ed3;

//-----------------------------------------------------------------------------------
EngineApplication::EngineApplication( MACOSView* view ) throws_error:
	_pRender( NULL ),
	_pEngine( NULL )
{
	Rd3::EAGLRenderCreateParams params( view );
		
	try
	{
		_pRender = Rd3::Render::CreateRender( params );
		_pGestureMsgQueue = new GestureMsgQueue( _pRender, _S("engine.msg.gesture") );
		_pRender->AddMessageQueue( _pGestureMsgQueue );
		
		_pEngine = new d3Engine( _pRender );
		
		// load world.xml as default for iOs
		_pEngine->Archive().SetNameAlias( _S("gameres"), _S("//res:/") );
		_pEngine->LoadWorld( _S("%gameres%/world.xml") );
	}
	catch(...)
	{
		delete _pRender;
		throw;
	}		
}

//-----------------------------------------------------------------------------------
void EngineApplication::Send( const GestureEvent& event )
{
	/**
	 to do
	if( _pGestureMsgQueue != NULL )
		_pGestureMsgQueue->SendMessage( event );
	 */
}

//-----------------------------------------------------------------------------------
void EngineApplication::RenderFrame() throws_error
{
	if( _pEngine != NULL )
	{
		_pEngine->RenderFrame();
	}
}
	
//-----------------------------------------------------------------------------------
EngineApplication::~EngineApplication()
{
	if( _pGestureMsgQueue )
		_pGestureMsgQueue->UnuseResource();
	
	delete _pEngine;
	delete _pRender;
}
