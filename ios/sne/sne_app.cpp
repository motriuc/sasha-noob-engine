#include "rd3afx.h"

#include "rd3_render.h"
#include "rd3_create_rparam.h"
#include "ed3_conf.h"
#include "ed3_engine.h"
#include "rd3_msg_gestureq.h"

#include "eagl_conf.h"
#include "eagl_msg_gestureq.h"
#include "eagl_serv_textedit.h"

#include "sne_app.h"

using namespace System;
using namespace Rd3;
using namespace Ed3;

//-----------------------------------------------------------------------------------
EngineApplication::EngineApplication( MACOSView* view ) throws_error:
	_pRender( NULL ),
	_pEngine( NULL ),
	_pTextEditService( NULL )
{
	Rd3::EAGLRenderCreateParams params( view );
		
	try
	{
		_pRender = Rd3::Render::CreateRender( params );
		_pGestureMsgQueue = new EaglGestureMsgQueue( _pRender, _S("engine.msg.gesture") );
		_pRender->AddMessageQueue( _pGestureMsgQueue );
		
		_pTextEditService = _pRender->CreateService<EAGLTextEditService>( _S("engine.service.textedit") );
		
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
void EngineApplication::Edit_AddText( const sString& text )
{
	if( _pTextEditService )
		_pTextEditService->AddText( text );
}

//-----------------------------------------------------------------------------------
void EngineApplication::Edit_DeleteBack()
{
	if( _pTextEditService )
		_pTextEditService->DeleteBack();
}

//-----------------------------------------------------------------------------------
void EngineApplication::Send( const GestureEvent& event )
{
	_pGestureMsgQueue->PostMessage( event );
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
	
	if( _pTextEditService )
		_pTextEditService->UnuseResource();
	
	delete _pEngine;
	delete _pRender;
}
