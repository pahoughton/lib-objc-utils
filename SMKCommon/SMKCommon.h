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
#include "SMKConfig.h"
#include "SMKException.h"

typedef enum SMKImgAspect_enum {
    SMK_ASPECT_4_3,  /* 4:3 */
    SMK_ASPECT_16_9, /* 16:9 */
    SMK_ASPECT_1_85, /* 1.85:1 */
    SMK_ASPECT_2_40, /* 2.40:1 */
    SMK_ASPECT_UNKNOWN
} SMKImgAspect;


#if defined( __cplusplus )
extern "C" {
#endif
    SMKImgAspect SMKAspect( float w, float h );
    const char * SMKAspectString( SMKImgAspect asp );
    
#if defined( __cplusplus )
};
#endif


#if defined (__OBJC__)
#import "SMKLogger.h"
#import "Incremental.h"
#import "SMKLogin.h"
#import "SMKCleanFilename.h"
#import "SMK_DateFmts.h"
#endif


#endif /* ! def SMKCommon_SMKcCommon_h_ */
