//
// File:        StringFirstNotOf.C
// Project:	Clue
// Desc:        
//
//  Compiled sources for StringFirstNotOf
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     08/11/97 08:47
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//


#include "StringUtils.hh"
#include <cstddef>
#include <cstring>


CLUE_FUNCT_VERSION(
  StringFirstNotOf,
  "$Id$" );

size_t
CLUE_FUNCT_T
StringFirstNotOf(
  const char *  haystack,
  size_t        hayLen,
  const char *  needle,
  size_t        needleLen
  )
{
  // check for valid input params
  if( ! haystack ||
      ! hayLen	 ||
      ! needle   ||
      ! needleLen )
    return( NPOS );
  
  size_t    nLen = (needleLen != NPOS) ? needleLen : strlen( needle );
  size_t    hLen = (hayLen != NPOS ) ? hayLen : strlen( haystack );

  if( ! hLen || ! nLen ) return( NPOS );
  
  register const char *     hBeg = haystack;
  register const char *	    nBeg = needle;
  
  const char * hEnd = hBeg + hLen;
  const char * nEnd = nBeg + nLen;

  for( const char * h = hBeg; h < hEnd; h++ )
    {
      const char * n = nBeg;
      for( ; n < nEnd ; n++ )
	{
	  if( *h == *n )
	    {
	      break;
	    }
	}
      if( n == nEnd )
	{
	  return( h - hBeg );
	}
    }

  return( NPOS );
}
  


// Revision Log:
//
// $Log$
// Revision 3.1  1997/08/12 11:10:33  houghton
// Initial Version.
//
//