//
//  NPGernalPacket.h
//  NPTcpServer
//
//  Created by 樊航宇 on 15/3/4.
//  Copyright (c) 2015年 樊航宇. All rights reserved.
//

#import "NPPacket.h"

/*
 
 Genral Packet Format:
 | Foward code 0x1010 (2bytes) | Type (1 byte) | Content Length (4bytes Network) | HeaderChecksum (1 byte) | Content |
 
 
 */


#define GPH_FORWARD @"Forward"
#define GPH_TYPE    @"Type"
#define GPH_CONTENTLENGTH   @"Content Length"
#define GPH_HEADERCHECKSUM  @"Header Checksum"



@interface NPGeneralPacket : NPPacket

-(BOOL)endPacket;

@end

@interface NPGeneralPacket(Headers)

+(NSArray*)headerFieldsDescription;
+(NSArray *)headerFieldsLength;

-(NSData *)canSetData:(NSData *)headerData toField:(NSString *)headerKey;
-(BOOL)endHeaders;
-(BOOL)autoEndHeaders;

-(id)getHeaderField:(NSString *)headerKey;

@end


@interface NPGeneralPacket(Tail)

+(NSData *)tailData;

@end

@interface NPGeneralPacket(Parser)

-(NSInteger)contentLengthToFill;
-(NSInteger)bytesLeftToFill;
-(BOOL)tryEndPacket;



@end