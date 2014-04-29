#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <sstream>

#include <vector>
#include <map>
#include <string>
#include "lib/set.h"
#include "webpage/WebPage.h"

using namespace std;

void pageRank( set<WebPage> & allPages );

int main( int argc, char* argv[] )
{
}

void pageRank( Set<WebPage*> & allPages )
{
	Set<WebPage*> T = allPages;
	
	// First need to find amount of all webpages
	int amtPages = allPages.size();
	
	// Damping factor value
	float dampFactor = 0.85;
	
	// Lastly, map each site with a list of scores added to them from outgoing links
	map< string, map< string, float> > pageRankMap;
	
	// Need a vector to store the new values of pageRank
	map< WebPage*, float > newPageRank;
	
	// Loop through all pages in set T to calculate new pageRank
	for (WebPage* w : T) {
		// If T has outgoing pages, loop through them all
		if ( w->allOutgoingLinks().size() > 0 ) {
			// Find weight distribution of all outgoing links
			float weightDistrib = 1 / w->allOutgoingLinks().size();
			// Loop to calculate contribution to pageRank vector for outgoing links
			for ( WebPage* wOut : w->allOutgoingLinks() ) {
				newPageRank[ wOut ] += ( weightDistrib * dampFactor ) * w->getPageRank();
			}
			// Loop to calculate contribution to pageRank vector from pages not linked to
			for ( WebPage* w2 : T ) {
				newPageRank[ w2 ] += (1 - dampFactor) / amtPages * w->getPageRank();
			}
		}
		// Otherwise T has no outgoing pages, 
		else {
			// If T has no outgoing pages, equal contribution is added to each element
			// of the final pageRank vector
			// Find weight distribution for all links
			float weightDistrib = 1 / w->allOutgoingLinks().size();
			// Loop to calculate contribution to pageRank vector from all pages
			for ( WebPage* wOut : T ) {
				newPageRank[ wOut ] += ( weightDistrib * dampFactor + (1 - dampFactor)/amtPages ) * w->getPageRank();
			}
		}
	}
	
	// Insert contents of newPageRank into original pages
	for (WebPage* w : T) {
		w->setPageRank( newPageRank[w] );
		cout << "New pageRank of webpage: " << w->filename() << " is " << w->getPageRank() << endl;
	}
	
}