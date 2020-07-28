//
//  ViewController.m
//  NectarIOS
//
//  Copyright © 2020 NectarJS. All rights reserved.
//

#import "ViewController.h"
#include <sys/sysctl.h>
#import "../ios.hpp"

@interface ViewController () <WKUIDelegate, WKNavigationDelegate>

@end

@implementation ViewController

@synthesize webView;
-(void) viewDidLoad {
    [super viewDidLoad];
    
WKWebViewConfiguration *configuration = [[WKWebViewConfiguration alloc] init];
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    char *model = (char*)malloc(size);
    sysctlbyname("hw.machine", model, &size, NULL, 0);
    NSString *deviceModel = [NSString stringWithCString:model encoding:NSUTF8StringEncoding];
    free(model);
    NSString *scriptString = [NSString stringWithFormat:@"%@%@/%@", @"function __NJS_fireiOSEvent(str){window.webkit.messageHandlers.notification.postMessage(str);}; window.Nectar = {fireEvent:__NJS_fireiOSEvent, model:\"", deviceModel, @"\" };"];
    
    WKUserScript *script = [[WKUserScript alloc] initWithSource:scriptString injectionTime:WKUserScriptInjectionTimeAtDocumentEnd forMainFrameOnly:YES];
    WKUserContentController* userController = [[WKUserContentController alloc] init];
    [userController addUserScript:script];
    [userController addScriptMessageHandler:self name:@"notification"];
    configuration.userContentController = userController;

    self.webView = [[WKWebView alloc] initWithFrame:self.view.bounds configuration:configuration];
    [self.view addSubview:self.webView];

    self.webView.backgroundColor = [UIColor whiteColor];
    self.webView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
    webView.UIDelegate = self;
    webView.navigationDelegate = self;
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
