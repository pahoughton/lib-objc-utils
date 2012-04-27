/**
 File:		SMKLogger.h
 Project:	SMKCocoaCommon 
 Desc:
 
    Log messages to your chosen destination
    
    Default Fmt: 120228 142302 ERR Class.m:37 Just a bad thing msg
 
    SMKLogError( @"Just a %@ thing happend",@"Terrible" );
    SMKLogWarn( @"Just a %@ thing happend",@"ucky" );
    SMKLogInfo( @"Just a %@ thing happend",@"normal" );
    SMKLogDebug( @"Just a %@ thing happend",@"silly" );
 
    SMKLogExcept( NSException * oops );
 
 Notes:
 
 Author(s):   Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
 Created:     01/29/2012 04:36
 Copyright:   Copyright (c) 2012 Secure Media Keepers
              www.SecureMediaKeepers.com
              All rights reserved.
 
 Revision History: (See ChangeLog for details)
 
   $Author$
   $Date$
   $Revision$
   $Name$
   $State$
 
 $Id$
 
**/

#import <Foundation/Foundation.h>

#define SMKFunctUnsup [NSException raise:[self className] format:@"%@::%s Unsupported",[self className],__func__]

@interface SMKLogger : NSObject
enum SMKLogLevel {
    SMK_LOG_DEBUG,
    SMK_LOG_INFO,
    SMK_LOG_WARN,
    SMK_LOG_ERROR,
    SMK_LOG_NONE
};

@property (assign) enum SMKLogLevel outLogLevel;
@property (retain,readonly) NSString * logFileFn;
@property (assign) NSUInteger maxLogSize;
@property (retain) NSDateFormatter * dateFormater;
@property (assign) BOOL logDoOutputDate;
@property (assign) BOOL logDoOutputSrcLine;
@property (assign) BOOL logDoOutputLevel;
@property (retain) NSFileHandle * logFile;
@property (retain) SMKLogger * teeLogger;
@property (assign) BOOL logIsFile;
@property (assign) NSFileManager * fm;
@property (retain) NSLock * logLock;

+(SMKLogger *)appLogger;
+(NSString *)userDefaultDateFormatKey;
+(NSString *)userDefaultOutLogLevel;
+(NSString *)userDefaultLogFile;
+(NSString *)userDefaultMaxLogSize;

-(id)initToStderr;
-(id)initToStdout;
-(id)initWithHandle:(NSFileHandle *)handle;
-(id)initWithPath:(NSString *)path;


-(void)logIt:(enum SMKLogLevel)lvl
        func:(const char *)func
        line:(int)srcLine
         fmt:(NSString *)msgFmt
   arguments:(va_list)args NS_FORMAT_FUNCTION(4,0);

-(void)logIt:(enum SMKLogLevel)lvl
        func:(const char *)func
        line:(int)srcLine
         fmt:(NSString *)msgFmt, ... NS_FORMAT_FUNCTION(4,5);

//-(void)mtLogIt:(NSString *)msg;

+(void)logIt:(enum SMKLogLevel)lvl
        func:(const char *)func
        line:(int)srcLine
         fmt:(NSString *)msgFmt, ... NS_FORMAT_FUNCTION(4,5);

+(void)logException:(NSException *)except func:(const char *)func line:(int)srcLine;

@end

#define SMKLogExcept( _exc_ ) [SMKLogger logException:_exc_ func:__func__ line:__LINE__]

#define SMKLogFunct SMKLogDebug( @"%s",__func__)

#define SMKLogLevelIt(lvl_, fmt_,...)     \
  [SMKLogger logIt: lvl_                  \
              func: __func__              \
              line: __LINE__              \
               fmt: fmt_, ##__VA_ARGS__ ]

#define SMKLogDebug( fmt_,... ) SMKLogLevelIt( SMK_LOG_DEBUG    \
                                              ,fmt_             \
                                              ,##__VA_ARGS__ )

#define SMKLogInfo( fmt_,... ) SMKLogLevelIt( SMK_LOG_INFO      \
                                              ,fmt_             \
                                              ,##__VA_ARGS__ )

#define SMKLogError( fmt_,... ) SMKLogLevelIt( SMK_LOG_ERROR    \
                                              ,fmt_             \
                                              ,##__VA_ARGS__ )

#define SMKLogWarn( fmt_,... ) SMKLogLevelIt( SMK_LOG_WARN      \
                                              ,fmt_             \
                                              ,##__VA_ARGS__ )


/*
#define SMKLogInfo(fmt_,...)  [SMKLogger logIt:SMK_LOG_INFO          \
                                         funct:__func__              \
                                          line:__LINE__              \
                                           fmt:fmt_, ##__VA_ARGS__ ] \

#define SMKLogWarn(fmt_,...)  [SMKLogger logIt:SMK_LOG_         \
                                         funct:__func__              \
                                          line:__LINE__              \
                                           fmt:fmt_, ##__VA_ARGS__ ] \

#define SMKLogDebug(fmt_,...) [SMKLogger logIt:SMK_LOG_DEBUG         \
                                         funct:__func__              \
                                          line:__LINE__              \
                                           fmt:fmt_, ##__VA_ARGS__ ] \

#define SMKLogDebug(fmt_,...) [SMKLogger logIt:SMK_LOG_DEBUG         \
                                         funct:__func__              \
                                          line:__LINE__              \
                                           fmt:fmt_, ##__VA_ARGS__ ] \

#define SMKLogDebug(fmt_,...) [SMKLogger logIt:SMK_LOG_DEBUG         \
                                         funct:__func__              \
                                          line:__LINE__              \
                                           fmt:fmt_, ##__VA_ARGS__ ] \

#define SMKLogDebug(fmt_,...) [SMKLogger logIt:SMK_LOG_DEBUG         \
                                         funct:__func__              \
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
*/
