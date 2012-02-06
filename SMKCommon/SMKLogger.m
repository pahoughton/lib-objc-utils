//
//  SMKLogger.m
//  Dig-It
//
//  Created by Paul Houghton on 1/29/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import "SMKLogger.h"

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


@implementation SMKLoggerClass

@end
