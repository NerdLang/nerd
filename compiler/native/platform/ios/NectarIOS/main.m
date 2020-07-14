//
//  main.m
//  NectarIOS
//
//  Created by user175602 on 6/9/20.
//  Copyright © 2020 NectarJS. All rights reserved.
//
// clang \
-arch i386 \
-mios-simulator-version-min=6.1 \
-fobjc-abi-version=2 \
-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator6.1.sdk \
-o window window.m -framework Foundation -framework UIKit

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    
    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
