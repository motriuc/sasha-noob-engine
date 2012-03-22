//
//  sd3engiphAppDelegate.h
//  sd3engiph
//
//  Created by Alexandru Motriuc on 16/02/12.
//  Copyright 2012 Home. All rights reserved.
//

#import <UIKit/UIKit.h>

@class sd3engiphViewController;

@interface sd3engiphAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    sd3engiphViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet sd3engiphViewController *viewController;

@end

