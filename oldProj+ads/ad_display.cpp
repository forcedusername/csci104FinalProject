
/*
#include "ad_display.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

vector <advertiserBid>& ad_display::match_ads () {
	unsigned int i= 0;
	//unsigned int j=0;
	vector <advertiserBid> match_query;
	while (i<ad_bank.size()){
		if (ad_bank [i].word==queryVector [0]) //from search app
		{
			match_query.push_back (ad_bank [i]);
		}
		i++;
		//j++;
	}
	
	if (queryVector.size()>1){
		for (unsigned int w=0; w<ad_bank.size();w++){
			if (ad_bank [w].word==queryVector [1]){
				vector <advertiserBid>::iterator temp;
				temp= find (match_query.begin(), match_query.end(), ad_bank [w]);
				if (temp==match_query.end()){
					match_query.push_back (ad_bank [w]);//this means no copy of ad bank [w] exists so just add and go
					continue;
				}
				else if (temp!=match_query.end()&& temp->bid>ad_bank [w].bid){
					continue; //this means you've already added the ad and the added version is >than this version
				}
				else {
					match_query.erase (temp);
					match_query.push_back (ad_bank [w]);
				}
				
			}
		}
	
	}
	
	return match_query;
}

vector <advertiserBid>& ad_display::sort_ads (vector <advertiserBid> &matching){
	//so what's the plan? you sort from highest to lowest all the ads
	
//	sort (matching.begin(), matching.end(), sort_bid);
	make_heap (matching.begin(), matching.end());
	cout<<"Given."<<endl;
	//you have comparator object so this should work
	sort_heap (matching.begin(), matching.end());
	
	return matching;
}
*/
