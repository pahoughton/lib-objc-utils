//
// File:        StringCapitalize.C
// Project:	StlUtils
// Desc:        
//
//    Convert the first lower case alpha (a-z) char of
//    every word to upper case and convert every other
//    character in every word to lower case.
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/06/95 12:03 
//
// Revision History: (See end of file for Revision Log)
//

#include "StringUtils.hh"
#include <cctype>
#include <cstddef>

STLUTILS_FUNCT_VERSION(
  StringCapitalize,
  "$Id$" );

char *
StringCapitalize( char * str, size_t len )
{
  if( len != NPOS )
    {
      const char * end = str + len;
      for( char * s = str; s < end; s++ )
	{
	  int inword = islower(*s);
	  
	  if( inword )
	    *s = toupper( *s );
	  else
	    inword = isupper(*s) || isdigit(*s);
	  
	  if( inword )
	    {
	      for( s++; s < end; s++ )
		{
		  if( isupper(*s) )
		    *s = tolower(*s);
		  else
		    if( ! islower(*s) && ! isdigit(*s) && (*s != '\'' ) )
		      break;
		}
	    }
	}
    }
  else
    {
      for( char * s = str; *s; s++ )
	{
	  int inword = islower(*s);
	  
	  if( inword )
	    *s = toupper( *s );
	  else
	    inword = isupper(*s) || isdigit(*s);
	  
	  if( inword )
	    {
	      for( s++; *s; s++ )
		{
		  if( isupper(*s) )
		    *s = tolower(*s);
		  else
		    if( ! islower(*s) && ! isdigit(*s) && (*s != '\'' ) )
		      break;
		}
	    }
	}
    }
  return( str );
}

//
// Revision Log:
//
// $Log$
// Revision 4.1  1997/09/17 15:12:59  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:50  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1996/11/24 19:04:50  houghton
// Removed support for short filenames.
// Changed include lines from < > to " " for rpm.
//
// Revision 3.1  1996/11/14 01:24:15  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:29:21  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.1  1995/11/10 12:41:09  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:47  houghton
// Ports and Version ID changes
//
