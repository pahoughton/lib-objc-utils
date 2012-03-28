#ifndef _SMKStrStreambuf_hh_
#define _SMKStrStreambuf_hh_
/**
   File:        SMKStrStreambuf.hh
   Project:	SMKCommon
   Desc:        
  
    Defines the streambuf used by Str.
  
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     05/30/95 11:09
  
   Revision History: (See end of file for Revision Log)
  
    $Author$ 
    $Date$ 
    $Name$ 
    $Revision$ 
    $State$ 
  
   $Id$ 
**/
     
#include "SMKConfig.h"
#include <cstddef>
#include <sstream>


#if defined( SMK_DEBUG )
#define inline
#endif

class SMK_CLASS_T SMKStr;
class SMK_CLASS_T SMKSubStr;

class SMK_CLASS_T SMKStrStreambuf : public stringbuf
{

public:
  
  inline size_t	    	plen(void) SMK_STRBUF_CONST_RDBUF;
  inline size_t	    	psize(void) SMK_STRBUF_CONST_RDBUF;
  inline const char * 	cstr(void);  

  void			readPrep( void );
  
  const char *		getClassName( void ) const;
  const char *		getVersion( bool withPrjVer = true ) const;
  
  ostream &		dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true );


  static const SMKClassVersion version;
  
private:

#if defined( SMK_STRBUF_PBASE )
  char * pbase( void ) { return( base() ); }
#endif
  
  inline const char * 	strbase( void ) SMK_STRBUF_CONST_RDBUF;
  
  friend class SMKStr;
  friend class SMKSubStr;

};

#if !defined( inline )
#include <SMKStrStreambuf.ii>
#else
#undef inline
#endif
/**
    Quick Start: - short example of class usage
  
    Data Types: - data types defined by this header
  
    	SMKStrStreambuf	class
  
    Constructors:
  
    	SMKStrStreambuf( );
  
    Destructors:
  
    Public Interface:
  
    	size_t
    	plen(void) STR_CONST_RDBUF;
  
    	size_t
    	psize(void) STR_CONST_RDBUF;
  
    	const char *
    	cstr(void);  
  
    	virtual const char *
    	getClassName( void ) const;
    	    Return the name of this class (i.e. SMKStrStreambuf )
  
    	virtual Bool
    	good( void ) const;
    	    Returns true if there are no detected errors associated
    	    with this class, otherwise FALSE.
  
    	virtual const char *
    	error( void ) const
    	    Returns as string description of the state of the class.
  
    Protected Interface:
  
    Private Methods:
  
    Other Associated Functions:
  
    	ostream &
    	operator <<( ostream & dest, const SMKStrStreambuf & obj );
  
   Revision History:
**/

#endif // ! def _SMKStrStreambuf_hh_ 
