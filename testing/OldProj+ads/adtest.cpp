#include "ad_display.h"

int main (int argc, char* argv []){
	ad_display test (argv [1]);
	
	if (argc<2){
		cout<<"Executable, text file. "<<endl;
		return 0;
	}
	
	//vector <advertiserBid> temp= test.get_bank ();
	//cout<<"Sorted now."<<endl;
	//temp=test.sort_ads(temp);
	
	string books ("books");
	string education ("naughty");
	//string failure ("failure");
	vector<string>some;
	some.push_back (books);
	some.push_back (education);
	//some.push_back (failure);
	
	test.queryVector=some;
	
	/* vector <advertiserBid> temp1=test.sort_ads (temp);
	for (unsigned int i=0; i<temp.size();i++){
		cout<<temp1[i].word<<" that's the word folks."<<endl;
		
		//fix company
		cout<<temp1[i].company<<" thats the company."<<endl;
		cout<<temp1[i].bid<<" thats the bid."<<endl;
	}
	 */
	cout<<"now for matches."<<endl;
	vector <advertiserBid> temp2= test.match_ads();
	for (unsigned int i=0; i<temp2.size();i++){
		cout<<temp2[i].word<<" that's the word folks."<<endl;
		
		//fix company
		cout<<temp2[i].company<<" thats the company."<<endl;
		cout<<temp2[i].bid<<" thats the bid."<<endl;
	}
	
	

	return 0;

}