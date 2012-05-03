#ifndef SMKCommon_SMKException_h_
#define SMKCommon_SMKException_h_
/**
  File:		SMKException.h
  Project:	SMKCommon
  Desc:

    
  
  Notes:
    
  Author(s):    Paul Houghton  ___EMAIL___ <Paul.Houghton@SecureMediaKeepers.com>
  Created:      2/22/12  6:01 AM
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
#if defined( __cplusplus )
#include <exception>
#include <iostream>
#include <string>
#include <stdio.h>

#define SMKThrow( desc_, ... ) throw SMKException( __func__, __LINE__, desc_, ##__VA_ARGS__ )

class SMKException : public std::exception
{
public:

  std::string   mDesc;
  char *  mFunct;
  unsigned int  mFileLine;
  // char *        mDesc;
  
  inline SMKException( const char * funct
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

  virtual ~SMKException( void ) throw ();
  
  virtual const char * what( void ) const throw();
  
protected:
private:
};

inline std::ostream & operator << ( std::ostream & dest, const SMKException & obj )
{
  dest << obj.mDesc << std::endl;
  return dest;
}
#elif defined ( __OBJC__)

@interface SMKException : NSException
+(void)setUncaughtHandler;
+(void)raise:(NSString *)name
        file: (const char *) fileName
       funct: (const char *) funcName
        line: (int)          lineNum
       descr: (NSString*)    descr,...;
@end
  
#define SMKThrow( desc_, ... ) [SMKException raise: @"SMKError"  \
                                              file: __FILE__     \
                                             funct: __func__     \
                                              line: __LINE__     \
                                             descr: desc_        \
                                                   ,##__VA_ARGS__]
  
/*  @interface SMKException : NSException
  +(void)raise:(NSString *)fmt, ...;
  
  +(void)raise:(NSString *)name format:(NSString *)format, ...;
  @end
  //throw SMKException( __FILE__, __LINE__, desc_, ##__VA_ARGS__ )
  */

#endif /* def __cplusplus */

#endif /* ! def SMKCommon_SMKException_h_ */

