/**
 File:		SMKLogger.m
 Project:	SMKCocoaCommon 
 Desc:
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

#import "SMKLogger.h"

static NSString * SMKLogLevelStrings[] = { @"DBG ",
    @"INF ",
    @"WRN ",
    @"ERR " };

static SMKLogger * dfltAppLogger = nil;
static NSUInteger  dfltMaxSize = (50 * 1024); // i.e 50K
static NSDateFormatter * dfltLogDateFormater = nil;

@implementation SMKLogger
@synthesize outLogLevel;
@synthesize logFileFn;
@synthesize maxLogSize;
@synthesize dateFormater;
@synthesize logDoOutputDate;
@synthesize logDoOutputLevel;
@synthesize logDoOutputSrcLine;
@synthesize logFile;
@synthesize teeLogger;
@synthesize logIsFile;
@synthesize fm;
@synthesize logLock;

-(void)cnfgLogger:(NSFileHandle *)logHandle
{
    fm = [NSFileManager defaultManager];

    logDoOutputDate = TRUE;
    logDoOutputLevel = TRUE;
    logDoOutputSrcLine = TRUE;
    teeLogger = nil;
    NSUserDefaults * dfls = [NSUserDefaults standardUserDefaults];
    NSString * udStrVal;
    NSNumber * udNumVal;

    if( dfltLogDateFormater == nil ) {
        // FIXME - this is to clean out the old format string
        udStrVal = nil; // [dfls stringForKey:[SMKLogger userDefaultDateFormatKey]];
        if( udStrVal != nil ) {
            dfltLogDateFormater = [[NSDateFormatter alloc]init];
            [dfltLogDateFormater setDateFormat:udStrVal];
        } else {
            NSString * dfltDateFmtStr = @"yyMMdd HHmmss";
            dfltLogDateFormater = [[NSDateFormatter alloc]init];
            [dfltLogDateFormater setDateFormat:dfltDateFmtStr];
            [dfls setObject:dfltDateFmtStr forKey:[SMKLogger userDefaultDateFormatKey]];
        }
        dateFormater = dfltLogDateFormater;
    } else {
        dateFormater = dfltLogDateFormater;        
    }
    
    udNumVal = [dfls objectForKey:[SMKLogger userDefaultMaxLogSize]];
    if( udNumVal != nil ) {
        maxLogSize = [udNumVal unsignedIntegerValue];
    } else {
        maxLogSize = dfltMaxSize;
        NSNumber * dfltMaxSize = [NSNumber numberWithUnsignedInteger:maxLogSize];
        [dfls setObject:dfltMaxSize forKey:[SMKLogger userDefaultMaxLogSize]];
    }
    
    udStrVal = [dfls objectForKey:[SMKLogger userDefaultOutLogLevel]];
    if( udStrVal != nil ) {
        // ok cheating - only going by first letter :)
        if( [udStrVal characterAtIndex:0] == 'N' ) {
            outLogLevel = SMK_LOG_NONE;
        } else if( [udStrVal characterAtIndex:0] == 'E' ) {
            outLogLevel = SMK_LOG_ERROR;
        } else if( [udStrVal characterAtIndex:0] == 'W' ) {
            outLogLevel = SMK_LOG_WARN;
        } else if( [udStrVal characterAtIndex:0] == 'I' ) {
            outLogLevel = SMK_LOG_INFO;
        } else {
            //oops may as well output debug
            outLogLevel = SMK_LOG_DEBUG;
        }
    }
    if( logHandle == nil ) {
        udStrVal = [dfls objectForKey:[SMKLogger userDefaultLogFile]];
        if( udStrVal != nil ) {
            logFileFn = udStrVal;
        } else {
            NSString *appName = [[[NSBundle mainBundle] 
                                  localizedInfoDictionary] 
                                 objectForKey:(NSString *)kCFBundleNameKey];
            NSString *bundlePath = [[NSBundle mainBundle] bundlePath]; 
            // arg test harness
            if( appName == nil ) {
                if( [dfls objectForKey:@"SenTest"] ) {
                    logFileFn = [NSString stringWithFormat:@"%@/SMKLogger.log",NSHomeDirectory()];
                } else {
                    logFileFn = @"/tmp/SMKLogger.log";
                }
            } else {
                logFileFn = [NSString stringWithFormat:@"%@/%@.log",bundlePath,appName];
                [dfls setObject:logFileFn forKey:[SMKLogger userDefaultLogFile]];
            }
        }
        // OPEN HERE
        if( ! [fm fileExistsAtPath:logFileFn] ) {
            if( ! [fm createFileAtPath:logFileFn contents:nil attributes:nil] ) {
                [NSException raise:@"SMKLogger" format:@"creat empty - SUCKS log %@ really!!",logFileFn];                
            }
        }
        logFile = [NSFileHandle fileHandleForWritingAtPath:logFileFn];
        if( logFile == nil ) {
            // ouch
            [NSException raise:@"SMKLogger" format:@"open log %@ really!!",logFileFn];
        }
        [logFile seekToEndOfFile];
    } else {
        logIsFile = FALSE; // your handle I can't trim
        logFile = logHandle;
    }
    logLock = [[NSLock alloc] init ];
    [logLock setName:logFileFn];
    // WOW i think it's finally good to go :)
}

-(id)init
{
    self = [super init];
    if( self ) {
        [self cnfgLogger:nil];
    }
    return self;
}
-(id)initWithHandle:(NSFileHandle *)handle
{
    self = [super init];
    if( self ) {
        [self cnfgLogger:handle];
    }
    return self;    
}
-(id)initToStderr
{
    self = [super init];
    if( self ) {
        logFileFn = @"STDERR";
        logIsFile = FALSE;
        [self cnfgLogger:[NSFileHandle fileHandleWithStandardError]];
    }
    return self;    
    
}
-(id)initToStdout
{
    self = [super init];
    if( self ) {
        logFileFn = @"STDOUT";
        logIsFile = FALSE;
        [self cnfgLogger:[NSFileHandle fileHandleWithStandardOutput]];
    }
    return self;        
}

-(id)initWithPath:(NSString *)path
{
    self = [super init];
    if( self ) {
        logFileFn = path;
        [self cnfgLogger:[NSFileHandle fileHandleForWritingAtPath:path]];
    }
    return self;    
}

-(void)trimLog
{
    [logLock lock];
    [logFile closeFile];
    NSString * tmpFn = [NSString stringWithFormat:@"%@.trim",logFileFn];
    NSError * er = nil;
    [fm moveItemAtPath:logFileFn toPath:tmpFn error:&er];
    if( er != nil ) {
        [NSException raise:@"SMKLogger" format:@"move %@ to %@",logFileFn, tmpFn];
    }
    NSFileHandle * oldLog = [NSFileHandle fileHandleForReadingAtPath:tmpFn];
    if( oldLog == nil ) {
        [NSException raise:@"SMKLogger" format:@"open tmp %@ really!!",tmpFn];
    }
    NSDictionary * fnAttrs = [fm attributesOfItemAtPath:tmpFn
                                                  error:nil];
    logFile = [NSFileHandle fileHandleForWritingAtPath:logFileFn];
    if( logFile == nil ) {
        [NSException raise:@"SMKLogger" format:@"open new log %@ really!!",logFileFn];
    }
    unsigned long long curSize = [fnAttrs fileSize];
    unsigned long long seekPos = 0;
    if( curSize > maxLogSize ) {
        // i.e. seek into the file 25% (+ any overage)
        seekPos = (maxLogSize / 4);
        seekPos -= curSize - maxLogSize;
    } else if( curSize > (maxLogSize / 4) ) {
        // take off 25% as long as the file is big enough
        seekPos = (maxLogSize / 4);
    } else {
        // don't know why trim was called, but o well
        seekPos = 0;
    }
    [oldLog seekToFileOffset:seekPos];
    
    // We have gobs of memory - FIXME - should do pages, but lazy
    [logFile writeData:[oldLog readDataToEndOfFile]];
    [oldLog closeFile];
    [fm removeItemAtPath:tmpFn error:&er];
    [logLock unlock];
}

-(void)mtLogIt:(NSString *)msg
{
    [logLock lock];
    [logFile writeData:[msg dataUsingEncoding:NSUTF8StringEncoding]]; 
    [logFile writeData:[NSData dataWithBytes:"\n" length:1]];
    [logFile synchronizeFile];
    [logLock unlock];
}

-(void)logIt:(enum LogLevel)lvl 
         src:(const char *)srcFn 
        line:(int)srcLine
         fmt:(NSString *)msgFmt
   arguments:(va_list)args
{
    if( lvl < outLogLevel
       && ( teeLogger == nil
           || lvl < teeLogger.outLogLevel ) ) {
        return;
    }
    
    // ar we at max size?
    if( logIsFile && [logFile offsetInFile] > maxLogSize ) {
        [self trimLog];
    }
    NSMutableString * logEntry = [[NSMutableString alloc]init];

    if( logDoOutputDate ) {
        [logEntry appendString:[dateFormater stringFromDate:[NSDate date]]];
        [logEntry appendString:@" "];
    }
    
    if( logDoOutputLevel ) {
        [logEntry appendString:
         SMKLogLevelStrings[ lvl <= SMK_LOG_ERROR 
                            ? lvl : SMK_LOG_ERROR ] ];
    }
    
    if( logDoOutputSrcLine ) {
        NSString * srcFile = [[NSString stringWithUTF8String:srcFn]
                              lastPathComponent];
        
        [logEntry appendFormat:@"%@:%d ",srcFile,srcLine];
    }
    
    [logEntry appendString:[[NSString alloc]
                            initWithFormat:msgFmt arguments:args]];
    
    if( lvl >= outLogLevel )  {
        [self mtLogIt:logEntry];
        /*
        if( [NSThread isMainThread] ) {
            [self mtLogIt:logEntry];
            
        } else {
            [self performSelectorOnMainThread:@selector(mtLogIt:)
                                   withObject:logEntry 
                                waitUntilDone:NO];
        }
         */
    }
    if( teeLogger 
       && lvl >= teeLogger.outLogLevel ) {
        [teeLogger mtLogIt:logEntry];
        /*
        if( [NSThread isMainThread] ) {
            [teeLogger mtLogIt:logEntry];
            
        } else {
            [teeLogger performSelectorOnMainThread:@selector(mtLogIt:)
                                        withObject:logEntry 
                                     waitUntilDone:NO];
        }
        */
    }
}

-(void)logIt:(enum LogLevel)lvl 
         src:(const char *)srcFn 
        line:(int)srcLine
         fmt:(NSString *)msgFmt, ...
{    
    va_list(args);
    va_start(args, msgFmt);
    [self logIt:lvl src:srcFn line:srcLine fmt:msgFmt arguments:args];
    va_end(args);
    
    
}

+(void)logIt:(enum LogLevel)lvl 
         src:(const char *)srcFn 
        line:(int)srcLine
         fmt:(NSString *)msgFmt, ...
{
    SMKLogger * logger = [SMKLogger appLogger];
    
    if( lvl < logger.outLogLevel
       && ( logger.teeLogger == nil
           || lvl < logger.teeLogger.outLogLevel ) ) {
        return;
    }
    
    va_list(args);
    va_start(args, msgFmt);
    [logger logIt:lvl src:srcFn line:srcLine fmt:msgFmt arguments:args];
    va_end(args);
}

+(void)logException:(NSException *)except src:(const char *)srcFn line:(int)srcLine
{
    SMKLogger * logger = [SMKLogger appLogger];
    
    NSMutableString * excMsg = [[NSMutableString alloc] init];
    [excMsg appendFormat:@"Exception: %@: %@\n",[except name], [except reason]];
    NSArray * backTrace = [except callStackSymbols];
    for( NSString * symName in backTrace ) {
        [excMsg appendFormat:@"    %@\n",symName];
    }
    [logger logIt:SMK_LOG_ERROR src:srcFn line:srcLine fmt:@"%@",excMsg];
}

-(void) dealloc
{
    if( logFile ) {
        [logFile closeFile];
    }
}

+(SMKLogger *)appLogger
{
    if( dfltAppLogger == nil ) {
        dfltAppLogger = [[SMKLogger alloc]init];
    }
    return dfltAppLogger;
}

+(NSString *)userDefaultDateFormatKey
{
    return @"SMKLoggerDateFormat";
}

+(NSString *)userDefaultOutLogLevel
{
    return @"SMKLoggerOutLogLevel";
}
+(NSString *)userDefaultLogFile
{
    return @"SMKLoggerLogFile";
}

+(NSString *)userDefaultMaxLogSize
{
    return @"SMKLoggerMaxLogSize";
}
         

@end
