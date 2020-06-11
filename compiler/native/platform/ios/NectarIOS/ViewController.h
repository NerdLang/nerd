//
//  ViewController.h
//  NectarIOS
//
//  Created by user175602 on 6/9/20.
//  Copyright © 2020 NectarJS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Webkit/Webkit.h>

@interface ViewController: UIViewController <WKScriptMessageHandler>;
@property (nonatomic, strong) IBOutlet WKWebView *webView;
@property (nonatomic, strong) IBOutlet UIView *view;
@property (nonatomic, strong) IBOutlet WKWebViewConfiguration *webConfig;
@end

