//
// File:        StringUpper.C
// Project:	StlUtils ()
// Desc:        
//
//    Convert all lowercase characters (a-z) to uppercase (A-Z).
//    Returns str.
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     05/06/95 11:59 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "StringUtils.hh"
#include <cstddef>
#include <cctype>

STLUTILS_FUNCT_VERSION(
  StringUpper,
  "$Id$ " );

char *
StringUpper( char * str, size_t len )
{
  if( len != NPOS )
    {
      const char * end = str + len;
      for( char * s = str; s < end; s++ )
	if( islower(*s) )  *s = toupper( *s );
    }
  else
    {
      for( char * s = str; *s; s++ )
	if( islower(*s) ) *s = toupper( *s );
    }
  return( str );
}

//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:21  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:43  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:03  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:53  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1996/11/24 19:08:41  houghton
// Removed support for short filenames.
//
// Revision 3.1  1996/11/14 01:24:20  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:32:30  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.1  1995/11/10 12:41:14  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:51  houghton
// Ports and Version ID changes
//
//
