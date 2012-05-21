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


#import <Foundation/Foundation.h>
#include "SMK_CleanFilename.h"

NSString *
SMKCleanFilename( NSString *fn );

void
SMKCleanMutableFilename( NSMutableString * fn );

#endif /* ! def SMKCommon_SMKCleanFilename_h */
