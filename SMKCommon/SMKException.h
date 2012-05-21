#ifndef SMKCommon_SMKException_h_
#define SMKCommon_SMKException_h_
/**
  File:		SMKException.h
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):    Paul Houghton  ___EMAIL___ <Paul.Houghton@SecureMediaKeepers.com>
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

@interface SMKException : NSException
+(void)setUncaughtHandler;
+(void)raise:(NSString *)name
        file: (const char *) fileName
       funct: (const char *) funcName
        line: (int)          lineNum
       descr: (NSString*)    descr,...;
@end
  
#define SMKThrow( desc_, ... ) [SMKException raise: @"SMKError"  \
                                              file: __FILE__     \
                                             funct: __func__     \
                                              line: __LINE__     \
                                             descr: desc_        \
                                                   ,##__VA_ARGS__]
  
/*  @interface SMKException : NSException
  +(void)raise:(NSString *)fmt, ...;
  
  +(void)raise:(NSString *)name format:(NSString *)format, ...;
  @end
  //throw SMKException( __FILE__, __LINE__, desc_, ##__VA_ARGS__ )
  */

#endif /* ! def SMKCommon_SMKException_h_ */

