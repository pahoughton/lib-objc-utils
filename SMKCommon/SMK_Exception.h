#ifndef SMKCommon_SMK_Exception_h
#define SMKCommon_SMK_Exception_h
/**
  File:		SMK_Exception.h
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):   Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
  Created:     120520
  Copyright:     Copyright (c) 2012 Secure Media Keepers. All rights reserved.
               All Rights Reserved.
	       
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Revision$
    $Name$
    $State$

  $Id$

**/

#include <stdio.h>

#if defined( __cplusplus )

#include <exception>
#include <iostream>
#include <string>

#define SMKThrow( desc_, ... ) throw SMK_Exception( __func__, __LINE__, desc_, ##__VA_ARGS__ )

class SMK_Exception : public std::exception
{
public:
  
  std::string   mDesc;
  char *  mFunct;
  unsigned int  mFileLine;
  // char *        mDesc;
  
  inline SMK_Exception( const char * funct
                      ,int          line
                      ,const char *  descFmt
                      ,... ) :
  mFunct(funct ? strdup( funct ) : 0 )
  ,mFileLine( line )
  {
    va_list ap;
    va_start( ap, descFmt );
    char * tmpDesc;
    vasprintf( &tmpDesc, descFmt, ap );
    va_end( ap );
    char lineNumBuff[ 1024 ];
    snprintf(lineNumBuff, sizeof( lineNumBuff ),":%u ",mFileLine);
    mDesc.append( mFunct );
    mDesc.append( lineNumBuff );
    mDesc.append( tmpDesc );
  };
  
  virtual ~SMK_Exception( void ) throw ();
  
  virtual const char * what( void ) const throw();
  
protected:
private:
};

inline std::ostream & operator << ( std::ostream & dest,
                                   const SMK_Exception & obj )
{
  dest << obj.mDesc << std::endl;
  return dest;
}

#endif

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( __cplusplus )
};
#endif


#endif /* ! def SMKCommon_SMK_Exception_h */
