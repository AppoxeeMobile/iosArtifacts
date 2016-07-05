//
//  AppDelegate.m
//  DemoApplication
//
//  Created by Raz Elkayam on 6/4/15.
//  Copyright (c) 2015 Teradata. All rights reserved.
//

#import "AppDelegate.h"
#import <AppoxeeSDK/AppoxeeSDK.h>
#import "APXRichContentViewController.h"

@interface AppDelegate () <AppoxeeDelegate>

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [[Appoxee shared] engageWithLaunchOptions:launchOptions andDelegate:self andSDKID:nil andAppSecret:nil];
    
    return YES;
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    [[Appoxee shared] didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    [[Appoxee shared] receivedRemoteNotification:userInfo];
}

- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
{
    [[Appoxee shared] didRegisterUserNotificationSettings:notificationSettings];
}

- (void)application:(UIApplication *)application handleActionWithIdentifier:(NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo completionHandler:(void (^)())completionHandler
{
    // Must be implemented in order to enable 'Push Actions'.
    BOOL didHandle = [[Appoxee shared] handleActionWithIdentifier:identifier forRemoteNotification:userInfo completionHandler:completionHandler];
    
    if (!didHandle) { completionHandler(); } // Handle the action in case it is not handled by Appoxee. When done - completionHandler() must be called.
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    BOOL handling = NO;
    
    if ([sourceApplication isEqualToString:@"AppoxeeSDK"]) {
        
        /*
         Appoxee SDK will automatically try to handle all annotations. return 'NO' to indicate the AppoxeeManager should handle the url, or 'YES' for taking over control.
         Possible annotations from Appoxee: @"APXURL_scheme", @"APXWeb_Site", @"APXApp_Store", @"APXView_Controller"
         */
        
        if ([annotation isEqualToString:@"APXURL_scheme"]) {
            
            /*
             We will demonstrate handling 'url scheme' (a.k.a Deep Linking), by saving the values passed, and segueing to a view controller from our 'main view controller', which will display the content of the scheme.
             We will take control from AppoxeeManager, and start a process which will display a the givven URL scheme in a View Controller.
             */
            
            handling = YES;
            
            [[NSUserDefaults standardUserDefaults] setObject:[url description] forKey:@"urlScheme"];
            [[NSUserDefaults standardUserDefaults] synchronize];
            [[NSNotificationCenter defaultCenter] postNotificationName:@"urlScheme" object:nil];
            
        } else {
            
            handling = NO; // We will let AppoxeeManager to handle the redirection for us.
        }
    }
    
    return handling;
}

#pragma mark - AppoxeeDelegate

- (void)appoxeeManager:(AppoxeeManager *)manager handledRemoteNotification:(APXPushNotification *)pushNotification andIdentifer:(NSString *)actionIdentifier
{
    // a push notification was recieved.
}

- (void)appoxeeManager:(AppoxeeManager *)manager handledRichContent:(APXRichMessage *)richMessage didLaunchApp:(BOOL)didLaunch
{
    if (didLaunch) {
        
        // If a Rich Message launched the app, we will display its content.
        
        UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        
        APXRichContentViewController *richContent = [storyboard instantiateViewControllerWithIdentifier:@"APXRichContentViewController"];
        [richContent setHtml:richMessage.messageLink];
        
        [self.window.rootViewController presentViewController:richContent animated:NO completion:nil];
    }
}

@end
