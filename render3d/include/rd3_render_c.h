

#include "platform_eagl_context.h"
#include "rd3_msg_gesture.h"

namespace Rd3
{
	class Render;
	class GestureMsgQueue;
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
	void Send( const GestureEvent& event ); 
	
	~EngineApplication();
private:
	Rd3::Render*			_pRender;
	Ed3::d3Engine*			_pEngine;
	Rd3::GestureMsgQueue*	_pGestureMsgQueue;
};
