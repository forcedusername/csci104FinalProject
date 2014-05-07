#include "mainwin.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string.h>
#include <string>
#include <sstream>
#include <ctype.h>
#include "WebPage.h"
#include <map>
#include <deque>
#include "lib/Set.h"
using namespace std;

//converts string s to lowercase string
//returns a list of words after formatting
/*
deque<string> parseQuery(char* line)
{

	deque<string> words;
	if (line == NULL)
		throw logic_error("the string is empty");//return empty deque
	stringstream ss(line);
	int pos2 = -1; //index of right parentheses
	string s;
	ss >> s; // get rid of AND/OR
	ss >> s;

	if (s[0] == '(')
	{
		s = s.substr(1, s.size()-1);
	}
	while (true)
	{
		try{
			int pos = s.find(',');//make sure comma is not in string
			if (pos > 0)
			{
				s = s.substr(0, pos);
				//cerr << s; //debug
			}
			pos2 = s.find(')');
			if (pos2 > 0)
			{
				s = s.substr(0, pos2);
				//cerr << s; //debug
			}
			words.push_front(toLowerCase(s));
		}
		catch (exception &e) //if already in page
		{
			cout << e.what();
		}

		ss >> s;
		if (ss.fail())
		{
			if (pos2 == -1) //right paren wasn't found
			{
				//cout << "error with formatting" << endl;
				throw logic_error("Error: missing parentheses");
			}
			ss.clear();
			return words;
		}
		else
		{
			if (pos2 > -1)//if the right parentheses was found but it's not the last word
				throw logic_error("Error: bad formatting");
		}
		pos2 = -1; //check if the right parentheses isn't in the last word
	}
	return words;

}
*/
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
  	MainWin w;
	w.addPagesFromFile(argv[1]);
	w.show();
	return a.exec();
}
