/**
  File:		Incremental.m
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):    Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
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
#import "Incremental.h"

@implementation Incremental
@synthesize value;
@synthesize increment;

- (id)initValue:(NSInteger)val
{
    self = [super init];
    if (self) {
        [self setValue:val];
        [self setIncrement:1];
    }
    return self;
}
- (id)initValue:(NSInteger)val incr:(NSInteger)inc 
{
    self = [super init];
    if (self) {
        [self setValue:val];
        [self setIncrement:inc];
    }
    return self;
}
- (id)init {
    self = [super init];
    if (self) {
        [self setValue:0];
        [self setIncrement:1];
    }
    return self;
}
-(NSInteger)incr
{
    value+=increment;
    return value;
}
-(NSInteger)decr
{
    value -= increment;
    return value;
}

-(NSString *)description
{
    return [[NSString alloc]initWithFormat:@"%ld",value];
}
@end
