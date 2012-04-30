//
//  SMKCommonTests.m
//  SMKCommonTests
//
//  Created by Paul Houghton on 2/22/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import "SMKCommonTests.h"
#import "Incremental.h"
#import "SMKLogger.h"
#import "SMKException.h"
#import "SMKLogin.h"
#import "TMDbQuery.h"

@implementation SMKCommonTests

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testExample
{
  /*
  SMKException * ex = [[SMKException alloc] init];
  STAssertNotNil(ex, @"ex not nil");
  */
  SMKLogin * smkLogin = [[SMKLogin alloc]init];
  STAssertNotNil(smkLogin, @"smkLogin nil");
  
  SMKLogger * logger = [[SMKLogger alloc]initToStderr];
  STAssertNotNil( logger, @"logger nil");
  
  Incremental * incr = [[Incremental alloc]init];
  STAssertNotNil( incr , @"incr");
  [incr incr];
  STAssertEquals([incr value], 1, @"value");

  for( int i = 0; i < 10000; ++ i ) {
    SMKLogDebug(@"test this logger with a loop %d",i);
  }
    
}

@end
