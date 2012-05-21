#ifndef SMKCommon_SMK_Aspect_h
#define SMKCommon_SMK_Aspect_h
/**
  File:		SMK_Aspect.h
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
  const char * SMKAspectString( SMKImgAspect asp );
  SMKImgAspect SMKAspect( float w, float h );
#if defined( __cplusplus )
};
#endif


#endif /* ! def SMKCommon_SMK_Aspect_h */
