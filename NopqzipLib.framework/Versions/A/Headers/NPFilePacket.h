//
//  NPFilePacket.h
//  NPTcpServer
//
//  Created by 樊航宇 on 15/3/9.
//  Copyright (c) 2015年 樊航宇. All rights reserved.
//

#import "NPPacket.h"

#define FPH_FILENAMELENGTH  @"Filename Length"
#define FPH_FILENAME        @"Filename"
#define FPH_CONTENTLENGTH   @"Content Length"


@interface NPFilePacket : NPPacket

-(BOOL)endPacket;

@end

@interface NPFilePacket(Headers)

+(NSArray*)headerFieldsDescription;
+(NSArray *)headerFieldsLength;

-(NSData *)canSetData:(NSData *)headerData toField:(NSString *)headerKey;
-(BOOL)endHeaders;
-(BOOL)autoEndHeaders;

-(id)getHeaderField:(NSString *)headerKey;

@end


@interface NPFilePacket(Parser)

-(NSInteger)contentLengthToFill;
-(BOOL)tryEndPacket;
-(void)nextHeaderIs:(NSString *__autoreleasing *)refHeaderKey andLengthIs:(NSNumber *__autoreleasing *)refHeaderLength;



@end