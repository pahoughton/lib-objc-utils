//
//  SMKLogger.h
//  Dig-It
//
//  Created by Paul Houghton on 1/29/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

// FIXME - change SMK Log Error to support raising exceptions. ( a stacktrace would be nice );

#import <Foundation/Foundation.h>

@interface SMKLogger : NSObject
enum LogLevel {
    SMK_LOG_DEBUG,
    SMK_LOG_INFO,
    SMK_LOG_WARN,
    SMK_LOG_ERROR
};

+(NSString *)userDefaultDateFormatKey;

-(void)logIt:(enum LogLevel)lvl 
         src:(const char *)srcFn 
        line:(int)srcLine
         fmt:(NSString *)msgFmt
   arguments:(va_list)args NS_FORMAT_FUNCTION(4,0);

-(void)logIt:(enum LogLevel)lvl 
         src:(const char *)srcFn 
        line:(int)srcLine
         fmt:(NSString *)msgFmt, ... NS_FORMAT_FUNCTION(4,5);

+(void)logIt:(enum LogLevel)lvl 
         src:(const char *)srcFn 
        line:(int)srcLine
         fmt:(NSString *)msgFmt, ... NS_FORMAT_FUNCTION(4,5);

@end

#define SMKLogDebug(fmt_,...) [SMKLogger logIt:SMK_LOG_DEBUG         \
                                           src:__FILE__              \
                                          line:__LINE__              \
                                           fmt:fmt_, ##__VA_ARGS__ ] \

#define SMKLogInfo(fmt_,...) [SMKLogger logIt:SMK_LOG_INFO         \
src:__FILE__              \
line:__LINE__              \
fmt:fmt_, ##__VA_ARGS__ ] \

#define SMKLogWarn(fmt_,...) [SMKLogger logIt:SMK_LOG_WARN         \
src:__FILE__              \
line:__LINE__              \
fmt:fmt_, ##__VA_ARGS__ ] \

#define SMKLogError(fmt_,...) [SMKLogger logIt:SMK_LOG_ERROR         \
src:__FILE__              \
line:__LINE__              \
fmt:fmt_, ##__VA_ARGS__ ] \



