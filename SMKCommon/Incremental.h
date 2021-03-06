/**
  File:		Incremental.h
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):    Paul Houghton  ___EMAIL___ <Paul.Houghton@SecureMediaKeepers.com>
  Created:      2/22/12  5:29 AM
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
#import <Foundation/Foundation.h>

@interface Incremental : NSObject
@property NSInteger value;
@property NSInteger increment; // defaults to 1
-(id)initValue:(NSInteger)value;
-(id)initValue:(NSInteger)value incr:(NSInteger)incr;
-(NSInteger)incr;
-(NSInteger)decr;

@end
