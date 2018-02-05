//
//  NPStreamManager.h
//  NPTcpServer
//
//  Created by 樊航宇 on 15/3/11.
//  Copyright (c) 2015年 樊航宇. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NPStreamManager;

@protocol NPStreamManagerDelegate <NSObject>
@optional

-(BOOL)streamManagerShouldOpen:(NPStreamManager *)streamManager;
-(void)streamManagerDidConnect:(NPStreamManager *)streamManager;
//-(void)isReceivingPacket:(NPPacket *)packet;
-(void)streamManager:(NPStreamManager *)streamManager didReceiveData:(NSData *)data;
//-(BOOL)didReceiveErrorPacket;
-(void)streamManagerDidDisconnect:(NPStreamManager *)streamManager;
-(void)streamManagerCanSendData:(NPStreamManager *)streamManager;
@end

@interface NPStreamManager : NSObject <NSStreamDelegate>

@property (weak) id<NPStreamManagerDelegate> delegate;
@property (weak) NSThread *selfManageThread;
@property NSTimeInterval connectTimeOut;
@property (readonly, nonatomic) NSInputStream *inputStream;
@property (readonly, nonatomic) NSOutputStream *outputStream;

//@property BOOL tls;

//-(instancetype)initWithNativeSocket:(CFSocketNativeHandle) nativeSocket;
-(instancetype)initWithInputStream:(NSInputStream *)inputStream andOutputStream:(NSOutputStream *)outputStream;

-(BOOL)connectTo:(NSString *)domain withPort:(UInt16)port;
-(BOOL)connectWithNativeSocket:(CFSocketNativeHandle)nativeSocket;
-(void)connectWithInputStream:(NSInputStream *)inputStream andOutputStream:(NSOutputStream *)outputStream;

-(void)disconnect;
-(void)sendData:(NSData *)data;

-(BOOL)isConnectedOrConnecting;

-(NSUInteger)bytesLeftToSend;
-(void) getIpAddress:(NSString *__autoreleasing *)ipAddress andPort:(UInt16 *)port;

-(void)scheduleStreamInRunloop;

-(void)setStreamProperty:(id)property forKey:(NSString *)key;



@end
