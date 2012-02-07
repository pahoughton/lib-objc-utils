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


@implementation SMKLogger
@synthesize outLogLevel;

-(id)init
{
    self = [super init];
    if( self ) {
        outLogLevel = SMK_LOG_DEBUG;
    }
    return self;
}

-(void)mtLogIt:(NSString *)msg
{
    NSFileHandle * dest = [NSFileHandle fileHandleWithStandardOutput];
    
    [dest writeData:[msg dataUsingEncoding:NSUTF8StringEncoding]]; 
    [dest writeData:[NSData dataWithBytes:"\n" length:1]];
    [dest synchronizeFile];
}

-(void)logIt:(enum LogLevel)lvl 
         src:(const char *)srcFn 
        line:(int)srcLine
         fmt:(NSString *)msgFmt
   arguments:(va_list)args
{
    if( lvl < outLogLevel ) 
        return;
    
    NSMutableString * logEntry = [[NSMutableString alloc]init];

    BOOL lgDate = true;
    if( lgDate ) {
        NSString * dateFmt = @"%y%m%d %H%M%S";
        NSString * userDfltDateFmt
        = [[NSUserDefaults standardUserDefaults]
           stringForKey:[SMKLogger userDefaultDateFormatKey]];
        
        if( userDfltDateFmt ) {
            dateFmt = userDfltDateFmt;
        }
        
        [logEntry appendString:
         [[NSDate  date] 
          descriptionWithCalendarFormat:dateFmt 
          timeZone:nil
          locale:[[NSUserDefaults standardUserDefaults] 
                  dictionaryRepresentation]]];
        [logEntry appendString:@" "];
    } // and that was just for the date :)
    
    BOOL lgLevel = TRUE;
    
    if( lgLevel ) {
        [logEntry appendString:
         SMKLogLevelStrings[ lvl <= SMK_LOG_ERROR 
                            ? lvl : SMK_LOG_ERROR ] ];
    }
    
    BOOL lgSrcLine = TRUE;
    if( lgSrcLine ) {
        NSString * srcFile = [[NSString stringWithUTF8String:srcFn]
                              lastPathComponent];
        
        [logEntry appendFormat:@"%@:%d ",srcFile,srcLine];
    }
    
    [logEntry appendString:[[NSString alloc]
                            initWithFormat:msgFmt arguments:args]];
    
    if( [NSThread isMainThread] ) {
        [self mtLogIt:logEntry];
        
    } else {
        [self performSelectorOnMainThread:@selector(mtLogIt:)
                               withObject:logEntry 
                            waitUntilDone:NO];
    }
}

-(void)logIt:(enum LogLevel)lvl 
         src:(const char *)srcFn 
        line:(int)srcLine
         fmt:(NSString *)msgFmt, ...
{
    if( lvl < outLogLevel ) 
        return;
    
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
    SMKLogger * logger = [[SMKLogger alloc]init];
    if( lvl < [logger outLogLevel] ) 
        return;
    
    va_list(args);
    va_start(args, msgFmt);
    
    // I'll probaqbly end up with a static 'default' logger
    
    [logger logIt:lvl src:srcFn line:srcLine fmt:msgFmt arguments:args];
    va_end(args);
}

+(void)LogException:(NSException *)except src:(const char *)srcFn line:(int)srcLine
{
    SMKLogger * logger = [[SMKLogger alloc]init];
    
    NSMutableString * excMsg = [[NSMutableString alloc] init];
    [excMsg appendFormat:@"Exception: %@: %@\n",[except name], [except reason]];
    NSArray * backTrace = [except callStackSymbols];
    for( NSString * symName in backTrace ) {
        [excMsg appendFormat:@"    %@\n",symName];
    }
    [logger logIt:SMK_LOG_ERROR src:srcFn line:srcLine fmt:@"%@",excMsg];
}

+(NSString *)userDefaultDateFormatKey
{
    return @"SMKLoggerDateFormat";
}

         

@end
