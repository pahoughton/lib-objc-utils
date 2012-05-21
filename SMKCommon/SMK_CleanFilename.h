#ifndef SMKCommon_SMK_CleanFilename_h
#define SMKCommon_SMK_CleanFilename_h
/**
  File:		SMK_CleanFilename.h
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

#define SMK_CLEANFN_CHARS "/\\?*:;[]"
#define SMK_CLEANFN_REGEX "[/\\\\?*:;\\[\\]]"

#if defined( __cplusplus )
extern "C" {
#endif

  char *
  SMK_CleanFilename( char * fn );

#if defined( __cplusplus )
};
#endif


#endif /* ! def SMKCommon_SMK_CleanFilename_h */
