#ifndef SMKCommon_SMKDateFmts_h
#define SMKCommon_SMKDateFmts_h
/**
  File:		SMKDateFmts.h
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):   Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
  Created:     120520
  Copyright:     Copyright (c) 2012 Secure Media Keepers. All rights reserved.
               All Rights Reserved.
	       
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Revision$
    $Name$
    $State$

  $Id$

**/
#import <Foundation/Foundation.h>

@interface SMKDateFmts : NSObject

+(NSDate *)yyyy_mm_dd_hh_mm_ssStr:(NSString *)str;
+(NSString *)yyyy_mm_dd_hh_mm_ss:(NSDate *)dt;

+(NSDate *)yyyy_mm_ddStr:(NSString *)str;
+(NSString *)yyyy_mm_dd:(NSDate *)dt;

+(NSDate *)yyyyStr:(NSString *)str;
+(NSString *)yyyy:(NSDate *)dt;

+(NSDate *)hh_mm_ssStr:(NSString *)str;
+(NSString *)hh_mm_ss:(NSDate *)dt;

+(NSDate *)yymmdd_hhmmssStr:(NSString *)str;
+(NSString *)yymmdd_hhmmss:(NSDate *)dt;

@end




#if defined( __cplusplus )
extern "C" {
#endif

#if defined( __cplusplus )
};
#endif


#endif /* ! def SMKCommon_SMKDateFmts_h */
