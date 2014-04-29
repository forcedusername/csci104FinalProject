#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <exception>
#include "webpageSTL.h"
#include "setSTL.h"
#include "comparatorsSTL.h"
#include "search.h"
#include "msort.h"
using namespace std;

class int_compare;
class string_compare;
void getQueryVector(string inputLine, vector<string> &queryVector);
void fillQuerymap (map<string, Set<int, int_compare> > &querymap, vector<string> &queryVector, vector<WebPage*> &webPagePtrList);
Set<int, int_compare> setOperation (map <string, Set <int, int_compare> > &querymap, int comm, vector <string> &queryVector);
void displayResult(vector<WebPage*> &webPagePtrList, Set<int, int_compare> &results);
void printwebPages(vector<WebPage*> &webPagePtrList);
void printLinks(vector<WebPage*> &webPagePtrList);
vector <WebPage*> get_pages (vector <string> queryMatch);

void searchApp::loadPagesAndParse()
{
    std::ifstream input(datafileName.c_str());
	//ifstream input;
    string webfilename;

    //int position = 0;
    while (getline (input, webfilename)){
        WebPage* pWebPage = new WebPage(webfilename);
        webPagePtrList.push_back(pWebPage);

        pageMap.insert (pair <string, WebPage*> (webfilename, pWebPage));
    }

  //  cout<<"Page map size is: "<<pageMap.size()<<endl;
  //  cout<<"Web Page Ptr List is: "<<webPagePtrList.size()<<endl;


    map<string, WebPage*>::iterator file_walk= pageMap.begin();
    while (file_walk!=pageMap.end()){
        file_walk->second->parse(file_walk->first, pageMap);
        file_walk++;
    }


} // searchApp:: loadPagesAndParse

void searchApp::searchQuery(const string &query, vector<string> &queryMatch)
{
    map<string, Set<int, int_compare> >     querymap;
    Set<int, int_compare>                    results;

    string inputString;
    vector<string> queryVector;
    int comm;

    if (query == ".") {
        return;
    }
    if (query == ""){
        return;
    }

    stringstream sstream(query);
    sstream >> inputString;

    getQueryVector(query, queryVector);

    if (inputString == "AND"){
        comm=1;
    }
    else if (inputString == "OR"){
        comm=2;
    }
    else{
        comm=3;
        if (queryVector.size()>1){
            cout<<"Error. Illegal Search Query."<<endl;
            return;
        }
    }

    fillQuerymap (querymap, queryVector, webPagePtrList);
    results = setOperation (querymap, comm, queryVector);


    int position;
    for (Set<int, int_compare>::iterator it = results.begin(); it != results.end(); ++it)
    {
        position = *it;
        WebPage *webPage = webPagePtrList[position];
        //queryMatch.push_back(webPage->filename());
        queryMatch.insert(queryMatch.begin(), webPage->filename());
    }

    queryVector.clear();
    
//SORT probably not here....
    vector<WebPage*> result = get_pages(queryMatch);
    queryMatch.clear();

    for (unsigned int i=0; i < result.size(); i++)
    {
        //WebPage *webPage = webPagePtrList[position];
        //queryMatch.push_back(webPage->filename());
        queryMatch.insert(queryMatch.begin(), result[i]->filename());
    }

}

 vector <WebPage*> searchApp::get_pages (vector <string> queryMatch)
{
	unsigned int iterating =0;
	//vector <WebPage*> matching_pages;
	Set<WebPage*, WebPtr_compare> matching_links;
	while (iterating<queryMatch.size()){
		WebPage* match= pageMap.at (queryMatch[iterating]);

		matching_links.insert (match);
/*
		Set<WebPage*, WebPtr_compare> temp= match->allIncomingLinks();
			Set<WebPage*, WebPtr_compare>::iterator temp_walker=temp.begin();
			while (temp_walker!=temp.end()){
				matching_links.insert (*temp_walker);	
				temp_walker++;
			}
*/
		Set<WebPage*, WebPtr_compare> temp= match->allOutgoingLinks();
			Set<WebPage*, WebPtr_compare>::iterator temp_walker7=temp.begin();
			while (temp_walker7!=temp.end()){
				matching_links.insert (*temp_walker7);	
				temp_walker7++;
			}
		iterating++;
	}

	vector<WebPage*> everything;
	Set<WebPage*, WebPtr_compare>::iterator temp_walker2=matching_links.begin();
	while (temp_walker2!=matching_links.end()){
		everything.push_back(*temp_walker2);
		temp_walker2++;
	}
	return everything;
}//searchApp::searchQuery

void searchApp::getPage(const string &filename, string &fileOUT, vector<string> &outLinks, vector<string> &inLinks)
{
    try
    {

         WebPage *webPage = pageMap.at(filename);
         stringstream ss;
         ss << *webPage;
         fileOUT = ss.str();
		 
		Set <WebPage*, WebPtr_compare> outset = webPage->allOutgoingLinks();
		Set <WebPage*, WebPtr_compare>::iterator oit= outset.begin();
		for (;oit != outset.end(); oit++)
		{
			WebPage *oweb = *oit;
			outLinks.push_back(oweb->filename());
		}
		Set <WebPage*, WebPtr_compare> intset = webPage->allIncomingLinks();
		Set <WebPage*, WebPtr_compare>::iterator iit= intset.begin();
		for (;iit != intset.end(); iit++)
		{
			WebPage *oweb = *iit;
			inLinks.push_back(oweb->filename());
		}
		

    }
    catch (...)
    {
       //e = e;
        //;
    }
}//searchApp::getPage


// global helper functions


void getQueryVector(string inputLine, vector<string> &queryVector)
{
	string str1;
  // erase white space
	inputLine.erase(remove_if(inputLine.begin(), inputLine.end(), ::isspace), inputLine.end());

  // Take out only the comma separated query words.
	size_t pos1 = inputLine.find_first_of('(');
	size_t pos2 = inputLine.find_first_of(')');
	if (pos1 > 0 && pos2 > 0){
		str1 = inputLine.substr(pos1+1, pos2-pos1-1);
	}
	else{
		str1 = inputLine;
	}
  // now split the words and put in the vector.
    
	size_t pos = 0;
	string token;
	string delimiter = ",";
	while ((pos = str1.find(delimiter)) != string::npos) {
		token = str1.substr(0, pos);
		transform(token.begin(), token.end(), token.begin(), ::tolower);
		queryVector.push_back(token);
		str1.erase(0, pos + delimiter.length());
	}    
	//cout<<"String 1 is: "<<str1<<endl;
	//cout<<"String 1 size is:"<<str1.length()<<endl;
	if (str1.length()>0){
		transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
  		queryVector.push_back(str1);
	}
	else {
		return;
	}
}

//if i enter AND (face, book, glob)
//get query should give me back face book glob
//if store in vector of strings vector [1]= face vector 2 book vector 3 glob 
//i can access index by index and then pull out the sets for each word
//and then do operations

void fillQuerymap (map <string, Set <int, int_compare> > &querymap, vector <string> &queryVector, vector <WebPage*> &webPagePtrList){
	int iteration_size= queryVector.size();

	//webPagePtrList is zero...
	int second_walk= webPagePtrList.size ( );

	int i=0;
	Set<int, int_compare> pageSet;
	while (i<iteration_size){
		string query_get= queryVector [i];
        //cout<<"Query get is: "<<query_get<<endl;
		
		//Set <int, int_compare> pageSet;
    // XXX make sure that this query is NOT there in the querymap already
		try{
			Set<int, int_compare> tempSet = querymap.at(query_get);
		//Key already exists, meaning that this query is already in the map, so skip it.
			i++;
			continue;
		} 
		catch (...){
		//make exceptions mean something
		//it is ok to get exception i.e map does not have the query, catch it continue;
            //cerr<<"not in map, going to add..."<<endl;
			//Set<int, int_compare> tempSet=querymap.at(queryVector [i]);
			//i++;
			//continue;
    }
    //Allocate a set for this query and add the web pages.
			//Set<int, int_compare>* pageSet= new Set<int, int_compare>;
      Set<int, int_compare> pageSet;
			int j=0;
			while (j<second_walk){
				WebPage* holder= webPagePtrList[j];
				Set<string, string_compare> WordGet= holder-> allWords ( );
			
			//this block should check if query get is in wordGet
				Set<string, string_compare>::iterator word_walk=WordGet.begin();
				while (word_walk!=WordGet.end()){
          //cout<<"Entering word walk while loop..."<<endl;
					if (*word_walk==query_get){
            //cout<<"Inserting....."<<endl;
						pageSet.insert (j);
            break;
					}
					word_walk++;
				}
			
				j++;
			}
      //cout<<"page set size is: "<<pageSet.size()<<endl;
	
      querymap.insert (pair <string, Set <int, int_compare> > (query_get, pageSet));
      //cout<<"Query map size is: "<<querymap.size()<<endl;
      i++;
    }
    //cout<<pageSet.size()<<" is page set's size in function."<<endl;
		//querymap.insert (pair <string, Set <int, int_compare> > (queryVector [i], *pageSet));
		//cout<<querymap.size()<<" is the query map size."<<endl;
    //i++;
	
    //cout<<queryMap.size()<<" is the query map size."<<endl;
   // cout<<"After exiting while loop, page set size is: "<<pageSet.size()<<endl;
   // cout<<"After exiting while loop, query map size is: "<<querymap.size()<<endl;
}

Set<int, int_compare> setOperation (map <string, Set <int, int_compare> > &querymap, int comm, vector <string> &queryVector){
	//cout<<"Entering setOperation."<<endl;
	//cout<<"The Query Vector size entering the set operation function is: "<<queryVector.size()<<endl;
	Set<int, int_compare> webPageIndexSet;
	unsigned int i;
  // IMPORTANT: all the entries in the query vector are already stored in querymap (if no string match, empty page set is 
  //    is stored for that key in querymap). So, querymap.get below WILL NOT throw exception.
	if (queryVector.size() == 0)
		return webPageIndexSet;
	if (comm == 1){
    // AND
		i = 0;
		while (i < queryVector.size()){
			if (i == 0){
				cout<<"Not going into set union..."<<endl;
				webPageIndexSet = querymap.at(queryVector [i]);
			}
			else{
				cout<<"Going into set union..."<<endl;
				webPageIndexSet = webPageIndexSet.setIntersection(querymap.at (queryVector [i]));
			}
			i++;
		}
	}
	else if (comm == 2){
    // XXX OR
		i = 0;
		while (i < queryVector.size()){
			if (i == 0){
				webPageIndexSet = querymap.at (queryVector [i]);
			}
			else{
				Set<int, int_compare> temp = querymap.at (queryVector [i]);
				Set<int, int_compare>::iterator temp_iterator=temp.begin();
				for(;temp_iterator!=temp.end(); temp_iterator++)
				{
				  cout<<"temp's elements are: "<<*temp_iterator<<endl;
				  //print each name of webpage of temp
				}
				
				
				webPageIndexSet = webPageIndexSet.setUnion(temp);
				/*
				Set<int, int_compare>::iterator wpage_index_iter=webPageIndexSet.begin();
				for(; wpage_index_iter!=webPageIndexSet.end(); wpgage_index_iter++)
				{
				 cout<<"wpage elements after union are: "<<*wpage_index_iter<<endl;
				 //rint webPAGeINdex set filename
				}
				*/
				
				Set<int, int_compare>::iterator wpage_iterator=webPageIndexSet.begin();
				for(; wpage_iterator!=webPageIndexSet.end();wpage_iterator++)
				{
				  cout<<"wpage elments are: "<<*wpage_iterator<<endl;
				  //print webPAGeINdex set filename
				}
				
				
			}
			i++;
		}
	}
	
	else if (comm==3){
        webPageIndexSet = querymap.at(queryVector [0]);  
        //cout<<"Query vector at 0 is: "<<queryVector[0]<<endl;
	}
	return webPageIndexSet;
} //END setOperation
template <typename Iter>
Iter __next(Iter iter)
{
    return ++iter;
}
template <typename Iter, typename Cont>
bool is_last(Iter iter, const Cont& cont)
{
    return (iter != cont.end()) && (__next(iter) == cont.end());
}

void displayResult(vector<WebPage*> &webPagePtrList, Set<int, int_compare> &results)
{
	int size = results.size();

	string cmd;
	cout << size << " pages matched the query " << endl;
  // if nothing to display return to main loop
	if (size == 0){
		cout<<"Sorry, no matches."<<endl;
		return;
	}
	
	Set<int, int_compare>::iterator thing=results.begin(); 
	int position = *thing;
	while (1){
		WebPage *webPage = webPagePtrList[position];
		cout << "PAGE DISPLAY START *******************\n";
		cout << *webPage;
		cout << "PAGE DISPLAY END *******************\n";
		cin >> cmd;
		if (cmd == "quit"){
      // done, return to main loop
			cout << "quiting...\n" << endl;
			return;
		}
		if (cmd == "next"){
			
			//does Set have an iterator since it inherits from set?
      
			//if (thing==results.end())
      if (is_last(thing,results))
      {
				cout<<"Last Page."<<endl;
				continue;
			}
			thing++;
			position= *thing;    
			//thing++;
		}
    // anything else print same page.i.e go back 
  } // while
}//END displayResult
void printwebPages(vector<WebPage*> &webPagePtrList)
{
	int size = webPagePtrList.size();
	for (int i = 0; i < size; i++){
		WebPage *webPage = webPagePtrList[i];
		cout << "PAGE DISPLAY START (" << i << ")*******************\n";
		cout << *webPage;
		cout << "PAGE DISPLAY END   (" << i << ")*******************\n";
	}
}
void printLinks(vector<WebPage*> &webPagePtrList)
{
	int size = webPagePtrList.size();
	for (int i = 0; i < size; i++){
		WebPage *webPage = webPagePtrList[i];

		Set <WebPage*, WebPtr_compare> outset = webPage->allOutgoingLinks();
		cout << "OUT links for " << webPage->filename() << " : " << outset.size() << endl;
		Set <WebPage*, WebPtr_compare>::iterator oit= outset.begin();
		for (;oit != outset.end(); oit++)
		{
			WebPage *oweb = *oit;
			cout << oweb->filename() << endl;
		}
		Set <WebPage*, WebPtr_compare> inset = webPage->allIncomingLinks();
		cout << "IN links for " << webPage->filename() << " : " << inset.size() << endl;
		Set <WebPage*, WebPtr_compare>::iterator iit= inset.begin();
		for (;iit != inset.end(); iit++)
		{
			WebPage *iweb = *iit;
			cout << iweb->filename() << endl;
		}
	}

}


void searchApp::sortRank(vector<string>& List)
{
	vector<WebPage*> base;
	for (unsigned int i=0; i<List.size(); i++)
	{
		map<string, WebPage*>::iterator sample= (pageMap.find(List[i]));
		WebPage* temp= sample->second;
		base.push_back(temp);
	}

    int pagenum = base.size();
	//The actual rank part starts from here
	//Starting to create the G matrix.
	double ** GMa = new double* [pagenum];	//GMa = G Matrix
	for (int i=0; i<pagenum; i++)
	{
		GMa[i] = new double[pagenum];
	}

	for (int i=0; i<pagenum; i++)
	{
		for(int j=0; j<pagenum; j++)
		{
			GMa[i][j] = 0.15/pagenum;
		}
	}	//Initialize the value for the later part(Matrix U with all 1's * 0.15/pagenum)


	for (int i=0; i<pagenum; i++) //Loop through all pages, check value for Hyperlink Matrix and Dangling Nodes Matrix
	{
		int workinglink = 0; //Variable to keep the number of pages that is in the scope and being pointed to.
		//Page A can link to Page D while Page D is not in the search results, so its needed to check.

		//Need to change this part to pointer version of Set<WebPage*>
		//This part is just counting the valid inscope links
		Set<WebPage*, WebPtr_compare> links = base[i]->allOutgoingLinks();
		for (Set<WebPage*, WebPtr_compare>::iterator it = links.begin(); it!=links.end(); ++it)
		{	//Check if the Link is one of the results
			for (int j=0; j<pagenum; j++)
			{
				if (base[j] == *it) workinglink++;
				//If a link can be find in the results, than it's considered a valid result
			}
		}
		//cout << workinglink << endl;

		if (!workinglink) //If no working link exist, that is a sink node
		{
			for (int j=0; j<pagenum; j++)
			{
				GMa[j][i] = GMa[j][i] + 0.85 /pagenum;
			}
		}
		else //Working link do exist
		{	//We still need to loop again to find out those working links
			//but this time updating their value in matrix
			Set<WebPage*, WebPtr_compare>links = base[i]->allOutgoingLinks();
			for (Set<WebPage*, WebPtr_compare>::iterator it = links.begin(); it!= links.end(); ++it)
			{
				for (int j=0; j<pagenum; j++)
				{
					if (base[j] == *it) 
					//If true, page i have link to page j
					{	
						GMa[j][i] = GMa[j][i] + 0.85 /workinglink;
					}
				}
			}

		}
	}
/*
	for (int i=0; i<pagenum; i++)
	{
		for (int j=0; j<pagenum; j++)
			cout << GMa[i][j] << "|";
		cout << endl;
	}
	*/
	double * score = new double [pagenum];
	//Initialize the value to all 1/n
	for (int i=0; i<pagenum; i++)
	{
		score[i] = 1.00/pagenum;
	}

	for (int a=0; a<30; a++)
	{
		double * temp = new double [pagenum];//Place to store all results before update them
		for (int i=0; i<pagenum; i++)
		{
			double buff = 0;
			for (int j=0; j<pagenum; j++)
			{
				buff = buff + GMa[i][j]*score[j];
			}
			temp[i] = buff;
		}//After this loop a set of new values have been calculated;
		for (int i=0; i<pagenum; i++)
			score[i] = temp[i]; 	//Set the new values at the same time
	}

	for (int i=0; i<pagenum; i++)
	{
		base[i]->rank = score[i]; // Set the rank values into webpage objects
	}
	//Rank values calculated
/*
	for (int i=0; i<pagenum; i++)
		//DEBUG: display the rank values
		cout << base[i]->rank << endl;
*/
	RankComp comp2;
	mergeSortStarter(base, comp2);
/*
	for (int i=0; i<pagenum; i++)
	//DEBUG: display the rank values
	cout << base[i]->filename() << "|" << base[i]->rank << endl;
*/
	List.clear();
	for(unsigned int i=0; i<base.size(); i++)
	{
		string temp = base[i]->filename();
		List.push_back(temp);
	}

	for (int i=0; i<pagenum; i++)
		delete[] GMa[i];
	delete[] GMa;
}

