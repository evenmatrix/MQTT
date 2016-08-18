//
//  MQTTSessionManager.h
//  MQTTClient
//
//  Created by Christoph Krey on 09.07.14.
//  Copyright (c) 2013-2015 Christoph Krey. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "MQTTSession.h"

FOUNDATION_EXTERN NSString *const  MQTTSessionConnectedNotification;

@class MQTTSessionManager;
@protocol MQTTSessionManagerDelegate <NSObject>
- (void)handleMessage:(NSData *)data onTopic:(NSString *)topic retained:(BOOL)retained;
- (MQTTMessage *)sessionManager:(MQTTSessionManager*)manager connectMessageWithSession:(MQTTSession *)session;
@end

@interface MQTTSessionManager : NSObject <MQTTSessionDelegate>

typedef NS_ENUM(int, MQTTSessionManagerState) {
    MQTTSessionManagerStateStarting,
    MQTTSessionManagerStateConnecting,
    MQTTSessionManagerStateError,
    MQTTSessionManagerStateConnected,
    MQTTSessionManagerStateClosing,
    MQTTSessionManagerStateClosed
};

@property (weak, nonatomic) id<MQTTSessionManagerDelegate> delegate;
@property (strong, nonatomic) NSMutableDictionary *subscriptions;

@property (nonatomic, readonly) MQTTSessionManagerState state;
@property (nonatomic, readonly) NSError *lastErrorCode;

- (void)connectTo:(NSString *)host
             port:(NSInteger)port
              tls:(BOOL)tls
        keepalive:(NSInteger)keepalive
            clean:(BOOL)clean
             auth:(BOOL)auth
             user:(NSString *)user
             pass:(NSString *)pass
        willTopic:(NSString *)willTopic
             will:(NSData *)will
          willQos:(MQTTQosLevel)willQos
   willRetainFlag:(BOOL)willRetainFlag
     withClientId:(NSString *)clientId;

//
-(void)connectTo:(NSString *)host
            port:(NSInteger)port
       keepalive:(NSInteger)keepalive
            user:(NSString*)user
            pass:(NSString*)pass
           clean:(BOOL)clean withClientId:(NSString *)clientId;

- (void)connectToLast;
- (UInt16)sendData:(NSData *)data topic:(NSString *)topic qos:(MQTTQosLevel)qos retain:(BOOL)retainFlag;
- (void)disconnect;
- (void)closeAndCleanConnected;
@end
