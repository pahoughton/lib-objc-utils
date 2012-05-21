#ifndef SMKCommon_SMKcCommon_h_
#define SMKCommon_SMKcCommon_h_
/**
  File:		SMKcCommon.h
  Project:      SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):   Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
  Created:     120330
  
  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
  
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Revision$
    $Name$
    $State$

  $Id$

**/
#ifndef __OBJC__
// #error "Use SMK_Common.h for non Obj-C"
#endif /* ! defined( __OBJC__ ) */

#import <SMKLogger.h>
#import <Incremental.h>
#import <SMKLogin.h>
#import <SMKCleanFilename.h>
#import <SMKDateFmts.h>
#import <SMKException.h>

NSString *
SMKVideoAspect( float vidWidth, float vidHeight );

NSString *
SMKShortByteSize( NSUInteger val );

NSArray *
SMKSplitAmpCommaString( NSString * str );

#endif /* ! def SMKCommon_SMKcCommon_h_ */
