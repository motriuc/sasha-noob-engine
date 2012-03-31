//
//  sd3engiphViewController.m
//  sd3engiph
//
//  Created by Alexandru Motriuc on 16/02/12.
//  Copyright 2012 Home. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "sd3engiphViewController.h"
#import "EAGLView.h"
@interface sd3engiphViewController ()
@property (nonatomic, assign) CADisplayLink *displayLink;
@end

@implementation sd3engiphViewController

@synthesize animating, displayLink;

#define _use_sError_
#define _use_d3Math_

#include "s_system.h"
#include "sne_app.h"

using namespace System::d3Math;
using namespace Rd3;

//---------------------------------------------------------------------------
-(void)awakeFromNib
{
	//new
	renderView = (MACOSView*)malloc(sizeof(MACOSView));
	renderView->_view = self.view;
	
#ifdef _D3_ENABLE_RETINA_DISPLAY
	
	float ver = [[[UIDevice currentDevice] systemVersion] floatValue];
	
	if( ver >= 4.0 )
	{
		self.view.contentScaleFactor = [[UIScreen mainScreen] scale];
	}
	
#endif //
	
	try 
	{
		render = new EngineApplication( renderView );
	}	
	catch (System::Errors::Error* error ) 
	{
		System::Platform::ShowError( error->ToString() );
		delete error;
	}
	catch (...) 
	{
		System::Platform::ShowError( _S("Unknown Error") );
	}
	
    animating = FALSE;
    animationFrameInterval = 1;
    self.displayLink = nil;
}

//---------------------------------------------------------------------------
-(void)dealloc
{
	delete render;
	free(renderView);
    
    [super dealloc];
}

//---------------------------------------------------------------------------
-(void)viewWillAppear:(BOOL)animated
{
    [self startAnimation];
    
    [super viewWillAppear:animated];
}

//---------------------------------------------------------------------------
-(void)viewWillDisappear:(BOOL)animated
{
    [self stopAnimation];
    
    [super viewWillDisappear:animated];
}

//---------------------------------------------------------------------------
-(void)viewDidUnload
{
	[super viewDidUnload];
}

//---------------------------------------------------------------------------
-(NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

//---------------------------------------------------------------------------
-(void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;
        
        if (animating)
        {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

//---------------------------------------------------------------------------
-(void)startAnimation
{
    if (!animating)
    {
        CADisplayLink *aDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawFrame)];
        [aDisplayLink setFrameInterval:animationFrameInterval];
        [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        self.displayLink = aDisplayLink;
        
        animating = TRUE;
    }
}

//---------------------------------------------------------------------------
-(void)stopAnimation
{
    if (animating)
    {
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
    }
}

//---------------------------------------------------------------------------
-(void)drawFrame
{
	try 
	{
		render->RenderFrame();
	}
	catch (System::Errors::Error* error ) 
	{
		System::Platform::ShowError( error->ToString() );
		delete error;
	}
	catch (...) 
	{
		System::Platform::ShowError( _S("Unknown Error") );
	}
}

//---------------------------------------------------------------------------
-(void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

//---------------------------------------------------------------------------
void ConvertoToGestureEvent( GestureEvent& ev, NSSet* touches, UIView* view )
{
	CGRect rc = view.bounds;
	
	for( UITouch* touch in touches )
	{
		CGPoint point = [touch locationInView: view ];
		
		point.x = point.x / rc.size.width;
		point.y = point.y / rc.size.height;
		
		point.x = 2.0f * point.x - 1.0f;
		point.y = 1.0f - 2.0f * point.y;
		
		GestureTap tap( d3Vector( point.x, point.y, 0.0f ) );
		ev.Add( tap );
    }
}

//---------------------------------------------------------------------------
-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{	
	if( render )
	{
		GestureEvent ev( GestureEvent::E_Begin );
		ConvertoToGestureEvent( ev, [event allTouches], self.view );
		render->Send( ev );
	}
}

//---------------------------------------------------------------------------
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	if( render )
	{
		GestureEvent ev( GestureEvent::E_End );
		ConvertoToGestureEvent( ev, [event allTouches], self.view );
		render->Send( ev );
	}
}

//---------------------------------------------------------------------------
-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	if( render )
	{
		GestureEvent ev( GestureEvent::E_Move );
		ConvertoToGestureEvent( ev, [event allTouches], self.view );
		render->Send( ev );
	}
}

@end