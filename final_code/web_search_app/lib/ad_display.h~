#ifndef AD_H
#define AD_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "stdlib.h"
#include <algorithm>
#include <string>

#include "search.h"

using namespace std;

struct advertiserBid {
	string company;
	string word;
	float bid;
	int clicks;
	
	
	bool operator == (const advertiserBid &other) const{
		
		//only if the same company bids for the same word is this a duplicate
		if (other.word==this->word &&other.company==this->company){
			return true;
		}
		return false;
	}
	
	bool operator < (advertiserBid &other){
		if (this->bid==other.bid){
			return this->company<other.company;
		}
		return this->bid<other.bid;
	}
	
};

class ad_display {
	//friend class searchApp;
	public:
		ad_display () { };
		ad_display (const char* inputFile, string outputfile) { //get all the ads
			outputfile=outputfile;
			cout << "Opening Input File: " << inputFile << std::endl;
	
		// Open dataStream to take companies, bids, and the price in dollars for their bids
			ifstream inputStream;
			inputStream.open( inputFile );
	
		// Take in company names as case sensitive
		// Keyword bids are case insensitive
		// Price in dollars for bid are accumulated
	
		// First take in the number of bids
			int numBids;
			inputStream >> numBids;
	
		// Have a vector of all advertiserBid's
	
		// Use a loop to fill set one by one
			for ( int i = 0; i < numBids; ++i ) {
				string company_line;
				string word;
				float price;
		
			// Variable to hold the advertiser bid pairing
				advertiserBid tempBid;
		
			// Get the bid, convert to lowercase
				inputStream >> word;
				
				for (unsigned int i=0; i<word.size(); i++){
					word [i]=tolower (word [i]);
					//for some reason, transform isn't working
				}
		
			// Get bid value
				inputStream >> price;
		
			// Get company name
				inputStream >> tempBid.company;
			//	inputStream>>company;
				
				string tempRestLine;
				getline (inputStream, tempRestLine);
				tempBid.company+=tempRestLine;
/* 				unsigned int i=0;
				const char* temp= tempBid.company.c_str();
				
				while (temp[i]<65||(temp[i]<97&&temp[i]>90)||temp[i]>122){
					i++;
				}	
				cout<<"i is: "<<i<<endl;
				//string temp (tempBid.company.substr (0,i));
				tempBid.company.erase (tempBid.company.begin()+i-1);
				//tempBid.company=tempBid.company-temp; */
				cout<<tempBid.company<<endl;
				
			// Fill advertiserBid values
				tempBid.word = word;
				tempBid.bid = price;
				tempBid.clicks=0;
				cout<<"Temp bid company: "<<tempBid.company<<endl;
				ad_bank.push_back(tempBid);
			}
	
		// Close inputstream
			inputStream.close();
		}

		~ad_display () { }; //perhaps you'll have to delete the new vector
		
		//this will get the ads that match the search
		vector <advertiserBid> match_ads (){
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
		vector <string> queryVector;
		vector <advertiserBid> sort_ads (vector <advertiserBid> &matching){
			make_heap (matching.begin(), matching.end());
			//cout<<"Given."<<endl;
			//you have comparator object so this should work
			sort_heap (matching.begin(), matching.end());
	
			return matching;
		} //this sorts the ads that match the search
		vector <advertiserBid> get_bank () {return ad_bank;}
		string query;
		
		void write_out (){
			ofstream writer (outputfile.c_str());
			//cout<<"Youre in write out."<<endl;
			vector <advertiserBid> pay=this->match_ads();
			if (pay.size()==0){
				string no_charge ("no charges.");
				cout<<"No charges issued."<<endl;
				writer<<no_charge<<endl;
				writer.close();
				return;
			}
			
			vector <advertiserBid> payments= this->sort_ads (pay);
			
			for (unsigned int i=0; i<payments.size()-1; i++){
				if (payments[i].company>payments[i+1].company){
					advertiserBid temp;
					temp.company=payments [i].company;
					temp.bid=payments [i].bid;
					temp.clicks=payments [i].clicks;
					temp.word=payments[i].word;
					
					payments [i].company=payments [i+1].company;
					payments [i].bid=payments [i+1].bid;
					payments [i].clicks=payments [i+1].clicks;
					payments [i].word=payments [i+1].word;
					
					payments [i+1].company=temp.company;
					payments [i+1].bid= temp.bid;
					payments [i+1].clicks=temp.clicks;
					payments [i+1].word=temp.word;
				}
			}
			
			for (unsigned int i=0; i<payments.size();i++){
				writer<<payments[i].company<<endl;
				cout<<"Should be writing to file."<<endl;
				double total=payments[i].clicks*payments[i].bid;

				writer<<total<<endl;
				writer<<endl;

			}
			writer.close();
		}
		
		
			
	private:
		//vector <advertiserBid> match_ads (); 
		vector <advertiserBid> ad_bank;
		string outputfile;

};
#endif //ad_display
