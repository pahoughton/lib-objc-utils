/**
  File:		File.c
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):   ___FULLUSERNAME__ <Paul.Houghton@SecureMediaKeepers.com>
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
#include <stdio.h>
#include <inttypes.h>

#include "SMK_CleanFilename.h"

char * SMK_CleanFilename( char * fn )
{
  if( fn[0] == '.' ) {
    fn[0] = '_';
  }
  for( char * them = fn; *them; ++ them ) {
    for( const char * rval = SMK_CLEANFN_CHARS; *rval; ++ rval ) {
      if( *them == *rval ) {
        *them = '_';
      }
    }
  }
  return fn;
}
