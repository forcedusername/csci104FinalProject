#ifndef SEARCH_H
#define SEARCH_H
#include "setSTL.h"
#include "comparatorsSTL.h"

#include <map>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include "webpageSTL.h"

class WebPage;
//class WebPtr_compare;

void getQueryVector(string inputLine, vector<string> &queryVector);

class searchApp {
  //friend class pagerank; 
  friend class ad_display;
  public:
    searchApp(string datafileNameIN): datafileName(datafileNameIN) { }

    ~searchApp() { }
    void loadPagesAndParse();
    void searchQuery(const string &query, vector<string> &queryMatch);

    void getPage(const string &filename, string &fileOUT, vector<string> &outLinks, vector<string> &inLinks);
    vector<WebPage*> get_pages(vector<string> queryMatch);
    void sortRank(vector<string>& List);
	void pageRank( Set<WebPage*, WebPtr_compare> & allPages );
  private:
    vector<WebPage *>       webPagePtrList;
    map<string, WebPage*>   pageMap;
    string                  datafileName;
    Set<WebPage*, WebPtr_compare> allPages;
};

#endif // SEARCH_H
