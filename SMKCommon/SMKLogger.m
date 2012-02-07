//
//  SMKLogger.m
//  Dig-It
//
//  Created by Paul Houghton on 1/29/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import "SMKLogger.h"

static NSString * SMKLogLevelStrings[] = { @"DBG ",
    @"INF ",
    @"WRN ",
    @"ERR " };

/*
 void SMKLogger( const char * srcFile, int srcLine, NSString * fmtString, ... )
{
    va_list arguments;
    va_start(arguments, fmtString);
    NSString *logString = [[NSString alloc] initWithFormat:fmtString arguments:arguments];
    va_end(arguments);

    NSString * srcFn = [[NSString stringWithUTF8String:srcFile]
                        lastPathComponent];
    
    NSLog(@"%@:%d %@",srcFn, srcLine, logString);
}
*/

@implementation SMKLogger


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
    enum LogLevel curLvl = SMK_LOG_DEBUG;
    
    if( lgLevel && lvl >= curLvl ) {
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
    va_list(args);
    va_start(args, msgFmt);
    
    SMKLogger * logger = [[SMKLogger alloc]init];
    
    [logger logIt:lvl src:srcFn line:srcLine fmt:msgFmt arguments:args];
    va_end(args);
}

+(NSString *)userDefaultDateFormatKey
{
    return @"SMKLoggerDateFormat";
}

         

@end
