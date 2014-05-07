#include <iostream>
#include <fstream>
#include "web_crawler.h"

using namespace std;

int main (int argc, char* argv[]){
	if (argc<3){
		cout<<"Executable, Input file, output file"<<endl;
	}
	
	ifstream input (argv[1]);
	//ostream output(argv[2]);
	vector <string> known_files;
	map <string, WebPage*> pageMap;
	string get_files;
	WebCrawler* crawl= new WebCrawler (get_files.c_str(), argv[2]);
	
	while (getline (input, get_files)){
		known_files.push_back (get_files);
		//WebCrawler* crawl= new WebCrawler (get_files.c_str(), argv[2]);
		WebPage* add= new WebPage (get_files);
		pageMap.insert (pair <string, WebPage*> (get_files, add));
	//adds all known files into map first
	}
	
	for (unsigned int i=0; i<known_files.size(); i++){
		crawl->parse (known_files[i].c_str(), pageMap);
	}
	
	crawl->write_file (argv[2], pageMap);
	
	return 0;
}