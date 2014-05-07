#include "WebPage.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string>
#include <ctype.h>
//#include "lib/Set.h"

using namespace std;

WebPage::WebPage ()   // constructor that creates an empty page
{
  pageRank = 0;
}
WebPage::WebPage(const char* file)
{
	_filename = file;
	pageRank = 0;//initial value
	//absolutely no parsing done in constructor
}
WebPage::~WebPage ()   // destructor
{

}
void WebPage::parse(map<string, WebPage*> & pages)
{
	//read in file
	ifstream ifile(_filename);

	if (ifile.fail())
	{
		ifile.clear();
		throw logic_error("The file is invalid.");
	}

	//char *s = new char[2000];
	string s;
	while (!ifile.fail())
	{
	  //	ifile.getline(s, 2000);
	  getline(ifile, s); 
	  int size = s.length();
	  string temp;
	  for (int i = 0; i < size; i++)
	    {
	      if (s[i]=='(')//if a link is found
		{
		  i++;
		  string filename = ""; //add chars to filename
		  while (s[i]!=')')
    			{
    				filename += s[i];
    				i++;
    			}
		  //set outgoing and incoming links 
    			addOutgoingLink(pages[filename]);
    			pages[filename]->addIncomingLink(this);
		  
		}
	      else
		temp += s[i];
	    }
		word_lines.push_back(temp);
	}
	//	delete s;
	
  //  Set<string> words; //contains the formatted words
    for (deque<string>::const_iterator it = word_lines.begin(); it != word_lines.end(); ++it)//itertae through list of lines
   	{
	string line = *it;
    	string temp = "";
    	int length = line.length();
    	for (int j = 0; j < length; j++)//iterate through each char
    	{
    		
    		if (isalnum(line[j])) //add char to string if alphanumeric
    		{
    			temp += tolower(line[j]);
    		}
    		else if (temp.size() > 0)//reached nonalphanumeric, separate the string
    		{
    			try
    			{
				//cerr << "adding " << temp << " to all_words" << endl;
        			all_words.insert(temp);
    			}
    			catch(exception &e) {}
    			temp = "";
    		}
    		if (j == length-1)//insert the last string in case last char is alphanumeric
    		{
    			all_words.insert(temp);
    		}
    	}
    }
}
void WebPage::addIncomingLink (WebPage* start)
{
	incoming_links.insert(start);
}
void WebPage::addOutgoingLink(WebPage* target)
{
	outgoing_links.insert(target);
}
Set<string> WebPage::allWords () const
{

    return all_words;
	/* Returns a set containing all individual words on the web page. */
}

ostream & operator<< (ostream & os, const WebPage & page)
{

	for (deque<string>::const_iterator it = page.word_lines.begin(); it != page.word_lines.end(); ++it)
	{
		string s = *it;
		int length = s.length();
		for (int i = 0; i < length; i++)
		{
			if (s[i]=='[' || s[i] == ']')//encountered anchor text
			{
				//don't print brackets when there's anchor text
			}
			else if (s[i] == '(')//encountered a link
			{
				while (s[i] != ')')
				  i++;//iterate through the chars in the link as to not print the link

			}
			else
				os << s[i];
		}
		os << endl;
	}
	return os;
      /* Declares an operator we can use to print the web page. */
}
Set<WebPage*> WebPage::allOutgoingLinks() const
{
	return outgoing_links;
}
Set<WebPage*> WebPage::allIncomingLinks() const
{
	return incoming_links;
}
string WebPage::filename() const
{
	return _filename;
}

 float WebPage::getPageRank() const
{
  // const float p = pageRank;
  //cerr << "checkpoint" << endl;
  return pageRank;
}
void WebPage::setPageRank(const float r)
{
  pageRank = r;
  }
