/////////////////////////////////////////////////////////////////////
//  File Name               : platform_eagl_context.h
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\h\eagl
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

#ifndef _EAGL_CONTEXT_H_
#define _EAGL_CONTEXT_H_


#ifdef _OBJC_INC_
	#import <OpenGLES/EAGL.h>
#endif

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>


/**
  *
  */
typedef struct
{

#ifdef _OBJC_INC_
	EAGLContext*	_eaglContext;
#endif
	
} EAGLRenderContext;

/**
 * MACOSView
 */
typedef struct
{
#ifdef _OBJC_INC_
	UIView*		_view;
#endif	
} MACOSView;

/**
 * EAGLInitParams
 */
typedef struct 
{
} EAGLInitParams;

#ifdef __cplusplus
extern "C" {
#endif

void MACOSView_ShowKeyboard( MACOSView* view );
void MACOSView_HideKeyboard( MACOSView* view );
	
EAGLRenderContext* EAGLRenderContext_Create();
void EAGLRenderContext_Free( EAGLRenderContext* context );
	
void EAGLRenderContext_SetCurrent( EAGLRenderContext* context );
void EAGLRenderContext_RenderbufferStorage( EAGLRenderContext* context, GLenum idBuf, const MACOSView* view );
GLboolean EAGLRenderContext_PresentRenderbuffer( EAGLRenderContext* context, GLenum idBuf );
	
	
#ifdef __cplusplus
}
#endif
		
#endif // _EAGL_CONTEXT_H_