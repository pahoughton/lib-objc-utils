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
+(void)raise:(NSString *)name format:(NSString *)format, ...
{
    va_list args;
    va_start(args, format);
    NSString * fmtStr = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    SMKLogWarn(@"Excpt: %@ %@", name, fmtStr);
    [super raise:name format:fmtStr];
}

@end
