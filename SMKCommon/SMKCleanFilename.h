#ifndef SMKCommon_SMKCleanFilename_h
#define SMKCommon_SMKCleanFilename_h
/**
  File:		SMKCleanFilename.h
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):   Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
  Created:     120507
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

#define SMK_CLEANFN_CHARS "/\\?*:;[]"
#define SMK_CLEANFN_REGEX "[/\\\\?*:;\\[\\]]"

#if defined( __OBJC__ )
#import <Foundation/Foundation.h>

NSString *
SMK_CleanFilename( NSString *fn );

void
SMK_CleanMutableFilename( NSMutableString * fn );

#endif
#if defined( __cplusplus )
extern "C" {
#endif

  char * SMKCleanFilename( char * name );
  
#if defined( __cplusplus )
};
#endif


#endif /* ! def SMKCommon_SMKCleanFilename_h */
