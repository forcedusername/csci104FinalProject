// required headers go here
#ifndef _WebPage
#define _WebPage

//#include "web_crawler.h"
#include "lib/setSTL.h"
#include <map>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include "lib/comparatorsSTL.h"

class WebCrawler;
class WebPage;
class WebPtr_compare {
	public:
		bool operator() (WebPage* const page1, WebPage* const page2);
};

//class string_compare;
//class int_compare;

class WebPage {
	
  friend class WebCrawler;
  //so WebCrawler can access Set Outgoing and Incoming
  
  public:
    WebPage ();    // constructor that creates an empty page
    WebPage (string filename);
      /* constructor that initializes the page from the given file.
         Should throw an exception if the file does not exist
         or points_to other problems. */
    ~WebPage () { };   // destructor
	
	Set<string, string_compare> allWords () const;
      /* Returns a set containing all individual words on the web page. */   

    friend ostream & operator<< (ostream & os, const WebPage & page);
      /* Declares an operator we can use to print the web page. */
	
	Set<WebPage*, WebPtr_compare> allOutgoingLinks () const;
      /* Returns "pointers" to all webpages that this page points_to links to. 
         As discussed above, this could be as a set or via an iterator,
         and it could be as actual pointers, or as strings, 
         or possibly other. */   

    Set<WebPage*, WebPtr_compare> allIncomingLinks () const;
      /* Returns "pointers" to all webpages that link to this page. 
         Same consideration as previous function. */   

    string filename () const;
      /* Returns the filename from which this page was read. */

    /* Based on which overall architecture you choose, you may 
       also need/want some or all of the following functions. */

    void parse (const string &page_filename,  map<string, WebPage*> &pageMap);
      /* actually parses the content of the filename that was passed 
         to the constructor into the object. */
	
	WebPage* getWebPageFromMap(const string &page_filename, map<string, WebPage*> &pageMap);
	//void addIncomingLink (WebPage* start);
      /* Adds a link from start to the current page 
         in the current page's storage. */
	void count_words (string query);
	
	double rank;
	void setPageRank (float next) {rank=next;}
	double getPageRank () {return rank;}
	//void addOutgoingLink (WebPage* target); 
      /* Adds a link from the current page to the target
         in the current page's storage. */
	float get_bold () {return num_bold;}
	float get_headers () {return num_headers;}
	
  private:
	Set<string, string_compare> topSecret_stuff;
    vector <string>              lineVector;
    stringstream                ssWebPage;
    string                      page_filename;
	
	Set<WebPage*, WebPtr_compare> points_to; //outgoing	
	Set<WebPage*, WebPtr_compare> connected_to; //incoming
    // you get to decide what goes here.
	float num_bold;
	float num_headers;
};

  struct AlphaStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    }
  };
  
struct RankComp {
  bool operator() (const WebPage* x, const WebPage* y) const
  {
    return ((x->rank) > (y->rank));
  }
};

#endif
