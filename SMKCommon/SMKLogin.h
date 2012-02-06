//
//  SMKLogin.h
//  Dig-It
//
//  Created by Paul Houghton on 1/28/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SMKLogin : NSObject

+(NSString *) passKey:(NSString *)item;
+(NSString *) getPassForItem:(NSString *)item user:(NSString *)user;
+(BOOL) setUserPassForItem:(NSString *)item user:(NSString *)user pass:(NSString *)pass;

@end
