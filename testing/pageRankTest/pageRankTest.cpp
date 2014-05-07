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

	int totalBold = 0;
	int totalHeader = 0;
	
	// Set the default page rank of each page
	// Also accumulate the total amount of bold and headers for the search term
	for (WebPage* w : T) {
		w->setPageRank(1.0/(T.size()));
		
		totalBold += w->getAmtBold();
		totalHeader += w->getAmtHeader();
	}
	
	// Calculate total dampFactor score modifier
	int dampModMax = 25;
	int totalScore = totalBold + totalHeader * 3;
	float dampModifier;
	if ( totalScore >= dampModMax ) {
		dampModifier = 1.0;
	}
	else {
		dampModifier = (float)totalScore / (float)dampModMax;
	}
	
	// Modifier for the damp factor
	float newDampFactor = ( 1 - dampFactor ) * dampModifier + dampFactor;
	
	for (int i = 0; i < 30; i++) {
	    // Need a vector to store the new values of pageRank
	    map< WebPage*, float > newPageRank;
	    for (map<WebPage*, float>::iterator it = newPageRank.begin(); it != newPageRank.end(); ++ it)
	      {
		it->second = 0.0;
	      }

	    // Loop through all pages in set T to calculate new pageRank
	    for (WebPage* w : T) {
	      // If T has outgoing pages, loop through them all
	      Set<WebPage*> outIntersect = T.setIntersection(w->allOutgoingLinks());
	      if (outIntersect.size() > 0 ) {
			// Find weight distribution of all outgoing links
			float weightDistrib = 1.0 / outIntersect.size();
			
			// Loop to calculate contribution to pageRank vector for outgoing links
			for ( WebPage* wOut : outIntersect ) {
			  
			  newPageRank[ wOut ] += ( weightDistrib * newDampFactor ) * w->getPageRank();
			}
			// Loop to calculate contribution to pageRank vector from pages not linked to
			for ( WebPage* w2 : T ) {
			
			  newPageRank[ w2 ] += (1.0 - newDampFactor) / amtPages * w->getPageRank();
			}
	      }
	      // Otherwise T has no outgoing pages, 
	      else {
			// If T has no outgoing pages, equal contribution is added to each element
			// of the final pageRank vector
			// Find weight distribution for all links
			float weightDistrib = 1.0 / T.size();
			// Loop to calculate contribution to pageRank vector from all pages
			for ( WebPage* wOut : T ) {
			  newPageRank[ wOut ] += weightDistrib*w->getPageRank();
			  //( weightDistrib * dampFactor + (1 - dampFactor)/amtPages ) * w->getPageRank();
			}
	      }
	    }

	    // Insert contents of newPageRank into original pages
	    for (WebPage* w : T) {
	      w->setPageRank( newPageRank[w] );

	    }
	}
}