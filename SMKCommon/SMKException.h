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
#include <stdio.h>

#define SMKThrow( desc_, ... ) throw SMKException( __FILE__, __LINE__, desc_, ##__VA_ARGS__ )

class SMKException : public std::exception
{
public:
  
  inline SMKException( const char * file,
                      int           line,
                      const char *  descFmt,
                      ... ) :
  mFileName(file), mFileLine( line ), mDesc( 0 ) {
    va_list ap;
    va_start( ap, descFmt );
    vasprintf( &mDesc, descFmt, ap );
    va_end( ap );
  };
  
  inline virtual ~SMKException( void ) throw () {
    if( mDesc ) free( mDesc );
  };
  
  inline virtual const char * what( void ) {
    return mDesc;
  };
  
  const char *  mFileName;
  unsigned int  mFileLine;
  char *        mDesc;
  
protected:
private:
};

inline std::ostream & operator << ( std::ostream & dest, const SMKException & obj )
{
  dest << basename( obj.mFileName ) << ':' << obj.mFileLine << ' ' << obj.mDesc << std::endl;
  return dest;
}
#endif

#endif /* ! def SMKCommon_SMKException_h_ */

