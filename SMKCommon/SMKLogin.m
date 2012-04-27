/**
 File:		SMKLogin.m
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

#import "SMKLogin.h"
#import "SMKException.h"
#import <Security/Security.h>

@implementation SMKLogin

+(NSString *) passKey:(NSString *) item
{
  NSString * pkey = [NSString stringWithFormat:@"%@.%@.password",
                     [[[NSBundle mainBundle]infoDictionary] valueForKey:@"CFBundleIdentifier"],
                     item ];
  return pkey;
}

+(NSString *) getPassForItem:(NSString *) item user:(NSString *) user;
{
  NSString * pass = nil;
  
  if( user != nil ) {
    NSString * pkey = [SMKLogin passKey:item];
    const char * cpKey = [pkey UTF8String];
    
    const char * cuValue = [user UTF8String];
    
    char * passDest = NULL;
    UInt32 passLen = 0;
    
    OSStatus secRet = SecKeychainFindGenericPassword( NULL,
                                                     (UInt32)strlen(cpKey),
                                                     cpKey,
                                                     (UInt32)strlen(cuValue),
                                                     cuValue,
                                                     &passLen,
                                                     (void**)&passDest,
                                                     NULL );
    
    if( secRet == errSecSuccess ) {
      char tmpPass[1024];
      if( passLen < (sizeof( tmpPass ) - 1 )) {
        memcpy(tmpPass, passDest, passLen );
        tmpPass[passLen] = 0;
        pass = [[NSString alloc] initWithUTF8String:tmpPass];
      } else {
        SMKThrow( @"Password to long" );
      }
    } else {
      CFStringRef ret = SecCopyErrorMessageString( secRet, NULL );
      SMKThrow( @"find error: %@",ret );
      CFRelease(ret);
    }
    if( passDest != NULL ) {
      SecKeychainItemFreeContent(NULL, passDest);
    }
  } else {
    SMKThrow( @"user name required" );
  }
  return pass;
}

+(BOOL) setUserPassForItem:(NSString *)item user:(NSString *)user pass:(NSString *)pass
{
  // FIRST - does it already exist?, if so, delete it.
  {
    if( user != nil ) {
      NSString * pkey = [SMKLogin passKey:item];
      const char * cpKey = [pkey UTF8String];
      
      const char * cuValue = [user UTF8String];
      
      char * passDest = NULL;
      UInt32 passLen = 0;
      SecKeychainItemRef itemRef;
      
      OSStatus secRet = SecKeychainFindGenericPassword( NULL,
                                                       (UInt32)strlen(cpKey),
                                                       cpKey,
                                                       (UInt32)strlen(cuValue),
                                                       cuValue,
                                                       &passLen,
                                                       (void**)&passDest,
                                                       &itemRef );
      
      if( secRet != errSecSuccess
         || (secRet = SecKeychainItemDelete(itemRef)) != errSecSuccess ) {
        CFStringRef ret = SecCopyErrorMessageString( secRet, NULL );
        // Not found is NO big
        // SMKAlert(@"sec find error %@", ret );
        CFRelease(ret);
      }
      if( passDest != NULL ) {
        SecKeychainItemFreeContent(NULL, passDest);
      }
    }
    
  }
  UInt32  ucPassLen = (UInt32)[pass lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
  const char * ucPass = [pass UTF8String];
  
  NSString * pkey = [SMKLogin passKey:item];
  const char * cpKey = [pkey UTF8String];
  
  const char * cuValue = [user UTF8String];
  
  OSStatus secRet = SecKeychainAddGenericPassword ( NULL,
                                                   (UInt32)strlen( cpKey ),
                                                   cpKey,
                                                   (UInt32)strlen( cuValue ),
                                                   cuValue,
                                                   ucPassLen,
                                                   ucPass,
                                                   NULL );
  
  
  if( secRet == errSecSuccess ) {
    return TRUE;
    
  } else {
    CFStringRef ret = SecCopyErrorMessageString( secRet, NULL );
    SMKThrow( @"Add Error: %@",ret );
    CFRelease(ret);
    return FALSE;
  }
}

@end
