//
//  NPTCPServerClient.h
//  NPTcpServer
//
//  Created by 樊航宇 on 15/3/2.
//  Copyright (c) 2015年 樊航宇. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol NPStreamManagerDelegate;

@interface NPTCPServerClient : NSObject 

//@property (readonly) CFSocketRef cfSocket;

@property (readonly) NSInteger clientId;
@property (readonly) NSInteger port;
@property (readonly) NSString *clientIp;

-(void)sendData:(NSData *)data;
-(NSUInteger)bytesLeftToSend;

@end
