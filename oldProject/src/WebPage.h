#ifndef WEBPAGE_H_
#define WEBPAGE_H_

#include <iostream>
#include "../lib/Set.h"
#include <deque>
#include <map>
// required headers go here

using namespace std;

class WebPage {
  public:
    WebPage ();    // constructor that creates an empty page
    WebPage (const char* file);
      /* constructor that initializes the page from the given file.
         Should throw an exception if the file does not exist
         or has other problems. */
    ~WebPage ();   // destructor
      Set<WebPage*> allOutgoingLinks () const;
        /* Returns "pointers" to all webpages that this page has links to.
           As discussed above, this could be as a set or via an iterator,
           and it could be as actual pointers, or as strings,
           or possibly other. */

      Set<WebPage*> allIncomingLinks () const;
        /* Returns "pointers" to all webpages that link to this page.
           Same consideration as previous function. */

      string filename () const;
        /* Returns the filename from which this page was read. */

      /* Based on which overall architecture you choose, you may
         also need/want some or all of the following functions. */

      void parse (map<string, WebPage*> & pages);// reference to map of filenames to webpage pointers passed to check for duplicates
        /* actually parses the content of the filename that was passed
           to the constructor into the object. */

      void addIncomingLink (WebPage* start);
        /* Adds a link from start to the current page
           in the current page's storage. */

      void addOutgoingLink (WebPage* target);
        /* Adds a link from the current page to the target
           in the current page's storage. */

    Set<string> allWords () const;
      /* Returns a set containing all individual words on the web page. */

    friend ostream & operator<< (ostream & os, const WebPage & page);
	
      /* Declares an operator we can use to print the web page. */
	  
    float getPageRank() const;
    void setPageRank(const float r);
 deque<string> word_lines; //unparsed lines directly from the file
 

  private:
    // you get to decide what goes here.
       Set<string> all_words;//parsed words, returned by allWOrds()
    const char* _filename;
    Set<WebPage*> outgoing_links;
    Set<WebPage*> incoming_links;
    float pageRank;
};


#endif /* WEBPAGE_H_ */
