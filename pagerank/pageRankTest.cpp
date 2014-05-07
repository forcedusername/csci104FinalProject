#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <sstream>

#include <vector>
#include <map>
#include <string>
#include "lib/setSTL.h"
#include "webpageSTL.h"

using namespace std;

void pageRank(Set<WebPage*, WebPtr_compare> & allPages );

int main( int argc, char* argv[] )
{
	map <string, WebPage*> pages;
	
	string query ("no");
	WebPage* next= new WebPage (argv [1]);
	//next->count_words (query);
	next->rank=0.0;
	
	string file (argv [1]);
	
	pages.insert (pair<string, WebPage*>( file, next));
	
	WebPage* faster= new WebPage (argv [2]);
	//faster->count_words (query);
	faster->rank=0.0;
	
	string next_file (argv [2]);
	pages.insert (pair<string, WebPage*> (next_file, faster));
	
	
	WebPage* newer= new WebPage (argv [3]);
	newer->rank=0.0;
	
	string newest_file (argv [3]);
	pages.insert (pair<string, WebPage*> (newest_file, newer));
	
	next->parse (file, pages);
	faster->parse (next_file, pages);
	newer->parse (newest_file, pages);
	
	cout<<"counting next."<<endl;
	next->count_words (query);
	
	cout<<"counting faster."<<endl;
	faster->count_words (query);
	
	cout<<"Counting newer."<<endl;
	newer->count_words (query);
	
	
	Set <WebPage*, WebPtr_compare> news;
	news.insert (next);
	news.insert (faster);
	pageRank (news);
	
	Set <WebPage*, WebPtr_compare>::iterator points;
	
	for (points=news.begin(); points!=news.end(); points++){
		cout<<"the page ranks are: "<<endl;
		cout<<"for "<<(*points)->filename()<<" : are "<<(*points)->rank<<endl;
	}


	return 0;
}

void pageRank( Set<WebPage*, WebPtr_compare> & allPages )
{
	Set<WebPage*, WebPtr_compare> T = allPages;

	// First need to find amount of all webpages
	int amtPages = allPages.size();
	cout<<"Amt pages is: "<<amtPages<<endl;
	// Damping factor value
	float dampFactor = 0.85;

	// Lastly, map each site with a list of scores added to them from outgoing links
	map< string, map< string, float> > pageRankMap;

	float totalBold = 0.0;
	float totalHeader = 0.0;
	
	// Set the default page rank of each page
	// Also accumulate the total amount of bold and headers for the search term
	Set<WebPage*, WebPtr_compare>::iterator w;
	for (w=T.begin();w!=T.end();w++) {
		double size;
		size=T.size();
		(*w)->setPageRank(1.0/size);
		
		totalBold += (*w)->get_bold();
		cout<<"Total bold is: "<<totalBold<<endl;
		totalHeader += (*w)->get_headers();
		cout<<"Total header is: "<<totalHeader<<endl;
	}
	
	cout<<"total bolds: "<<totalBold<<endl;
	cout<<"total headers: "<<totalHeader<<endl;
	
	// Calculate total dampFactor score modifier
	float dampModMax = 25.0;
	float totalScore = totalBold + totalHeader * 3.0;
	cout<<"total score is: "<<totalScore<<endl;
	float dampModifier;
	if ( totalScore >= dampModMax ) {
		dampModifier = 0.9999;
	}
	else {
		dampModifier = totalScore / dampModMax;
	}
	cout<<"Damp modifier is: "<<dampModifier<<endl;
	
	// Modifier for the damp factor
	float newDampFactor = ( 1 - dampFactor ) * dampModifier + dampFactor;
	cout<<"new damp factor: "<<newDampFactor<<endl;
	
//	newDampFactor= dampFactor;
	for (int i = 0; i < 30; i++) {
	    // Need a vector to store the new values of pageRank
	    map< WebPage*, float > newPageRank;
	    for (map<WebPage*, float>::iterator it = newPageRank.begin(); it != newPageRank.end(); ++ it)
	      {
			it->second = 0.0;
	      }

	    // Loop through all pages in set T to calculate new pageRank
		
		Set<WebPage*, WebPtr_compare>::iterator s;
	    for (s=T.begin();s!=T.end();s++) {
			//cout<<"entering the t for loop."<<endl;
	      // If T has outgoing pages, loop through them all
	      Set<WebPage*, WebPtr_compare> outIntersect = T.setIntersection((*s)->allOutgoingLinks());
		  cout<<"out intersect size is: "<<outIntersect.size()<<endl;
	      if (outIntersect.size() > 0 ) {
			cout<<"entering if statement"<<endl;
			// Find weight distribution of all outgoing links
			float weightDistrib;
			weightDistrib= 1.0 / outIntersect.size();
			
			// Loop to calculate contribution to pageRank vector for outgoing links
			Set<WebPage*, WebPtr_compare>::iterator wOut;
			for (wOut=outIntersect.begin();wOut!=outIntersect.end();wOut++) {
			  
			  newPageRank[ (*wOut) ] += ( weightDistrib * newDampFactor ) * (*s)->getPageRank();
			}
			// Loop to calculate contribution to pageRank vector from pages not linked to
			Set<WebPage*, WebPtr_compare>::iterator w2;
			for (w2=T.begin();w2!=T.end();w2++) {
			
			  newPageRank[ (*w2) ] += (1.0 - newDampFactor) / amtPages * (*s)->getPageRank();
			  cout<<"New page rank is: "<<newPageRank [ (*w2)]<<endl;
			}
	      }
	      // Otherwise T has no outgoing pages, 
		  
	      else {
			// If T has no outgoing pages, equal contribution is added to each element
			// of the final pageRank vector
			// Find weight distribution for all links
			//cout<<"out interesect size is: "<<outIntersect.size()<<endl;
			float size=T.size();
			cout<<"T size is: "<<size<<endl;
			float weightDistrib = 1.0 / size;
			// Loop to calculate contribution to pageRank vector from all pages
			
			Set<WebPage*, WebPtr_compare>::iterator wOut;
			for (wOut=T.begin();wOut!=T.end();wOut++) {
			  newPageRank[ (*wOut) ] += weightDistrib* (*s)->getPageRank();
			  cout<<"new page rank in for loop: "<<newPageRank [ (*wOut)];
			  //( weightDistrib * dampFactor + (1 - dampFactor)/amtPages ) * w->getPageRank();
			}
	      }
	    }
		//cout<<"New damp factor is: "<<newDampFactor<<endl;

	    // Insert contents of newPageRank into original pages
	    Set<WebPage*, WebPtr_compare>::iterator wOut;
		for (wOut=T.begin();wOut!=T.end();wOut++) {
	      (*wOut)->setPageRank( newPageRank[(*wOut)] );
		  //cout<<"New Page Rank for: "<<(*wOut)->filename()<<" is: "<<(*wOut)->rank<<endl;

	    }
	}
}