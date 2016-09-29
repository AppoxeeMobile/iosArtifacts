//
//  AppoxeeMediaExtension.h
//  AppoxeeSDK
//
//  Created by Raz Elkayam on 9/14/16.
//  Copyright © 2016 Appoxee. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationContent;
@class UNNotificationRequest;

/**
 Initialize this class to provide out-of-the-box media attachments handling.
 Class instance will initiate the attachments download from a remote server, generating an attachment and attaching it to the push notification.
 */
@interface AppoxeeMediaExtension : NSObject

/**
 Initialize the Appoxee media attachment

 @param request        a UNNotificationRequest instance.
 @param contentHandler a completion handler for the media attachment.

 @return an AppoxeeMediaExtention instance.
 */
+ (nullable instancetype)mediaExtensionWithNotificationRequest:(nullable UNNotificationRequest *)request andContentHandler:(void (^ _Nullable)(UNNotificationContent * _Nonnull))contentHandler;

/**
 Forward the OS call to the instance, just before the extension is terminated by the system.
 */
- (void)serviceExtensionTimeWillExpire;

@end
