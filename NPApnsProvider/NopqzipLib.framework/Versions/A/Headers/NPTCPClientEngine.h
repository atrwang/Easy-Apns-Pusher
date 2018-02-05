//
//  NPTCPClient.h
//  NPTcpServer
//
//  Created by 樊航宇 on 15/3/2.
//  Copyright (c) 2015年 樊航宇. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NPStreamManager.h"
@class NPPacket;
@class NPTCPClientEngine;

@protocol NPClientDelegate <NSObject>

@optional
/**
 */
-(void)clientEngineDidConnectToServer:(NPTCPClientEngine *)clientEngine;

/**
 */
-(void)clientEngine:(NPTCPClientEngine *)clientEngine isReceivingPacket:(NPPacket *)packet;

/**
 */
-(void)clientEngine:(NPTCPClientEngine *)clientEngine didReceivePacket:(NPPacket *)packet;

/**
 */
-(void)clientEngine:(NPTCPClientEngine *)clientEngine didReceiveData:(NSData *)data;

/**
 */
-(BOOL)clientEngine:(NPTCPClientEngine *)clientEngine didReceiveErrorPacket:(NPPacket *)packet;

/**
 */
-(void)clientEngineDidDisconnect:(NPTCPClientEngine *)clientEngine;


@end

@interface NPTCPClientEngine : NSObject <NPStreamManagerDelegate>

/**
 Property that indecates the server's listening port 
 */
@property UInt16 serverPort;

/** Property that indecates the server's domain name */
@property NSString *serverDomain;

/** Sets or returns the receiver's delegate */
@property (weak) id<NPClientDelegate> delegate;

@property (readonly,getter=isConnected) BOOL connected;

/*@property NSString* streamType;

@property BOOL serverTLS;*/

-(instancetype)init;
-(instancetype)initWithPort:(UInt16)port andDomain:(NSString *)domain;

/**
 Sets the packet type the client engine would receive. Class type must be a NPPacket class or its subclasses.
 If no class is set, delegate method of didReceivePacket and isReceivingPacket would not be called.
 */
-(BOOL)setPacketType:(Class)packetClass;

/**
 Connects to server.
 If the method succeed, the return value is YES otherwise NO.
 You should not use the return value to justify whether the client is connected to server. The correct way is to implement the delegate method called didConnect/didDisconnect to ensure the connection.
 */
-(BOOL)connect;

/**
 Disconnects to server.
 */
-(void)disconnect;

/**
 Sends Data to server.
 */
-(void)sendData:(NSData *)data;

/**
 Sends a packet to server. The packet should be a type of NPPacket or its subclass.
 */
-(void)sendPacket:(NPPacket *)packet;

/**
 Returns the sending caches length.
 */
-(NSUInteger)bytesLeftToSend;

/**
 Returns the server's Ip address.
 */
-(NSString *)getServerIp;



@end
