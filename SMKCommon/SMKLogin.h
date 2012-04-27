/**
 File:		SMKLogin.h
 Project:	SMKCocoaCommon 
 Desc:
 Notes:
 
 Author(s):   Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
 Created:     01/28/12
 Copyright:   Copyright (c) 2012 Secure Media Keepers
              www.SecureMediaKeepers.com
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

@interface SMKLogin : NSObject

+(NSString *) passKey:(NSString *)item;
+(NSString *) getPassForItem:(NSString *)item user:(NSString *)user;
+(BOOL) setUserPassForItem:(NSString *)item user:(NSString *)user pass:(NSString *)pass;

@end
