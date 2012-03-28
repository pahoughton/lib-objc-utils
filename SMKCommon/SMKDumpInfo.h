#ifndef _SMKDumpInfo_hh_
#define _SMKDumpInfo_hh_
/**
   File:        DumpInfo.hh
   Project:	StlUtils ()
   Desc:        
  
    Most of my classes have a method called dumpInfo that is
    used to dump the entire contents of the instance to an
    ostream. This is mostly used for debuging.
  
    The DumpInfo<T> template class makes it easier to use the
    dumpInfo methdod. To use it, your class must have a the
    a 'ostream & dumpInfo( ostream &, const char * , bool )' method
    that dumps an instance to the stream in a readable form.
    The DumpInf<T> object can only be instaciated by the
    class specified as 'T' and only has a toStream method.
    
    A class that uses this should return an instance that can
    then be inserted (i.e. <<) into an ostream. Please see the
    example.
  
    Example:
  	
  	class MyClass
  	{
  	public:
  	  ostream & dumpInfo( ostream &	    dest,
  			      const char *  prefix = "    ",
  			      bool	    showVer = true ) const;
  	
  	  inline
  	  DumpInfo<MyClass> dump( const char *  prefix = "    ",
  				  bool		showVer = true ) const;
  	
  	}
  	
  	inline
  	DumpInfo<MyClass>
  	MyClass::dump( const char * prefix, bool showVer )
  	{
  	  return( DumpInfo<MyClass>( *this, prefix, showVer ) );
  	}
  	
  	// So Now you can do the follwing
  
  	MyClass obj;
  	
  	cerr << obj.dump() << endl;
  	
  	// Without dump info you would have to
  
  	dumpInfo( cerr ) << endl; 
  
  
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     12/08/96 07:46
  
   Revision History: (See end of file for Revision Log)
  
   $Id$ 
  
**/
#include <SMKConfig.hh>
#include <iostream>

template< class T >
class DumpInfo
{

public:
  inline ostream &	    toStream( ostream & dest ) const {
    return( obj.dumpInfo( dest, prefix, showVer ) ); };

  inline DumpInfo( const T & dumpObj, const char * pre, bool ver )
    : obj( dumpObj ), prefix( pre ), showVer( ver ) {};
  
protected:

  // friend T;
  
  const T &	obj;
  const char *	prefix;
  bool		showVer;
  
};

template< class T >
inline
ostream &
operator << ( ostream & dest, const DumpInfo<T> & src )
{
  return( src.toStream( dest ) );
}



/**  
   Detail Documentation
  
    Data Types: - data types defined by this header
  
    	DumpInfo	class
  
    Constructors:
  
    	DumpInfo( );
  
    Destructors:
  
    Public Interface:
  
  	virtual ostream &
  	toStream( ostream & dest ) const;
  	    output class as a string to dest (used by operator <<)
  

    Protected Interface:
  
    Private Methods:
  
    Associated Functions:
  
  	inline
    	ostream &
    	operator <<( ostream & dest, const DumpInfo & src );
  
   Example:
  
   See Also:
  
   Files:
  
   Documented Ver:
  
   Tested Ver:
**/
  
#endif // ! def _SMKDumpInfo_hh_ 

