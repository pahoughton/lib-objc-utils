/**
  File:		SMKException.m
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):    Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
  Created:      2/22/12  6:01 AM
  Copyright:    Copyright (c) 2012 Secure Media Keepers.
                All rights reserved.

  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Revision$
    $Name$
    $State$

  $Id$

**/
#import "SMKException.h"
#import "SMKLogger.h"
@implementation SMKException
+(void)raise: (NSString *)name
        file: (const char *) fileName
       funct: (const char *) funcName
        line: (int)          lineNum
       descr: (NSString *)   descr, ...
{
  va_list args;
  va_start(args, descr );
  NSString * descStr = [[NSString alloc] initWithFormat: descr arguments: args];
  va_end(args);
  NSString * msg = [NSString stringWithFormat:
                    @"%s:%d %@"
                    ,funcName
                    ,lineNum
                    ,descStr ];
  [SMKLogger logIt:SMK_LOG_WARN func: funcName line:lineNum fmt:@"%@",msg];
  [super raise:@"SMKException" format: @"%@",msg];
}

@end
