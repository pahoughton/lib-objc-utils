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
#import "SMKException.h"
#import "StlUtilsLogTie.h"

#define LOGThrow( _fmt_, ... )  [NSException raise:@"SMKLogger" format:_fmt_,##__VA_ARGS__ ]


static NSString * SMKLogLevelStrings[] = { @"DBG ",
    @"INF ",
    @"WRN ",
    @"ERR " };

static SMKLogger * dfltAppLogger = nil;
static NSUInteger  dfltMaxSize = (100 * 1024); // i.e 50K
static NSDateFormatter * dfltLogDateFormater = nil;

@implementation SMKLogger
@synthesize outLogLevel          = _outLogLevel;
@synthesize logFileFn            = _logFileFn;
@synthesize maxLogSize           = _maxLogSize;
@synthesize dateFormater         = _dateFormater;
@synthesize logDoOutputDate      = _logDoOutputDate;
@synthesize logDoOutputLevel     = _logDoOutputLevel;
@synthesize logDoOutputSrcLine   = _logDoOutputSrcLine;
@synthesize logFile              = _logFile;
@synthesize teeLogger            = _teeLogger;
@synthesize logIsFile            = _logIsFile;
@synthesize fm                   = _fm;
//@synthesize logLock;
+(NSString *)setDefaultLogDir:(NSString *)dir
                   name:(NSString *)name
                   user:(NSString *)user
{
  
  BOOL isDir = false;
  NSFileManager * fm = [NSFileManager defaultManager];
  [fm fileExistsAtPath: dir isDirectory:&isDir];
  if( ! isDir ) {
    return [NSString stringWithFormat:
            @"Log directory '%@' does not exists"
            ,dir];
  }
  
  NSString * logFn = [NSString stringWithFormat:
                      @"%@/%@.%@.log"
                      ,dir
                      ,name
                      ,user];
  
  [[SMKLogger appLogger] setLogFileFn: logFn];
  return nil;
}

-(void)cnfgLogger:(NSFileHandle *)logHandle
{
  [ self setFm: [NSFileManager defaultManager]];
  
  [self setLogDoOutputDate: TRUE ];
  [self setLogDoOutputLevel: TRUE ];
  [self setLogDoOutputSrcLine: TRUE ];
  [self setTeeLogger: nil ];
  NSUserDefaults * dfls = [NSUserDefaults standardUserDefaults];
  NSString * udStrVal;
  NSNumber * udNumVal;
  
  if( dfltLogDateFormater == nil ) {
    udStrVal = [dfls stringForKey:[SMKLogger userDefaultDateFormatKey]];
    if( udStrVal != nil ) {
      dfltLogDateFormater = [[NSDateFormatter alloc]init];
      [dfltLogDateFormater setDateFormat:udStrVal];
    } else {
      NSString * dfltDateFmtStr = @"yyMMdd HHmmss";
      dfltLogDateFormater = [[NSDateFormatter alloc]init];
      [dfltLogDateFormater setDateFormat:dfltDateFmtStr];
      [dfls setObject:dfltDateFmtStr forKey:[SMKLogger userDefaultDateFormatKey]];
    }
    [self setDateFormater: dfltLogDateFormater];
  } else {
    [self setDateFormater: dfltLogDateFormater ];
  }
  
  udNumVal = [dfls objectForKey:[SMKLogger userDefaultMaxLogSize]];
  if( udNumVal != nil ) {
    NSUInteger maxSize = [udNumVal unsignedIntegerValue];
    if( maxSize < dfltMaxSize ) {
      udNumVal = [NSNumber numberWithUnsignedInteger: dfltMaxSize];
      [dfls setObject: udNumVal forKey:[SMKLogger userDefaultMaxLogSize]];
    }
    [self setMaxLogSize: [udNumVal unsignedIntegerValue] ];
  } else {
    [self setMaxLogSize: dfltMaxSize ];
    NSNumber * dfltMaxSize = [NSNumber numberWithUnsignedInteger:self.maxLogSize];
    [dfls setObject:dfltMaxSize forKey:[SMKLogger userDefaultMaxLogSize]];
  }
  
  udStrVal = [dfls objectForKey:[SMKLogger userDefaultOutLogLevel]];
  if( udStrVal != nil ) {
    // ok cheating - only going by first letter :)
    if( [udStrVal characterAtIndex:0] == 'N' ) {
      [self setOutLogLevel: SMK_LOG_NONE ];
    } else if( [udStrVal characterAtIndex:0] == 'E' ) {
      [self setOutLogLevel: SMK_LOG_ERROR ];
    } else if( [udStrVal characterAtIndex:0] == 'W' ) {
      [self setOutLogLevel: SMK_LOG_WARN ];
    } else if( [udStrVal characterAtIndex:0] == 'I' ) {
      [self setOutLogLevel: SMK_LOG_INFO ];
    } else {
      //oops may as well output debug
      [self setOutLogLevel: SMK_LOG_DEBUG ];
    }
  }
  if( logHandle == nil ) {
    NSString * lgFn = [dfls objectForKey:[SMKLogger userDefaultLogFile]];
    if( lgFn == nil ) {
      NSString *appName;
      
      appName = [[[NSBundle mainBundle] localizedInfoDictionary] 
                 objectForKey:@"CFBundleName"];
      if( appName == nil ) {
        appName = [[[NSBundle mainBundle] infoDictionary] 
                   objectForKey:@"CFBundleName"];
      }
      if( appName == nil ) {
        appName = @"SMKLogger";
      }
      
      NSString *bundlePath = [[NSBundle mainBundle] bundlePath]; 
      if( bundlePath == nil
         || [bundlePath rangeOfString:@"DerivedData"].location != NSNotFound 
         || [bundlePath rangeOfString:@"Xcode.app"].location != NSNotFound 
         ) {
        // running from build dir, use /tmp;
        bundlePath = @"/tmp";
      }
      lgFn = [[bundlePath stringByAppendingPathComponent: appName] 
              stringByAppendingPathExtension:@"log"];
      
    }
    // set fn - opens
    [self setLogFileFn: lgFn ];

  } else {
    [self setLogIsFile: FALSE]; // your handle I can't trim
    [self setLogFile: logHandle];
  }
  //logLock = [[NSLock alloc] init ];
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
    self->_logFileFn = @"STDERR";
    self->_logIsFile = FALSE;
    [self cnfgLogger:[NSFileHandle fileHandleWithStandardError]];
  }
  return self;    
  
}
-(id)initToStdout
{
  self = [super init];
  if( self ) {
    self->_logFileFn = @"STDOUT";
    self->_logIsFile = FALSE;
    [self cnfgLogger:[NSFileHandle fileHandleWithStandardOutput]];
  }
  return self;        
}

-(id)initWithPath:(NSString *)path
{
  self = [super init];
  if( self ) {
    [[NSUserDefaults standardUserDefaults]
     setObject: path forKey:[SMKLogger userDefaultLogFile]];
    [self cnfgLogger: nil];
  }
  return self;    
}
-(void)setLogFileFn:(NSString *)fn
{
  if( self.logFile != nil ) {
    [self.logFile closeFile];
    [self setLogFile: nil ];
  }
  [[NSUserDefaults standardUserDefaults]
   setObject: fn forKey:[SMKLogger userDefaultLogFile]];
  self->_logFileFn = fn;
  // OPEN HERE
  if( ! [self.fm fileExistsAtPath: self.logFileFn] ) {
    if( ! [self.fm createFileAtPath:self.logFileFn contents:nil attributes:nil] ) {
      LOGThrow(@"creat empty - SUCKS log %@ really!!",self.logFileFn );
    }
  }
  self->_logFile = [NSFileHandle fileHandleForWritingAtPath: self.logFileFn];
  if( self.logFile == nil ) {
    // ouch
    LOGThrow(@"open log %@ really!!",self.logFileFn);
  }
  [self setLogIsFile: TRUE];
  [self.logFile seekToEndOfFile];
}
-(NSString *)logFileFn
{
  return self->_logFileFn;
}

-(void)trimLog
{
  //[logLock lock];
  [self.logFile closeFile];
  [self setLogFile: nil ];
  
  NSString * tmpFn = [NSString stringWithFormat:@"%@.trim",self.logFileFn];
  NSError * er = nil;
  [self.fm moveItemAtPath:self.logFileFn toPath:tmpFn error:&er];
  if( er != nil ) {
    //[logLock unlock];
    LOGThrow(@"move %@ to %@",self.logFileFn, tmpFn);
  }
  NSFileHandle * oldLog = [NSFileHandle fileHandleForReadingAtPath:tmpFn];
  if( oldLog == nil ) {
    //[logLock unlock];
    LOGThrow(@"open tmp %@ really!!",tmpFn );
  }
  NSDictionary * fnAttrs = [self.fm attributesOfItemAtPath:tmpFn
                                                     error:nil];
  if( ! [self.fm createFileAtPath:self.logFileFn contents:nil attributes:nil] ) {
    LOGThrow(@"create %@ failed :(",self.logFileFn);
  }
  NSFileHandle * nFh = [NSFileHandle fileHandleForWritingAtPath:self.logFileFn];
  
  if( nFh == nil ) {
    //[logLock unlock];
    LOGThrow( @"open new log %@ really!!",self.logFileFn);
  }
  unsigned long long curSize = [fnAttrs fileSize];
  unsigned long long seekPos = 0;
  if( curSize > self.maxLogSize ) {
    seekPos = (curSize / 4);
  }
  [oldLog seekToFileOffset: seekPos ];
  
  // We have gobs of memory - FIXME - should do pages, but lazy
  [nFh writeData:[oldLog readDataToEndOfFile]];
  [oldLog closeFile];
  [self.fm removeItemAtPath: tmpFn error:&er];
  [self setLogFile:nFh];
  // [logLock unlock];
}

-(void)mtLogIt:(NSString *)msg
{
  // [logLock lock];
  if( self.logIsFile && [self.logFile offsetInFile] > self.maxLogSize ) {
    [self trimLog];
  }
  [self.logFile writeData:[msg dataUsingEncoding:NSUTF8StringEncoding]]; 
  [self.logFile writeData:[NSData dataWithBytes:"\n" length:1]];
  [self.logFile synchronizeFile];
  // [logLock unlock];
}

-(void)logIt:(enum SMKLogLevel)lvl
        func:(const char *)func
        line:(int)srcLine
         fmt:(NSString *)msgFmt
   arguments:(va_list)args
{
  if( lvl < self.outLogLevel
     && ( self.teeLogger == nil
         || lvl < self.teeLogger.outLogLevel ) ) {
       return;
     }
  
  // ar we at max size?
  NSMutableString * logEntry = [[NSMutableString alloc]init];
  
  if( self.logDoOutputDate ) {
    [logEntry appendString:[self.dateFormater stringFromDate:[NSDate date]]];
    [logEntry appendString:@" "];
  }
  
  if( self.logDoOutputLevel ) {
    [logEntry appendString:
     SMKLogLevelStrings[ lvl <= SMK_LOG_ERROR 
                        ? lvl : SMK_LOG_ERROR ] ];
  }
  
  if( self.logDoOutputSrcLine ) {
    NSString * srcFile = [[NSString stringWithUTF8String:func]
                          lastPathComponent];
    
    [logEntry appendFormat:@"%@:%d ",srcFile,srcLine];
  }
  
  [logEntry appendString:[[NSString alloc]
                          initWithFormat:msgFmt arguments:args]];
  
  if( lvl >= self.outLogLevel )  {
    [self performSelectorOnMainThread: @selector(mtLogIt:)
                           withObject: logEntry
                        waitUntilDone: NO];
    // [self mtLogIt:logEntry];
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
  if( self.teeLogger 
     && lvl >= self.teeLogger.outLogLevel ) {
    [self.teeLogger performSelectorOnMainThread: @selector(mtLogIt:)
                                     withObject: logEntry
                                  waitUntilDone: FALSE];
    //[self.teeLogger mtLogIt:logEntry];
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

-(void)logIt:(enum SMKLogLevel)lvl
        func:(const char *)func
        line:(int)srcLine
         fmt:(NSString *)msgFmt, ...
{    
  va_list(args);
  va_start(args, msgFmt);
  [self logIt:lvl func:func line:srcLine fmt:msgFmt arguments:args];
  va_end(args);
  
}

+(void)logIt:(enum SMKLogLevel)lvl
        func:(const char *)func
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
  [logger logIt:lvl func:func line:srcLine fmt:msgFmt arguments:args];
  va_end(args);
}

+(void)logException:(NSException *)except func:(const char *)func line:(int)srcLine
{
  SMKLogger * logger = [SMKLogger appLogger];
  
  NSMutableString * excMsg = [[NSMutableString alloc] init];
  [excMsg appendFormat:@"Exception: %@: %@\n",[except name], [except reason]];
  NSArray * backTrace = [except callStackSymbols];
  if( backTrace == nil || backTrace.count == 0) {
    backTrace = [NSThread callStackSymbols];
  }
  for( NSString * symName in backTrace ) {
    [excMsg appendFormat:@"    %@\n",symName];
  }
  [logger logIt:SMK_LOG_ERROR func:func line:srcLine fmt:@"%@",excMsg];
}

-(void) dealloc
{
  if( self.logFile ) {
    [self.logFile closeFile];
  }
}

+(SMKLogger *)appLogger
{
  if( dfltAppLogger == nil ) {
    dfltAppLogger = [[SMKLogger alloc]init];
    [StlUtilsLogTie tieToSMKLogger: dfltAppLogger];
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
