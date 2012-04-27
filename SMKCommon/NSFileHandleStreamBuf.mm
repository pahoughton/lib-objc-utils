/**
 File:		NSFileHandleStreamBuf.cpp
 Project:	SMKCommon
 Desc:
 
 
 
 Notes:
 
 Author(s):    Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
 Created:      4/26/12
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

#include "NSFileHandleStreamBuf.h"

NSFileHandleStreamBuf::NSFileHandleStreamBuf(
  NSFileHandle * tieFh )
:mNsfh(tieFh)
{
}

int
NSFileHandleStreamBuf::sync()
{
  [mNsfh synchronizeFile];
  return 0;
}

std::streamsize
NSFileHandleStreamBuf::xsputn(const NSFileHandleStreamBuf::char_type * s, std::streamsize n)
{
  [mNsfh writeData:[NSData dataWithBytes: s length: n ]];
  return n;
}
