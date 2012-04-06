//
//  sd3engiphViewController.h
//  sd3engiph
//
//  Created by Alexandru Motriuc on 16/02/12.
//  Copyright 2012 Home. All rights reserved.
//

#import <UIKit/UIKit.h>


#define _OBJC_INC_

#include "platform_eagl_context.h"

// forward declarations
class EngineApplication;


@interface sd3engiphViewController : UIViewController<UIKeyInput>
{
@private	
	EngineApplication*	render;
	MACOSView*			renderView;
    BOOL				animating;
    CADisplayLink*		displayLink;
    NSInteger			animationFrameInterval;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

- (void)startAnimation;
- (void)stopAnimation;

@end
