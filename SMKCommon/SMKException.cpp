//
//  SMKExceptionx.cpp
//  SMKCommon
//
//  Created by Paul Houghton on 4/26/12.
//  Copyright (c) 2012 Secure Media Keepers. All rights reserved.
//

#include "SMKException.h"

SMKException::~SMKException( void ) throw () {
  if( mFunct ) free( mFunct );
};

const char *
SMKException::what() const throw()
{
  return mDesc.c_str();
}
