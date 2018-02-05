//
//  NPGifCoder.h
//  NopqzipLib
//
//  Created by 樊航宇 on 15/4/23.
//  Copyright (c) 2015年 樊航宇. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NPGifCoder : NSObject

@property BOOL hasGlobeColorMap;
@property unsigned short height;
@property unsigned short width;

@property (readonly) NSData *data;

-(void)addCGImage:(CGImageRef)image origin:(CGPoint)origin duration:(NSTimeInterval)duration;

//-(NSData *)logicalScreenDescriptor;

@end
