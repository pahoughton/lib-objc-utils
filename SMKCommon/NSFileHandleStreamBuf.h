#ifndef __SMKCommon__NSFileHandleStreamBuf__
#define __SMKCommon__NSFileHandleStreamBuf__
/**
 File:		NSFileHandleStreamBuf.h
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

#import <Foundation/Foundation.h>
#include <iostream>

class NSFileHandleStreamBuf : public std::streambuf
{
public:
  NSFileHandleStreamBuf( NSFileHandle * tieFh );

protected:
  virtual int
  sync();
 
  virtual std::streamsize
  xsputn(const char_type * __s, std::streamsize __n);

public:
  NSFileHandle * mNsfh;
  
};

#endif /* defined(__SMKCommon__NSFileHandleStreamBuf__) */
