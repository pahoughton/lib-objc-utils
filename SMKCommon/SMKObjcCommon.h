//
//  SMKCommon.h
//  SMKCommon
//
//  Created by Paul Houghton on 2/22/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Incremental.h>
#import <SMKException.h>
#import <SMKLogger.h>
#import <SMKLogin.h>
#import <TMDbQuery.h>

NSString * SMKVideoAspect( float vidWidth, float vidHeight );

NSString * SMKHH_MM_SSFromSeconds( NSInteger secs ); // HH:MM:SS
NSString * SMKHHMMSSFromSeconds( NSInteger secs ); // HHMMSS
NSString * SMKTimeStampShort(void);
NSString * SMKShortByteSize( NSUInteger val ); // 25.03 GB; 145 KB ...

NSArray *
SMKSplitAmpCommaString( NSString * str );

@interface SMKCommon : NSObject

@end
