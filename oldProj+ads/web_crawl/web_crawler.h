#ifndef _WebCrawler
#define _WebCrawler

//#include "search.h"
#include "setSTL.h"
#include "comparatorsSTL.h"
#include "webpageSTL.h"
#include <fstream>
#include <string>
#include <cstdlib>

//you'll have the input and output files as private
//your parse, depth first search will all be public functions 

class WebPage;

class WebCrawler {
	public: 
		WebCrawler ( ) { }
		WebCrawler (const char* filename, char* output){
			std:: string input_filename (filename);
			std:: string output_filename (output);
		}
		~WebCrawler ( ){ }
		void write_file (char* output_file, map<string, WebPage*> &pageMap);
		void parse (const char* filename, map<string, WebPage*> &pageMap);
		//void depth_search (WebPage* search_links, map <string, WebPage*> &allPages);
		string get_input (){return input_filename;}
		string get_output (){return output_filename;}
		
	private:
		string input_filename;
		string output_filename;
};

#endif