//
//  APXPushNotification.h
//  AppoxeeSDK
//
//  Created by Raz Elkayam on 3/8/15.
//  Copyright (c) 2015 Appoxee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APXPushNotificationAction.h"

@interface APXPushNotification : NSObject

@property (nonatomic, strong, readonly) NSString *alert;
@property (nonatomic, readonly) NSInteger badge;
@property (nonatomic, readonly) NSInteger uniqueID;
@property (nonatomic, strong, readonly) NSDictionary *extraFields;
@property (nonatomic, readonly) BOOL didLaunchApp;
@property (nonatomic, readonly) BOOL isRich;
@property (nonatomic, readonly) BOOL isSilent;
@property (nonatomic, readonly) BOOL isTriggerUpdate;
@property (nonatomic, strong, readonly) APXPushNotificationAction *pushAction;

- (id)initWithKeyedValues:(NSDictionary *)keyedValues;

@end