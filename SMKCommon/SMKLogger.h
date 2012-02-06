//
//  SMKLogger.h
//  Dig-It
//
//  Created by Paul Houghton on 1/29/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

// FIXME - change SMK Log Error to support raising exceptions. ( a stacktrace would be nice );

#import <Foundation/Foundation.h>

#define SMKLogError( ... ) SMKLogger( __FILE__, __LINE__, __VA_ARGS__ )
#define SMKLogInfo NSLog
#define SMKLogWarn NSLog
#define SMKLogWarnv NSLogv
#define SMKLogDebug( ... ) SMKLogger( __FILE__, __LINE__, __VA_ARGS__ )

void SMKLogger( const char * srcFile, int srcLine, NSString * fmtString, ... );

#define TEST_DEF @"test_define"

@interface SMKLoggerClass : NSObject

@end
