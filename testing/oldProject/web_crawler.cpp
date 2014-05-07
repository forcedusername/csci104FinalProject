#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string.h>
#include <string>
#include <sstream>
#include <ctype.h>
#include "src/WebPage.h"
#include <map>
#include <deque>
#include "lib/Set.h"


using namespace std;

Set<string> found;//contains the filenames already added/printed to outfile
map<string, deque<string>> listoflinks;//maps a filename to the filenames it links to
deque<string> page_names;
ofstream ofile;

void find_links(string name)
{
  ifstream ifile(name.c_str());
  string s;
  char * temp  = new char[2000];
  while (!ifile.fail())
    {
      ifile.getline(temp, 2000);
      s += temp;
    }
     int length = s.length();
      for (int i = 0; i < length; i++)
	{
	  if (s[i]=='(')
	    {
	      i++;
	      string filename = "";
	      
	      while (i < length && s[i]!= ')')
		{
		  filename += s[i];
		  i++;
		 
		}
	      cerr << "found a link: " << filename << endl;
	      listoflinks[name].push_back(filename);
	      
	    }
	}
    
  ifile.close();
}
void crawl(string s)
{
	if (found.find(s) == found.end())//if the page isn't already in the map
	{
		//add to found set
		found.insert(s);
		//add to ofstream
		ofile << s  << endl;
	}
	//recursively call its outgoing links
	deque<string> links = listoflinks[s];
	for (string l : links)
	{
		crawl(l);
	}
}
void addLinksFromFile(const char* filename)
{
	ifstream ifile(filename);
	string pagename;
	ifile >> pagename;
	while (!ifile.fail())//read in all the webpages
	{
	  page_names.push_back(pagename);
	  find_links(pagename);
	  ifile >> pagename;
	}
	ifile.close();
}
int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		cout << "Not enough arguments" << endl;
		return 1;
	}
	const string input_file = argv[1];
	string output_file = argv[2];
	ofile.open(output_file.c_str());
	//read in WebPages and parse
	addLinksFromFile(input_file.c_str());
	//add pages to a DFS queue

	for (string s : page_names)
	  {
	    crawl(s);
	  }

	ofile.close();
	return 0;
}


