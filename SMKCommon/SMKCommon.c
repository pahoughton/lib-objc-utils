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

#include "SMKCommon.h"

static const char * SMKAspectStrings[] = {
    "4:3",
    "16:9",
    "1.85:1",
    "2.40:1",
    "UNKNOWN",
    0
};

SMKImgAspect SMKAspect( float w, float h )
{
    SMKImgAspect aspect = SMK_ASPECT_UNKNOWN;
    
    float aspRatio = w / h;
    if( aspRatio < 1.4 ) {
        aspect = SMK_ASPECT_4_3;
    } else if( aspRatio < 1.79 ) {
        aspect = SMK_ASPECT_16_9;
    } else if( aspRatio < 2.0 ) {
        aspect = SMK_ASPECT_1_85;
    } else if( aspRatio < 2.6 ) {
        aspect = SMK_ASPECT_2_40;
    }
    return aspect;
}

const char * SMKAspectString( SMKImgAspect asp ) 
{
    if( SMK_ASPECT_4_3 <= asp && asp <= SMK_ASPECT_UNKNOWN ) {
        return SMKAspectStrings[ asp ];
    }
    return SMKAspectStrings[ SMK_ASPECT_UNKNOWN ];
}

