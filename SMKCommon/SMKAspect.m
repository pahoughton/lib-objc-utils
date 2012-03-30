/**
  File:		SMKAspect.m
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):    Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
  Created:      120312  07:28
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
#import "SMKcCommon.h"

NSString * SMKVideoAspect( float vidWidth, float vidHeight )
{
    const char * aspect = NULL;
    char aspRatioStr[16];
    SMKImgAspect asp = SMKAspect(vidWidth, vidHeight);
    if( asp == SMK_ASPECT_UNKNOWN ) {
        sprintf( aspRatioStr, "(%1.2f)", vidWidth / vidHeight );
        aspect = aspRatioStr;
    } else {
        aspect = SMKAspectString(asp);
    }
    
    return [[NSString alloc] initWithUTF8String:aspect];
}
