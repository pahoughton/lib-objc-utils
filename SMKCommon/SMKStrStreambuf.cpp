/**
   File:        StrStreambuf.C
   Project:	StlUtils ()
   Desc:        
  
    Compiled sources for StrStreambuf.
    
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     05/30/95 11:32 
  
   Revision History: (See end of file for Revision Log)
  
    $Author$ 
    $Date$ 
    $Name$ 
    $Revision$ 
    $State$ 
  
   $Id$ 
**/
#include "SMKStrStreambuf.h"

#if defined( SMK_DEBUG )
#include "SMKStrStreambuf.ii"
#endif

SMK_VERSION(
  SMKStrStreambuf,
  "$Id$ " );

void
SMKStrStreambuf::readPrep( void )
{
  if( egptr() < pptr() ) {
    setg( gptr(), gptr(), pptr() );
  }
}

const char *
SMKStrStreambuf::getClassName( void ) const
{
  return( "SMKStrStreambuf" );
}

ostream &
SMKStrStreambuf::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  )
{
  if( showVer )
    dest << SMKStrStreambuf::getClassName() << ":\n"
	 << SMKStrStreambuf::getVersion() << '\n';

  dest << prefix << "length:  " << plen() << '\n'
#if defined( SMK_HAVE_STRBUF_BASE )
       << prefix << "base():  " << (void *) base() << '\n'
#endif
#if defined( SMK_HAVE_STRBUF_EBUF )
       << prefix << "ebuf():  " << (void *) ebuf() << '\n'
#endif
       << prefix << "pbase(): " << (void *) pbase() << '\n'
       << prefix << "pptr():  " << (void *) pptr() << '\n'
       << prefix << "epptr(): " << (void *) epptr() << '\n'
       << prefix << "eback(): " << (void *) eback() << '\n'
       << prefix << "gptr():  " << (void *) gptr() << '\n'
       << prefix << "egptr(): " << (void *) egptr() << '\n'
       << prefix << "n - b:   " << pptr() - pbase() << '\n'
       << prefix << "string:  '" << (void *)cstr() << "'\n"
       << prefix << "pbase(): " << (void *) pbase() << '\n'
       << prefix << "pptr():  " << (void *) pptr() << '\n'
       << prefix << "length:  " << plen() << '\n'
       << prefix << "size:    " << psize() << '\n'
    ;

  return( dest );
}

const char *
SMKStrStreambuf::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}

