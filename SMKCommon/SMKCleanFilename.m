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

#import "SMKCleanFilename.h"
#import "SMKException.h"

static NSRegularExpression * fnCleanRegex = nil;

NSString * SMKCleanFilename( NSString * name )
{

  if( fnCleanRegex == nil ) {
    NSError * err = nil;
    fnCleanRegex = [[NSRegularExpression alloc]
                    initWithPattern:@SMK_CLEANFN_REGEX
                    options:0
                    error:&err];
    if( fnCleanRegex == nil || err != nil ) {
      SMKThrow(@"Error %@ patt %s",err,SMK_CLEANFN_REGEX);
    }
  }
  
  NSString * clean
  = [fnCleanRegex stringByReplacingMatchesInString: name
                                           options: 0
                                             range: NSMakeRange(0, name.length )
                                      withTemplate: @"_"];

  
  return (clean.length
          ? [clean stringByReplacingOccurrencesOfString:@"."
                                          withString:@"_"
                                             options:0
                                               range:NSMakeRange(0, 1)]
          : clean );
}

void SMKCleanMutableFilename( NSMutableString * name )
{
  if( fnCleanRegex == nil ) {
    NSError * err = nil;
    fnCleanRegex = [[NSRegularExpression alloc]
                    initWithPattern:@SMK_CLEANFN_REGEX
                    options:0
                    error:&err];
    if( fnCleanRegex == nil || err != nil ) {
      SMKThrow(@"Error %@ patt %s",err,SMK_CLEANFN_REGEX);
    }
  }
  
  [fnCleanRegex replaceMatchesInString: name
                               options: 0
                                 range: NSMakeRange(0, name.length)
                          withTemplate: @"_"];
  if( name.length ) {
    [name replaceOccurrencesOfString: @"."
                          withString: @"_"
                             options: 0
                               range: NSMakeRange(0, 1)];
  }
    
}
