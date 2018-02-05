//
//  NPTCPServer.h
//  NPTcpServer
//
//  Created by 樊航宇 on 15/3/2.
//  Copyright (c) 2015年 樊航宇. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
#import <sys/socket.h>
#import <netinet/in.h>

@class NPTCPServerClient;
@class NPTCPServerEngine;

@class NPPacket;

@protocol NPServerDelegate <NSObject>

@optional
/**
 */
-(void)serverEngine:(NPTCPServerEngine *)serverEngine clientDidConnect:(NPTCPServerClient *)client;

/**
 */
-(void)serverEngine:(NPTCPServerEngine *)serverEngine clientDidDisconnect:(NPTCPServerClient *)client;

/**
 */
-(void)serverEngine:(NPTCPServerEngine *)serverEngine client:(NPTCPServerClient *)client isReceivingPacket:(NPPacket *)packet;

/**
 */
-(void)serverEngine:(NPTCPServerEngine *)serverEngine client:(NPTCPServerClient *)client didReceivePacket:(NPPacket *)packet;

/**
 */
-(BOOL)serverEngine:(NPTCPServerEngine *)serverEngine client:(NPTCPServerClient *)client shouldDisconnectWithErrorPacket:(NPPacket *)errorPacket;  //return YES to disconnect it.


@end

@interface NPTCPServerEngine : NSObject 

@property unsigned int port;
@property (weak) id<NPServerDelegate> delegate;


-(instancetype)init;
-(instancetype)initWithPort:(unsigned int)port;
+(instancetype)serverWithPort:(unsigned int)port;

-(BOOL)startListen;
-(void)stopListen;

-(void)disconnectClient:(NPTCPServerClient *)client;
-(void)disconnectAll;

-(void)sendPacket:(NPPacket *)packet toClient:(NPTCPServerClient *)client;
-(void)sendPacketToAll:(NPPacket *)packet;

-(BOOL)setPacketClass:(Class)pktClass;

-(NSArray *)connectedClients;

/**
 Returns a list of NSString(s) containing ip of server.
 */
+(NSArray *)serverIps;



//-(void)testDealloc;


@end
