//
//  SMKCommonTests.m
//  SMKCommonTests
//
//  Created by Paul Houghton on 2/22/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#import "SMKCommonTests.h"
#import "SMKCommon.h"

NSApplication * NSApp = nil;

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

  SMKLogin * smkLogin = [[SMKLogin alloc]init];
  STAssertNotNil(smkLogin, @"smkLogin nil");
  
  SMKLogger * logger = [[SMKLogger alloc]initToStderr];
  STAssertNotNil( logger, @"logger nil");
  */
  Incremental * incr = [[Incremental alloc]init];
  STAssertNotNil( incr , @"incr");
  [incr incr];
  
  
  NSInteger expVal = 1;
  STAssertEquals(incr.value, expVal, @"value");
  
/*
  for( int i = 0; i < 10000; ++ i ) {
    SMKLogDebug(@"test this logger with a loop %d",i);
  }
  */
  NSString * srcFn = @".this: fname [is dirty] / fixit";
  NSString * expFn = @"_this_ fname _is dirty_ _ fixit";
  NSMutableString * mSrcFn = [srcFn mutableCopy];
  
  char * cSrcFn = strdup( srcFn.UTF8String );
  const char * cExpFn = expFn.UTF8String;
  
  cSrcFn = SMKCleanFilename( cSrcFn);
  STAssertTrue(strcmp( cSrcFn, cExpFn) == 0
               ,@"diff '%s' != '%s'"
               ,cSrcFn
               ,cExpFn);
  srcFn = SMK_CleanFilename( srcFn );
  STAssertTrue([srcFn isEqualToString: expFn]
               ,@"diff '%@' != '%@'"
               ,srcFn
               ,expFn );
  NSLog(@"%@",srcFn);
  SMK_CleanMutableFilename( mSrcFn );
  STAssertTrue([mSrcFn isEqualToString: expFn]
               ,@"diff '%@' != '%@'"
               ,mSrcFn
               ,expFn );
}

@end
