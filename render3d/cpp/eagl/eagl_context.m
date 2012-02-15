/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_context.cpp
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\cpp\eagl
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#define _OBJC_INC_

#import "platform_eagl_context.h"
#import <QuartzCore/QuartzCore.h>


EAGLRenderContext* EAGLRenderContext_Create()
{	
    EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!aContext)
    {
        aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    }
	
	if (!aContext) 
	{
		return NULL;
	}

	EAGLRenderContext* context = (EAGLRenderContext*)malloc(sizeof(EAGLRenderContext));
	
	context->_eaglContext = aContext;
	
	return context;
}

void EAGLRenderContext_Free( EAGLRenderContext* context )
{
	EAGLContext *aContext = context->_eaglContext;
	
    // Tear down context.
    if ([EAGLContext currentContext] == aContext)
        [EAGLContext setCurrentContext:nil];
    
	[aContext release];
	
	free(context);
}

void EAGLRenderContext_SetCurrent( EAGLRenderContext* context )
{
	EAGLContext *aContext = context->_eaglContext;
	
	[EAGLContext setCurrentContext:aContext];
}

void EAGLRenderContext_RenderbufferStorage( EAGLRenderContext* context, GLenum idBuf, const MACOSView* view )
{
	EAGLContext *aContext = context->_eaglContext;
	UIView* aView = view->_view;
	
	[aContext renderbufferStorage:idBuf fromDrawable:(CAEAGLLayer *)aView.layer];
}
 
GLboolean EAGLRenderContext_PresentRenderbuffer( EAGLRenderContext* context, GLenum idBuf )
{
	EAGLContext *aContext = context->_eaglContext;
	
	return [aContext presentRenderbuffer:idBuf];
}