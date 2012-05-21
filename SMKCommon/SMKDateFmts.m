//
//  SMK_DateFmts.m
//  SMKCommon
//
//  Created by Paul Houghton on 120508.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import "SMKDateFmts.h"

static NSString * YYYY_MM_DD_HH_MM_SS_FmtStr = @"yyyy-MM-dd HH:mm:ss";
static NSString * YYYY_MM_DD_FmtStr = @"yyyy-MM-dd";
static NSString * YYYY_FmtStr = @"yyyy";
static NSString * HH_MM_SS_FmtStr = @"HH:mm:ss";

static NSString * YYMMDD_HHMMSS_FmtStr = @"yyMMdd HHmmss";

static NSDateFormatter * YYYY_MM_DD_HH_MM_SS_Fmt = nil;
static NSDateFormatter * YYYY_MM_DD_Fmt = nil;
static NSDateFormatter * YYYY_Fmt = nil;
static NSDateFormatter * HH_MM_SS_Fmt = nil;
static NSDateFormatter * YYMMDD_HHMMSS_Fmt = nil;

@implementation SMKDateFmts

+(NSDate *)yyyy_mm_dd_hh_mm_ssStr:(NSString *)str
{
  if( YYYY_MM_DD_HH_MM_SS_Fmt == nil ) {
    YYYY_MM_DD_HH_MM_SS_Fmt = [[NSDateFormatter alloc]init];
    [YYYY_MM_DD_HH_MM_SS_Fmt setDateFormat: YYYY_MM_DD_HH_MM_SS_FmtStr];
  }
  return [YYYY_MM_DD_HH_MM_SS_Fmt dateFromString:str];
}
+(NSString *)yyyy_mm_dd_hh_mm_ss:(NSDate *)dt
{
  if( YYYY_MM_DD_HH_MM_SS_Fmt == nil ) {
    YYYY_MM_DD_HH_MM_SS_Fmt = [[NSDateFormatter alloc]init];
    [YYYY_MM_DD_HH_MM_SS_Fmt setDateFormat: YYYY_MM_DD_HH_MM_SS_FmtStr];
  }
  return [YYYY_MM_DD_HH_MM_SS_Fmt stringFromDate: dt ];  
}
+(NSDate *)yyyy_mm_ddStr:(NSString *)str
{
  if( YYYY_MM_DD_Fmt == nil ) {
    YYYY_MM_DD_Fmt = [[NSDateFormatter alloc]init];
    [YYYY_MM_DD_Fmt setDateFormat: YYYY_MM_DD_FmtStr];
  }
  return [YYYY_MM_DD_Fmt dateFromString:str];
}
+(NSString *)yyyy_mm_dd:(NSDate *)dt
{
  if( YYYY_MM_DD_Fmt == nil ) {
    YYYY_MM_DD_Fmt = [[NSDateFormatter alloc]init];
    [YYYY_MM_DD_Fmt setDateFormat: YYYY_MM_DD_FmtStr];
  }
  return [YYYY_MM_DD_Fmt stringFromDate: dt ];  
}
+(NSDate *)yyyyStr:(NSString *)str
{
  if( YYYY_Fmt == nil ) {
    YYYY_Fmt = [[NSDateFormatter alloc]init];
    [YYYY_Fmt setDateFormat: YYYY_FmtStr];
  }
  return [YYYY_Fmt dateFromString:str];
}
+(NSString *)yyyy:(NSDate *)dt
{
  if( YYYY_Fmt == nil ) {
    YYYY_Fmt = [[NSDateFormatter alloc]init];
    [YYYY_Fmt setDateFormat: YYYY_FmtStr];
  }
  return [YYYY_Fmt stringFromDate: dt ];  
}
+(NSDate *)hh_mm_ssStr:(NSString *)str
{
  if( HH_MM_SS_Fmt == nil ) {
    HH_MM_SS_Fmt = [[NSDateFormatter alloc]init];
    [HH_MM_SS_Fmt setDateFormat: HH_MM_SS_FmtStr];
  }
  return [HH_MM_SS_Fmt dateFromString:str];
}
+(NSString *)hh_mm_ss:(NSDate *)dt
{
  if( HH_MM_SS_Fmt == nil ) {
    HH_MM_SS_Fmt = [[NSDateFormatter alloc]init];
    [HH_MM_SS_Fmt setDateFormat: HH_MM_SS_FmtStr];
  }
  return [HH_MM_SS_Fmt stringFromDate: dt ];  
}
+(NSDate *)yymmdd_hhmmssStr:(NSString *)str
{
  if( YYMMDD_HHMMSS_Fmt == nil ) {
    YYMMDD_HHMMSS_Fmt = [[NSDateFormatter alloc]init];
    [YYMMDD_HHMMSS_Fmt setDateFormat: YYMMDD_HHMMSS_FmtStr];
  }
  return [YYMMDD_HHMMSS_Fmt dateFromString:str];
}
+(NSString *)yymmdd_hhmmss:(NSDate *)dt
{
  if( YYMMDD_HHMMSS_Fmt == nil ) {
    YYMMDD_HHMMSS_Fmt = [[NSDateFormatter alloc]init];
    [YYMMDD_HHMMSS_Fmt setDateFormat: YYMMDD_HHMMSS_FmtStr];
  }
  return [YYMMDD_HHMMSS_Fmt stringFromDate: dt ];  
}


@end
