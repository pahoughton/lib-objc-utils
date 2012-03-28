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

NSString * SMKVideoAspect( float vidWidth, float vidHeight )
{
    const char * aspect = NULL;
    char aspRatioStr[16];
    float aspRatio = 0;
    aspRatio = vidWidth / vidHeight;
    if( aspRatio < 1.4 ) {
        aspect = "4:3";
    } else if( aspRatio < 1.79 ) {
        aspect = "16:9";
    } else if( aspRatio < 2.0 ) {
        aspect = "1.85:1";
    } else if( aspRatio < 2.6 ) {
        aspect = "2.40:1";
    } else {
        sprintf( aspRatioStr, "(%1.2f)",aspRatio );
        aspect = aspRatioStr;
    }
    return [[NSString alloc] initWithUTF8String:aspRatioStr];
}
