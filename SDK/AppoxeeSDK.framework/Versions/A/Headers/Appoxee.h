//
//  Appoxee.h
//  AppoxeeSDK
//
//  Created by Raz Elkayam on 16/12/2015.
//  Copyright © 2015 Appoxee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "APXPushNotification.h"
#import "APXRichMessage.h"
#import "APXClientDevice.h"

@class Appoxee;

typedef void(^AppoxeeCompletionHandler)(NSError * _Nullable appoxeeError, id _Nullable data);

@protocol AppoxeeNotificationDelegate <NSObject>

@optional
/**
 Delegate method for informing Push Notification handling by Appoxee SDK.
 @brief Method is called when a Push Notification is handled by Appoxee SDK.
 @param manager A singleton instance of Appoxee.
 @param pushNotificatoin An instance of APXPushNotification object which represents a Push Notification object.
 @param actionIdentifier An optional identifier, if the Push Notification has an ‘action’ associated with it, else value is nil.
 */
- (void)appoxee:(nonnull Appoxee *)appoxee handledRemoteNotification:(nonnull APXPushNotification *)pushNotification andIdentifer:(nonnull NSString *)actionIdentifier;

/**
 Delegate method for informing Rich Content handling by Appoxee SDK and was delivered with a Push Notification.
 @brief Method iscalled when Rich Content is handled by Appoxee SDK and is delivered with a Push Notification. @attention The developer should decide how to display the Rich Message content.
 @attention The developer should decide how to display the Rich Message content.
 @param manager A singleton instance of Appoxee.
 @param richMessage An instance of APXRichMessage object which represents Rich Content object.
 @param didLaunch A Boolean value indicating if the Rich Content was recieved while app was launched, due to a Push Notification.
 */
- (void)appoxee:(nonnull Appoxee *)appoxee handledRichContent:(nonnull APXRichMessage *)richMessage didLaunchApp:(BOOL)didLaunch;

@end

@interface Appoxee : NSObject

/*!
 * Between 1 - 5, where 1 prints all logs and 5 prints critical logs.
 */
@property (nonatomic) NSInteger logLevel;

/*!
 * Set to YES to postpone a request for notifications.
 * Setting the property should be performed prior to engaging the SDK.
 */
@property (nonatomic) BOOL postponeNotificationRequest;

/*!
 * Indicates if the device is registered at Appoxee (but not yet ready for push notifications). You can listen to ‘APX_Ready’ NSNotification to catch this event, or use KVO to get notified when state turns to YES.
 */
@property (nonatomic, readonly) BOOL isReady;

/*!
 * The Appoxee notification delegate.
 */
@property (nonatomic, weak, nullable) id <AppoxeeNotificationDelegate> delegate;

/*!
 * The user's DMC user ID.
 */
@property (nonatomic, strong, nullable, readonly) NSString *dmcUserID;

/*!
 * The DMC alias.
 */
@property (nonatomic, strong, nullable, readonly) NSString *dmcAlias;

#pragma mark - Appoxee Push Service

/**
 Appoxee instance
 @brief Method for gets a singleton instance of Appoxee.
 @code
 Appoxee *appoxee = [Appoxee shared];
 @endcode
 @return Appoxee an Instance Type of Appoxee.
 */
+ (nullable instancetype)shared;

/**
 Appoxee SDK version string.
 @brief Method to get the Appoxee SDK version string.
 @code
 NSString *sdkVersoin = [Appoxee sdkVersion];
 @endcode
 @return An NSString Object that represents an Appoxee SDK version.
 */
+ (nonnull NSString *)sdkVersion;

/**
 Method auto integrate and engage with Appoxee SDK.
 @brief Call this method to perform auto integration of your AppDelegate file, and to engage with Appoxee SDK.
 @attention Provide an AppoxeeConfiguration.plist in your application. Method is considered critical, and must be implemented.
 @code
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
    // Method takes into consideration a valid AppoxeeConfig.plist file in your application.
    [[Appoxee shared] engageAndAutoIntegrateWithLaunchOptions:launchOptions andDelegate:nil];
    return YES;
 }
 @endcode
 @param launchOptions NSDictionary which contains the launchOptions of didFinishLaunchingWithOptions AppDelegate method.
 @param delegate An object which conforms to AppoxeeDelegate Protocol.
 */
- (void)engageAndAutoIntegrateWithLaunchOptions:(nullable NSDictionary *)launchOptions andDelegate:(nullable id<AppoxeeNotificationDelegate>)delegate;

/**
 Method for engaging Appoxee SDK.
 @brief Call this method to engage Appoxee SDK in your application. 
 @attention Method is considered critical, and must be implemented.
 @code
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
    [[Appoxee shared] engageWithLaunchOptions:launchOptions andDelegate:self andSDKID:@"123"];
    return YES;
 }
 @endcode
 @param launchOptions NSDictionary which contains the launchOptions of didFinishLaunchingWithOptions AppDelegate method.
 @param delegate An object which conforms to AppoxeeDelegate Protocol.
 @param sdkID NSString representation of the SDK ID.
 */
- (void)engageWithLaunchOptions:(nullable NSDictionary *)launchOptions andDelegate:(nullable id<AppoxeeNotificationDelegate>)delegate andSDKID:(nonnull NSString *)sdkID;

/**
 Method for notifing Appoxee registration for Push Notifications was succesful.
 @brief Notify Appoxee on a successful registration of APNS. 
 @attention method is considered critical and must be implemented. If engageAndAutoIntegrateWithLaunchOptions:andDelegate:andSDKID or engageAndAutoIntegrateWithLaunchOptions:andDelegate: is used, implementation is optional.
 @code
 - (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
 {
    [[Appoxee shared] didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
 }
 @endcode
 @param token NSData representation of Apple generated Push Token.
 */
- (void)didRegisterForRemoteNotificationsWithDeviceToken:(nullable NSData *)token;

/**
 Method for notifing Appoxee on registration progress.
 @brief Appoxee on registration progress. 
 @attention method is considered critical and must be implemented. If engageAndAutoIntegrateWithLaunchOptions:andDelegate:andSDKID: or engageAndAutoIntegrateWithLaunchOptions:andDelegate: is used, implementation is optional.
 @code
 - (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
 {
    [[Appoxee shared] didRegisterUserNotificationSettings:notificationSettings];
 }
 @endcode
 @param notificationSettings UIUserNotificationSettings instance.
 */
- (void)didRegisterUserNotificationSettings:(nullable UIUserNotificationSettings *)notificationSettings;

#pragma mark - Push Handling

/**
 Method for notifing Appoxee a remote Push Notification was received to the device.
 @brief Use this method to pass information to Appoxee Manager regarding incoming push notifications. 
 @attention method is considered critical and must be implemented. If engageAndAutoIntegrateWithLaunchOptions:andDelegate:andSDKID: or engageAndAutoIntegrateWithLaunchOptions:andDelegate: is used, implementation is optional.
 @code
 - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
 {
    [[Appoxee shared] receivedRemoteNotification:userInfo];
 }
 @endcode
 @param userInfo NSDictionary object containing user info with Push payload.
 */
- (void)receivedRemoteNotification:(nullable NSDictionary *)userInfo;

/**
 Method for handling 'Push Actions'. Forward this call to Appoxee directly and call completionHandler(); if the returned value is NO, since Appoxee will not handle a complete custom action provided by the developer.
 @brief Implementation of this method enables ‘Push Actions’. Forward this call to Appoxee directly and call completionHandler(); if the returned value is NO, since Appoxee will not handle a complete custom action provided by the developer. 
 @attention If engageAndAutoIntegrateWithLaunchOptions:andDelegate:andSDKID: or engageAndAutoIntegrateWithLaunchOptions:andDelegate: is used, implementation is optional.
 @code
 - (void)application:(UIApplication *)application handleActionWithIdentifier:(NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo completionHandler:(void (^)())completionHandler
 {
    [[Appoxee shared] handleActionWithIdentifier:identifier forRemoteNotification:userInfo completionHandler:completionHandler];
 }
 @endcode
 @param identifier The identifier argument passed by the application delegate.
 @param userInfo The userInfo argument passed by the application delegate.
 @param completionHandler The completionHandler argument passed by the application delegate.
 @return YES, if Appoxee handled the action, else returns NO. If the returned value is NO, you will need to call completionHandler(); after you finish handling the Push action.
 */
- (BOOL)handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(nullable NSDictionary *)userInfo completionHandler:(nonnull void (^)())completionHandler;

/*
 
 Application's plist must contain a 'remote-notification' value in 'UIBackgroundModes'.
 
 */
/**
 Method for enabling Appoxee to fetch new data while in background. If completionHandler is nil, Appoxee assumes the developer also has work to perform, and by this Appoxee will NOT call the completionHandler, but it will provide a UIBackgroundFetchResult as an NSNumber argument in the AppoxeeCompletionHandler block. Application's plist must contain a 'remote-notification' value in 'UIBackgroundModes'.
 @brief Implementation of this method enables Appoxee to fetch new data, or update a geo location, while in background. If completionHandler is nil, Appoxee assumes the developer also has work to perform, and by this Appoxee will NOT call the completionHandler, but it will provide a UIBackgroundFetchResult as an NSNumber argument in the AppoxeeCompletionHandler block. Application’s plist must contain a ‘remote-notification’ value in ‘UIBackgroundModes’. 
 @attention If engageAndAutoIntegrateWithLaunchOptions:andDelegate:andSDKID: or engageAndAutoIntegrateWithLaunchOptions:andDelegate: is used, implementation is optional.
 @code
 // 1. 
 // Handling a silent push which did not originate at Appoxee. 
 - (void)application:(UIApplication )application didReceiveRemoteNotification:(NSDictionary )userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler 
 { 
    // passing completionHandler for the completionHandler argument, so that Appoxee calls it when Appoxee is done. 
    [[Appoxee shared] didReceiveRemoteNotification:userInfo fetchCompletionHandler:completionHandler andNotifyCompletionWithBlock:^(NSError * Nullable appoxeeError, id Nullable data) {
    
        if (appoxeeError) {
 
             // This means that the silent push did not originate from Appoxee. The data param will contain a UIBackgroundFetchResultFailed as an NSNumber.
             // Appoxee will not perform any action, and it is the developer's responsibility to call the completionHandler();.
            completionHandler(UIBackgroundFetchResultFailed); // provide an UIBackgroundFetchResult by your own app-specific logic.
 
        } else {
 
            // No need to pefrom any action, since Appoxee will call completionHandler() providing it a UIBackgroundFetchResult.
 
        }
    }];
 }
 // 2. 
 // Handling the completion handler by the developer 
 - (void)application:(UIApplication )application didReceiveRemoteNotification:(NSDictionary )userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler 
 { 
    // passing nil for the completionHandler argument, so that the developer can also perform it’s work. 
    [[Appoxee shared] didReceiveRemoteNotification:userInfo fetchCompletionHandler:nil andNotifyCompletionWithBlock:^(NSError * Nullable appoxeeError, id Nullable data) {
 
        if (appoxeeError) {
 
             // This means that the silent push did not originate from Appoxee. The data param will contain a UIBackgroundFetchResultFailed as an NSNumber.
             // Appoxee will not perform any action, and it is the developer's responsibility to call the completionHandler();.
 
             // add Developer operations logic, and call:
             completionHandler(UIBackgroundFetchResultNewData); // provide an UIBackgroundFetchResult by your own app-specific logic.
 
         } else {
 
             // add Developer operations logic, and call:
             completionHandler(UIBackgroundFetchResultNewData); // provide an UIBackgroundFetchResult by your own app-specific logic.
         }
     }];
 }
 @endcode
 @param userInfo NSDictionary object containing user info with Push payload.
 @param completionHandler The OS completion handler block. Must be called (by Appoxee / by developer) when work is completed. if param is nil, the developer will need to call it on he's own. If provided, Appoxee will call it when it completes its work, unless the silent-push did not originate at Appoxee. It is advised to wait for the completionBlock parameters, and act according to their data.
 @param completionBlock A completion block which will be called when Appoxee completes it's work, enabling the developer to call completionHandler, in case fetchHandler is nil.
 */
- (void)didReceiveRemoteNotification:(nullable NSDictionary *)userInfo fetchCompletionHandler:(nullable void (^)(UIBackgroundFetchResult))completionHandler andNotifyCompletionWithBlock:(nullable AppoxeeCompletionHandler)completionBlock;

#pragma mark - Background fetch

/**
 Method for enabling Appoxee to fetch new data while in background. If fetchHandler is nil, Appoxee assumes the developer also has work to perform, and by this Appoxee will NOT call the fetchHandler, but it will provide a UIBackgroundFetchResult as an NSNumber argument in the AppoxeeCompletionHandler block. Application's plist must contain a 'fetch' value in 'UIBackgroundModes'.
 @brief Implementation of this method enables Appoxee to fetch new data, or update a geo location, while in background. If fetchHandler is nil, Appoxee assumes the developer also has work to perform, and by this Appoxee will NOT call the fetchHandler, but it will provide a UIBackgroundFetchResult as an NSNumber argument in the AppoxeeCompletionHandler block. Application’s plist must contain a ‘fetch’ value in ‘UIBackgroundModes’. 
 @attention If engageAndAutoIntegrateWithLaunchOptions:andDelegate:andSDKID: or engageAndAutoIntegrateWithLaunchOptions:andDelegate: is used, implementation is optional.
 @code
// 1.
// In case the developer needs to perform work. 
- (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler 
{

    [[Appoxee shared] performFetchWithCompletionHandler:nil andNotifyCompletionWithBlock:^(NSError * Nullable appoxeeError, id Nullable data) {

        if ([data isKindOfClass:[NSNumber class]]) {

            // Fetch the background resualt provided by Appoxee, notifying if Appoxee did fetch new data, or did not.
            NSNumber *backgroundFetchResult = (NSNumber *)data;

            // Call the completion handler, when you finish your work.
            completionHandler([backgroundFetchResult integerValue]);
        }
    }];
}
// 2. 
// In case the developer does not need to perform work. 
- (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler 
{ 
    // Appoxee will call completionHandler(); with a UIBackgroundFetchResult when it will finish it’s work.
    [[Appoxee shared] performFetchWithCompletionHandler:completionHandler andNotifyCompletionWithBlock:nil];
} 
 @endcode
 @param fetchHandler The OS fetch handler block. must be called (by Appoxee / by developer) when work is completed. if nil, the developer will need to call it, while waiting for Appoxee's completionBlock. If provided, then Appoxee will call the fetchHandler when done.
 @param completionBlock A completion block which will be called when Appoxee completes it's work, enabling the developer to be notified, in case fetchHandler is nil, and to call the fetchHandler.
 */
- (void)performFetchWithCompletionHandler:(nullable void (^)(UIBackgroundFetchResult))fetchHandler andNotifyCompletionWithBlock:(nullable AppoxeeCompletionHandler)completionBlock;

#pragma mark - Device API

/**
 Disable and re-enable Push Notifications.
 @brief Method will disable or re-enable Push Notification per device at Appoxee Dashboard. 
 @attention Method does not un-register from push notifications, but rather, it opts-out the device from Push Services at Appoxee Dashboard.
 @code
 [[Appoxee shared] disablePushNotifications:booleanArgument withCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        // operation was successful.
    }
 }];
 @endcode
 @param isDisabled BOOL value indacating if should enable or disable push.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)disablePushNotifications:(BOOL)isDisabled withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Get the current state of the push from Appoxee dashboard.
 @brief Method to get the state value of the push status from Appoxee Dashboard. 
 @attention Method indicates if a device is push-enabled at Appoxee dashboard, and not if a device is registered for APNS.
 @code
 [[Appoxee shared] isPushEnabled:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        BOOL state = [(NSNumber *)data boolValue];
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)isPushEnabled:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Disable and re-enable Inbox.
 @brief Method disables or re-enables Inbox. 
 @attention Standalone Feature. Method does not un-register sound from push notifications, but opts-out the device sound from Push Services at Appoxee dashboard.
 @code
 [[Appoxee shared] disableInbox:booleanArgument completionHwithCompletionHandlerandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        // operation was successful.
    }
 }];
 @endcode
 @param isDisabled BOOL value indacating if should enable or disable sound.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)disableInbox:(BOOL)isDisabled withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Get the current state of the Inbox.
 @brief Method to get the current state of Inbox. 
 @attention Standalone Feature. Method fetches opt-out status of the device inbox from Push Services at Appoxee dashboard.
 @code
 [[Appoxee shared] isInboxEnabled:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        BOOL state = [(NSNumber *)data boolValue];
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)isInboxEnabled:(nullable AppoxeeCompletionHandler)handler;

#pragma mark - Alias

/**
 Set an alias to be identifies with a device.
 @brief Method sets an alias to identify a device.
 @code
 [[Appoxee shared] setDeviceAlias:@"Alias" withCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        // Alias was set.
    }
 }];
 @endcode
 @param alias An NSString object representing an alias.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)setDeviceAlias:(nullable NSString *)alias withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Remove an alias from a device.
 @brief Method removes an alias from a device.
 @code
 [[Appoxee shared] removeDeviceAliasWithCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        // Alias was removed.
    }
 }];
 @endcode
 An NSString object representing an alias.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)removeDeviceAliasWithCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Get an alias for a device.
 @brief Method gets the alias for a device.
 @code
 [[Appoxee shared] getDeviceAliasWithCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError && [data isKindOfClass:[NSString class]]) {
 
        NSString *deviceAlias = (NSString *)data;
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)getDeviceAliasWithCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Clear cached value of an alias.
 @brief Method clears cached value of an alias.
 @code
 [[Appoxee shared] clearAliasCacheWithCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        // Alias cache was cleared.
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)clearAliasCacheWithCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

#pragma mark - Device Tags

/**
 Standalone Feature
 Get the device tags from Appoxee's servers
 @brief Method gets the device tags from the Appoxee servers.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] fetchDeviceTags:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError && [data isKindOfClass:[NSArray class]]) {
 
        NSArray *deviceTags = (NSArray *)data;
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)fetchDeviceTags:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Get the application tags from Appoxee's servers
 @brief Method gets the appilcation tags from the Appoxee servers.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] fetchApplicationTags:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError && [data isKindOfClass:[NSArray class]]) {
 
        NSArray *applicationTags = (NSArray *)data;
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)fetchApplicationTags:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Add Tags to a device.
 @brief Method adds tags to a device. Method may return in the callback an error with APX_DataService domain value. This means that the operation was successfully completed, but with errors. The errors indicate if the operation triggered a server update. Operations such as adding an existing device tag, or passing an empty array, will trigger such APX_DataService errors. Any other error with a different domain indicates an unsuccessful operation.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] addTagsToDevice:@[@"firstTag", @"secondTag"] withCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (appoxeeError) {
 
        // check the error domain
    }
 }];
 @endcode
 @param tagsToAdd NSArray containing a list of NSString tags.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)addTagsToDevice:(nullable NSArray <NSString *> *)tagsToAdd withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Remove Tags from a device.
 @brief Method removes tags from a device. Method may return in the callback an error with APX_DataService domain value. This means that the operation was successfully completed, but with errors. The errors indicate if the operation triggered a server update. Operations such as adding an existing device tag, or passing an empty array, will trigger such APX_DataService errors. Any other error with a different domain indicates an unsuccessful operation.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] removeTagsFromDevice:@[@"firstTag", @"secondTag"] withCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (appoxeeError) {
 
        // check the error domain
    }
 }];
 @endcode
 @param tagsToRemove NSArray containing a list of NSString tags.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)removeTagsFromDevice:(nullable NSArray <NSString *> *)tagsToRemove withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Add Tags to a device and remove tags from a device.
 @brief Method adds tags to a device and removes tags from a device. Method may return in the callback an error with APX_DataService domain value. This means that the operation was successfully completed, but with errors. The errors indicate if the operation triggered a server update. Operations such as adding an existing device tag, or passing an empty array, will trigger such APX_DataService errors. Any other error with a different domain indicates an unsuccessful operation.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] addTagsToDevice:@[@"firstTag", @"secondTag"] andRemove:@[@"thirdTag", @"fourthTag"]  withCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (appoxeeError) {
 
        // check the error domain
    }
 }];
 @endcode
 @param tagsToAdd NSArray containing a list of NSString tags.
 @param tagsToRemove NSArray containing a list of NSString tags.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)addTagsToDevice:(nullable NSArray <NSString *> *)tagsToAdd andRemove:(nullable NSArray <NSString *> *)tagsToRemove withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Clear device tags cached on device.
 @brief Method will clear the device tags cache.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] clearTagsCacheWithCompletionhandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        // operation is successful
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)clearTagsCacheWithCompletionhandler:(nullable AppoxeeCompletionHandler)handler;

#pragma mark - Custom Fields

/**
 Set a custom date for a key to Appoxee Servers.
 @brief Method sets a custom value of NDSate to Appoxee Servers.
 @code
 [[Appoxee shared] setDateValue:[NSDate date] forKey:@"key" withCompletionHandler:^(NSError * _Nullable appoxeeError, id  _Nullable data) {
 
    if (!appoxeeError) {
 
        // Operation was successful.
    }
 }];
 @endcode
 @param date an NSDate instance representing a date.
 @param key an NSString instance representing a key.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)setDateValue:(nonnull NSDate *)date forKey:(nonnull NSString *)key withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Set a custom number for a key to Appoxee Servers.
 @brief Method sets a custom value of NSNumber to Appoxee Servers.
 @code
 [[Appoxee shared] setNumberValue:@(1.01) forKey:@"key" withCompletionHandler:^(NSError * _Nullable appoxeeError, id  _Nullable data) {
 
    if (!appoxeeError) {
 
        // Operation was successful.
    }
 }];
 @endcode
 @param number an NSNumber instance representing a number.
 @param key an NSString instance representing a key.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)setNumberValue:(nonnull NSNumber *)number forKey:(nonnull NSString *)key withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Increment a custom number for a key to Appoxee Servers.
 @brief Method increments a custom value of NSNumber to Appoxee Servers. Value is added to an existing key, or else a new entry is created.
 @attantion If key doesn't exist, a new key and value will be set.
 @code
 [[Appoxee shared] incrementNumericKey:@"key" byNumericValue:@(1.6) withCompletionHandler:^(NSError * _Nullable appoxeeError, id  _Nullable data) {
 
    if (!appoxeeError) {
 
        // Operation was successful.
    }
 }];
 @endcode
 @param key an NSString instance representing a key.
 @param number an NSNumber instance representing a number.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)incrementNumericKey:(nonnull NSString *)key byNumericValue:(nonnull NSNumber *)number withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Set a custom string for a key to Appoxee Servers.
 @brief Method sets a custom value of NSString to Appoxee Servers.
 @code
 [[Appoxee shared] setStringValue:@"string" forKey:@"key" withCompletionHandler:^(NSError * _Nullable appoxeeError, id  _Nullable data) {
 
    if (!appoxeeError) {
 
        // Operation was successful.
    }
 }];
 @endcode
 @param string NSString instance representing a string.
 @param key an NSString instance representing a key.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)setStringValue:(nonnull NSString *)string forKey:(nonnull NSString *)key withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Get a key-value pair stored in cache.
 @brief Method gets a key-value pair stored on the device.
 @code
 [[Appoxee shared] fetchCustomFieldByKey:@"CustomFieldKey" withCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError && [data isKindOfClass:[NSDictionary class]]) {
 
        NSDictionary *dictionary = (NSDictionary *)data;
        NSString *key = [[dictionary allKeys] firstObject];
        id value = dictionary[key]; // can be of the following types: NSString || NSNumber || NSDate
    }
 
    // If there wan't an error, and data object is nil, then value doesn't exist on the device.
 }];
 @endcode
 @param key NSString with the key of a previously saved key-value pair.
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)fetchCustomFieldByKey:(nullable NSString *)key withCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Clear cached value of custom fields.
 @brief Method clears cached value of custom fields.
 @code
 [[Appoxee shared] clearCustomFieldsCacheWithCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        // custom fields cache was cleared.
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)clearCustomFieldsCacheWithCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

#pragma mark - Device Info

/**
 Get information on the current iDevice.
 @brief Method gets information on the current iDevice.
 @code
    // Note that calling this method prior to device registration will provide basic information regarding this device.
    // Developers should prefare using deviceInformationwithCompletionHandler:
    APXClientDevice *device = [[Appoxee shared] deviceInfo];
 @endcode
 @param APXClientDevice an instance that describes this device.
 */
- (nonnull APXClientDevice *)deviceInfo;

/**
 Get information on the current iDevice.
 @brief Method gets information on the current iDevice.
 @code
 [[Appoxee shared] deviceInformationwithCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError && [data isKindOfClass:[APXClientDevice class]]) {
 
        APXClientDevice *device = (APXClientDevice *)data;
    }
  }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)deviceInformationwithCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

#pragma mark - Inbox API

/**
 Standalone Feature
 Inbox API for getting Inbox Messages.
 @brief Method for getting all of the Rich messages associated with a device.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] getRichMessagesWithHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        NSArray *messages = (NSArray *)data; // all objects in array are of type APXRichMessage
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)getRichMessagesWithHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Inbox API for deleting a Rich Message.
 @brief Method that deletes a Rich Message from Inbox.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] deleteRichMessage:richMessage withHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        // refresh UI
    }
 }];
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)deleteRichMessage:(nullable APXRichMessage *)richMessage withHandler:(nullable AppoxeeCompletionHandler)handler;

/**
 Standalone Feature
 Refresh Inbox Messages while syncing with Appoxee Servers.
 @brief Method refreshes Inbox Rich Messages while synching data with Appoxee Servers.
 @attention Standalone Feature.
 @code
 [[Appoxee shared] refreshInboxWithCompletionHandler:^(NSError *appoxeeError, id data) {
 
    if (!appoxeeError) {
 
        NSArray *messages = (NSArray *)data; // all objects in array are of type APXRichMessage
    }
 }];
 @endcode
 @param handler Code Block to be executed when method completes with an NSError object and data as arguments.
 */
- (void)refreshInboxWithCompletionHandler:(nullable AppoxeeCompletionHandler)handler;

@end
