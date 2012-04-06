

#include "platform_eagl_context.h"
#include "rd3_msg_gesture.h"

class EaglGestureMsgQueue;
class EAGLTextEditService;

namespace Rd3
{
	class Render;
	class GestureMsgQueue;
	class Service;
}

namespace Ed3
{
	class d3Engine;
}

/**
 * EngineApplication
 */
class EngineApplication 
{
public:
	/**
	 *
	 */
	EngineApplication( MACOSView* view ) throws_error;
	
	/**
	 *
	 */
	void RenderFrame() throws_error;
	
	/**
	 *
	 */
	void Send( const Rd3::GestureEvent& event );

	void Edit_AddText( const sString& text );
	void Edit_DeleteBack();
	
	~EngineApplication();
private:
	Rd3::Render*			_pRender;
	Ed3::d3Engine*			_pEngine;
	EaglGestureMsgQueue*	_pGestureMsgQueue;
	EAGLTextEditService*	_pTextEditService;
};
