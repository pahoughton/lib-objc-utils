//
// File:        StripWhite.C
// Desc:        
//
//  	Remove leading and trailing white space from a string.
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     02/18/95 16:13
//
// Revision History:
//
//  grabed old 'StripSpaces.c' function and added the ability to
//  specifiy white spaces that are to be striped
//
// $Log$
// Revision 1.1  1995/11/05 13:23:40  houghton
// Initaial implementation
//
//

#include "StringUtils.hh"
#include "_Clue.hh"

#include <cstring>

static const char * RcsId =
LIB_CLUE_VERSION
"$Id$";

char *
StripWhite( char * buffer, const char * white, size_t bufSize )
{

  const char *  beg;
  size_t    	len;
  
  if( ! bufSize )
    {
      beg = buffer + strspn( buffer, white );
      len = strlen( buffer );
    }
  else
    {
      size_t i;
      for( i = 0; i < bufSize; i++ )
	{
	  if( ! strchr( white, buffer[i] ) )
	    {
	      break;
	    }
	}
      beg = buffer + i;
      len = bufSize - 1;
    }

  for( ; len; len-- )
    {
      if( ! strchr( white, buffer[len] ) )
	{
	  break;
	}
    }

  memmove( buffer, beg, (len - (beg - buffer)) + 1);
  
  buffer[ (len - (beg - buffer)) + 1 ] = 0;
  return( buffer );
}

      


 
