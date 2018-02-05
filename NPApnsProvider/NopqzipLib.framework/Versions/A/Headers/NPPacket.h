//
//  NPTCPPacket.h
//  NPTcpServer
//
//  Created by 樊航宇 on 15/3/3.
//  Copyright (c) 2015年 樊航宇. All rights reserved.
//

#import <Foundation/Foundation.h>


#define NP_FILLRESULT_NEEDMORE -1
#define NP_FILLRESULT_FAIL -2
#define NP_FILLRESULT_UNUSED -3

#define NP_HEADERLENGTH_FLEXIBLE -1
@class NPCache;

@interface NPPacket : NSObject
{
    @private
    NSMutableData *_contentData;
    NSMutableArray *_headers;
    NPCache *_cache;
    BOOL _filled;
    BOOL _headerFilled;
    BOOL _fillFailed;
}

-(instancetype)init;                            // override (optional)
-(BOOL)isFilled;
-(BOOL)isFillFailed;
-(NSData*)data;
-(NSUInteger)length;

//  Flexible Packet subclasses should override this method that return YES. otherwise ignore it or return NO;
+(BOOL) isFlexible;                             // override (Flexible)

// Refers to an empty object.
+(id)emptyObject;

+(BOOL)convertData:(NSData *)data ToNumber:(NSNumber* __autoreleasing*)number;

@end



@interface NPPacket (Headers)

-(NSData*)headerContent;
-(NSArray*)headers;
-(NSUInteger)headerLength;
-(NSUInteger)headerLengthFilled;

/**
   Return the entity's fields description.
   Fixed type should not override this method.
   Flexible type should ovrride this method and return a self-managed NSArray/NSMutableArray type that contains NSString. Nil pointer is not allowed so you have to at least allocate an empty array in init method and return it.
   The obj count of this returned Array must be the same with the return value of -headerFieldsLength.
 */
-(NSArray*)headerFieldsDescription;             // override(Flexible)


/*  XXX Not used...
 Return the entity's fields length.
 Fixed type should not override this method.
 Flexible type should ovrride this method and return a self-managed NSArray/NSMutableArray type that contains NSNumber.Nil pointer is not allowed so you have to at least allocate an empty array in init method and return it.
 The obj count of this returned Array must be the same with the return value of -headerFieldsDescription.
 */
//-(NSArray*)headerFieldsLength;

/**
 Return fields description of packets of this kind.
 Fixed type should override this method and return an array of NSString which would present each field's description sequencelly.
 Packet with no header should not override this method.
 Flexible types with ***flexible*** sequence of header fields should override this method and return a nil object;
 Flexible types with *****fixed**** sequence of header fields should override this method and return a self-managed NSArray/NSMutableArray type that contains NSString.
 The obj count of this returned Array must be the same with the return value of +headerFieldsLength.
 */
+(NSArray*)headerFieldsDescription;             // override

/**
 Return fields length of packets of this kind.
 Fixed type should override this method and return an array of NSNumber which would present each field's length sequencelly. If length of any field is variable, set an +emptyObject to the corresponding index of the returned array.
 Packet with no header should not override this method.
 Flexible types should ignore this method and manage length of header fields with its own -headerFieldsLength or setHeader:data: etc..
 The obj count of this returned Array must be the same with the return value of +headerFieldsLength.
 */
+(NSArray*)headerFieldsLength;                  // override (Fixed)

+(NSNumber *)getFieldLength:(NSString *)headerKey;
-(NSNumber *)getFieldLength:(NSString *)headerKey;



/** Header Length or FLEXIBLE */
+(NSInteger)headerLength;

-(NSData*) canSetData:(NSData *)headerData toField:(NSString *)headerKey;       // override

-(BOOL) setData:(NSData *)headerData toField:(NSString *)headerKey;             // override (optional)

-(BOOL) setChar:(UInt8)charData toField:(NSString *)headerKey;
-(BOOL) setShort:(UInt16)shortData toField:(NSString *)headerKey;
-(BOOL) setLong:(UInt32)longData toField:(NSString *)headerKey;
-(BOOL) setLongLong:(UInt64)longLongData toField:(NSString *)headerKey;
-(BOOL) setString:(NSString *)stringData toField:(NSString *)headerKey;

-(BOOL) setShort:(UInt16)shortData toField:(NSString *)headerKey byNetOrder:(BOOL)isNetOrder;
-(BOOL) setLong:(UInt32)longData toField:(NSString *)headerKey byNetOrder:(BOOL)isNetOrder;
-(BOOL) setLongLong:(UInt64)longLongData toField:(NSString *)headerKey byNetOrder:(BOOL)isNetOrder;

-(BOOL) setNumber:(UInt64)number toFiled:(NSString *)headerKey byNetOrder:(BOOL)isNetOrder;




/**
 Get Header Field's Data, if there is no data (include emptyObject), nil will be returned.
 */
-(NSData *) getHeaderFieldData:(NSString *)headerKey;

/**
 Get Header Filed's auctal Meaning. Subclasses should override this method. If no data (besides emptyObject), nil will be returned.
 */
-(id) getHeaderField:(NSString *)headerKey;                                 // override

-(BOOL) removeHeader:(NSString *)headerKey;



/**
 finalize headers. if succeed, no further modify of headers is permitted.
 */
-(BOOL) endHeaders;                                                         // override


-(BOOL) autoEndHeaders;                                                     // override

-(BOOL) isAllHeaderFieldFilled;

@end

@interface  NPPacket(Content)


-(void)fillContent:(NSData*)data;

-(BOOL)endPacket;                                                           // override



-(NSData*)content;

-(NSUInteger)contentLength;
-(NSUInteger)contentLengthFilled;

@end

@interface NPPacket(Tail)

/**
 If packet of this type has a tail, override this method. Your tail data should be a static one. otherwise set no tail and put your tail into content so that you can check that yourself.
 */
+(NSData *)tailData;                                                        // override

@end


@interface NPPacket(Parser)


/**
 Override this method if subclasses need to check the filling data at first (such as make sure when to end the packet...etc).
 */
-(NSInteger)tryFillPacketWithData:(NSData *)data;                           // override (optional)

/**
 Subclasses of whose header has fixed sequenced header fields but flexible length should override this method to write-back the actual length, otherwise no data would be written to that field, which is obviously unsafe.
 */

-(void)nextHeaderIs:(NSString **)refHeaderKey andLengthIs:(NSNumber **)refHeaderLength;  // override (flexible lengh of header field)

/**
 Subclasses should override this method to handle the content filling. If this method return a NP_FILLRESULT_NEEDMORE, all cached data would be written to content. If the return value is NP_FILLRESULT_UNUSED, the method is ingored. If both methods return NP_FILLRESULT_UNUSED, -tryFillPacketWithData would try ending packet filling after all cached data being written to content. If none of the method returns NP_FILLRESULT_UNUSED, method that returns a positive number is in used. If both method return a positive number but do not logically match (bytesLeft+contentLengthFilled!=contentLength), an assertion falure would be raised.
 */
-(NSInteger)contentLengthToFill;                                            // override
-(NSInteger)bytesLeftToFill;                                                // override


//-(BOOL)fieldHasBeenFilled:(NSString *)headerKey;
/*-(void)cacheDataPush:(NSData *)data;
-(NSData *)cacheDataPull:(NSUInteger)length;
-(NSData *)cacheDataPull;*/
-(NSData *)peekCachedData;

-(BOOL)tryEndPacket;                                                        // override

@end


@interface NPPacket(Flexible)

/*+(BOOL) canAddHeaderDescription;
+(BOOL) canModifyHeaderFieldLength;

-(BOOL) canAddHeaderField:(NSString *)field withData:(NSData *)data;*/

@end