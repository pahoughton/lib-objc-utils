/**
  File:		StlUtilsLogTie.m
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):   Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
  Created:     4/25/12
  Copyright:   Copyright (c) 2012 Secure Media Keepers. All rights reserved.
               All Rights Reserved.
	       
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Revision$
    $Name$
    $State$

  $Id$

**/

#import "StlUtilsLogTie.h"
#import "SMKLogger.h"
#import "LibLog.hh"
#import "NSFileHandleStreamBuf.h"

@implementation StlUtilsLogTie
+(void)tieToSMKLogger:(SMKLogger *)logger
{
  LogLevel::Level  outLvl = LogLevel::None;
  
  switch ( logger.outLogLevel ) {
    case SMK_LOG_DEBUG:
      outLvl |= LogLevel::Debug;
    case SMK_LOG_INFO:
      outLvl |= LogLevel::Info;
    case SMK_LOG_WARN:
      outLvl |= LogLevel::Warn;
    case SMK_LOG_ERROR:
      outLvl |= LogLevel::Error;
      break;
      
    default:
      break;
  }
  std::ostream * tieOStream;
  tieOStream = new std::ostream( new  NSFileHandleStreamBuf( logger.logFile ));
  _LibLog = new Log( *tieOStream, outLvl );
  _LibLog->tieCommonLogger();
}

@end


