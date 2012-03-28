/**
  File:		SMKDateTimeUtilsMore.m
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):    Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
  Created:      120312  08:42
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
#import <SMKCommon.h>
#import "SMKDateTimeUtils.h"
// HH:MM:SS
NSString * SMKHH_MM_SSFromSeconds( NSInteger secs )
{
    return [NSString stringWithFormat:
            @"%02d:%02d:%02d",
            HourInTimeT(secs),
            MinInTimeT(secs),
            SecInTimeT( secs ) ];
    
}
// HHMMSS
NSString * SMKHHMMSSFromSeconds( NSInteger secs )
{
    return [NSString stringWithFormat:
            @"%02d%02d%02d",
            HourInTimeT(secs),
            MinInTimeT(secs),
            SecInTimeT( secs ) ];
        
}
static NSDateFormatter * dfltSMKShortDateFormater = nil;

NSString * SMKTimeStampShort(void)
{
    if( dfltSMKShortDateFormater == nil ) {
        NSString * dfltDateFmtStr = @"yyMMdd HHmmss";
        dfltSMKShortDateFormater = [[NSDateFormatter alloc]init];
        [dfltSMKShortDateFormater setDateFormat:dfltDateFmtStr];
    }
    return [dfltSMKShortDateFormater stringFromDate:[NSDate date]];
}
