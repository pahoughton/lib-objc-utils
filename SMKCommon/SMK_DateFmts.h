//
//  SMK_DateFmts.h
//  SMKCommon
//
//  Created by Paul Houghton on 120508.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SMK_DateFmts : NSObject

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
