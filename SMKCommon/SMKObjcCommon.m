//
//  SMKCommon.m
//  SMKCommon
//
//  Created by Paul Houghton on 2/22/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import "SMKObjcCommon.h"

NSString * SMKShortByteSize( NSUInteger val ) 
{
    float sz = val;
    float kb = 1024;
    float mb = (kb * kb);
    float gb = (mb * kb);
    if( sz > gb  ) {
        return [[NSString alloc] initWithFormat:
                @"%.02f GB",sz / gb];
    } else if( sz > mb ) {
        return [[NSString alloc] initWithFormat:
                @"%.02f MB",sz / mb];
    } else if( sz > kb ) {
        return [[NSString alloc] initWithFormat:
                @"%.02f KB",sz / kb];
    } else {
        return [[NSString alloc] initWithFormat:
                @"%d",val];    
    }
}

NSArray *
SMKSplitAmpCommaString( NSString * str )
{
  NSString * alistStr = str;
  NSArray * alist = [alistStr componentsSeparatedByString:@" & "];
  if( [alist count] > 1 ) {
    NSArray * a0list = [[alist objectAtIndex:0] componentsSeparatedByString:@", "];
    NSArray * a1list = [[alist objectAtIndex:1] componentsSeparatedByString:@", "];
    if( [a0list count] > 1 || [a1list count] > 1 ) {
      return [a0list arrayByAddingObjectsFromArray:a1list];
    }
  } else {
    alist = [alistStr componentsSeparatedByString:@", "];
  }
  return alist;  
}

@implementation SMKCommon

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

@end
