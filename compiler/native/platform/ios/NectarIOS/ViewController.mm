//
//  ViewController.m
//  NectarIOS
//
//  Created by user175602 on 6/9/20.
//  Copyright © 2020 NectarJS. All rights reserved.
//

#import "ViewController.h"
#import "ios.hpp"

@interface ViewController ()

@end

@implementation ViewController
@synthesize webView;
-(void) viewDidLoad {
    [super viewDidLoad];
    
    WKWebViewConfiguration *configuration = [[WKWebViewConfiguration alloc] init];
    NSString *scriptString = @"function __NJS_fireiOSEvent(str){window.webkit.messageHandlers.notification.postMessage(str);}; window.Nectar = {fireEvent:__NJS_fireiOSEvent };";
    
    WKUserScript *script = [[WKUserScript alloc] initWithSource:scriptString injectionTime:WKUserScriptInjectionTimeAtDocumentEnd forMainFrameOnly:YES];
    WKUserContentController* userController = [[WKUserContentController alloc] init];
    [userController addUserScript:script];
    [userController addScriptMessageHandler:self name:@"notification"];
    configuration.userContentController = userController;

    self.webView = [[WKWebView alloc] initWithFrame:self.view.bounds configuration:configuration];
    [self.view addSubview:self.webView];

    self.webView.backgroundColor = [UIColor whiteColor];
    self.webView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);

    [self performSelectorInBackground:@selector(selLaunchServer) withObject:nil];

    [self.view addSubview:self.webView];
    loadedCallback(self.webView);
}
- (void)userContentController:(WKUserContentController*)userContentController didReceiveScriptMessage:(WKScriptMessage*)message
{
        njsCallback(self.webView, message.body);
}
    
- (void) selLaunchServer
{
    launchServer();
}

@end
