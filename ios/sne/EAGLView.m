//
//  EAGLView.m
//  sd3engiph
//
//  Created by Alexandru Motriuc on 16/02/12.
//  Copyright 2012 Home. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "EAGLView.h"

@implementation EAGLView

@synthesize delegate;

//----------------------------------------------------------------
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

//----------------------------------------------------------------
//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:.
- (id)initWithCoder:(NSCoder*)coder
{
    self = [super initWithCoder:coder];
	
	if (self)
    {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
                                        kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
                                        nil];
    }
    

    return self;
}

//----------------------------------------------------------------
- (void)insertText:(NSString *)text
{
    // Do something with the typed character
	[self.delegate insertText: text];
}

//----------------------------------------------------------------
- (void)deleteBackward 
{
    // Handle the delete key
	[self.delegate deleteBackward];
}

//----------------------------------------------------------------
- (BOOL)hasText 
{
    // Return whether there's any text present
	return [self.delegate hasText];
}

//----------------------------------------------------------------
- (BOOL)canBecomeFirstResponder 
{
	return YES;
}

@end
