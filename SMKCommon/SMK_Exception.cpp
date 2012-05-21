//
//  SMKExceptionx.cpp
//  SMKCommon
//
//  Created by Paul Houghton on 4/26/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#include "SMK_Exception.h"

SMK_Exception::~SMK_Exception( void ) throw () {
  if( mFunct ) free( mFunct );
};

const char *
SMK_Exception::what() const throw()
{
  return mDesc.c_str();
}
