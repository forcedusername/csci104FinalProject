#include "mainwin.h"
#include "pagewin.h"
#include "msort.h"

//#include "ui_mainwin.h"
struct PageRankComp{
  bool operator()(const WebPage* w1, const WebPage* w2)
  {
    //returns 1 if w1 has a higher or equal page rank to w2
    return w1->getPageRank() >= w2->getPageRank();
  }
};

struct PageNameComp{
  bool operator()(const WebPage* w1, const WebPage* w2)
  {
    //returns true (1) if w1 comes before w2
    return w1->filename() < w2->filename();
  }
};


void MainWin::calcPageRank( Set<WebPage*> & allPages )
{
	Set<WebPage*> T = allPages;
	
	// First need to find amount of all webpages
	int amtPages = allPages.size();
	
	// Damping factor value
	float dampFactor = 0.85;
	
	// Lastly, map each site with a list of scores added to them from outgoing links
	map< string, map< string, float> > pageRankMap;
	
	    for (WebPage* w : T)
	      {
		w->setPageRank(1.0/(T.size()));
	  
	      }
	for (int i = 0; i < 30; i++)
	  {
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
		  newPageRank[ wOut ] += ( weightDistrib * dampFactor ) * w->getPageRank();
		}
		// Loop to calculate contribution to pageRank vector from pages not linked to
		for ( WebPage* w2 : T ) {
		  newPageRank[ w2 ] += (1.0 - dampFactor) / amtPages * w->getPageRank();
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

string MainWin::toLowerCase(string s)
{
	int length = s.size();
	for (int i = 0; i < length; i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}
MainWin::MainWin(QWidget *parent) :    QMainWindow(parent)
{
//allocating mem for everything
    mainLayout = new QVBoxLayout;
    topLayout = new QHBoxLayout;
    radioBtnLayout = new QHBoxLayout;
    bottomLayout = new QHBoxLayout;
    txtQuery = new QLineEdit;
    btnSearch = new QPushButton("&Search");
    btnAnd = new QPushButton("&And");
    btnOr = new QPushButton ("&Or");
    btnInfo = new QPushButton("&Info");
    btnQuit = new QPushButton("&Quit");
    sortRankBtn = new QRadioButton("Sort by Rank");
    sortRankBtn->setChecked(true);//default sort
    sortNameBtn = new QRadioButton("Sort Alphabetically");
    resultsList = new QListWidget;
    // resultsList->setSortingEnabled(true); //sorts alphabetically
    
    centerWidget = new QWidget(this);
    centerWidget->setLayout(mainLayout);
    this->setCentralWidget(centerWidget);
//setting layout for top
    topLayout->addWidget(txtQuery, 2);
    topLayout->addWidget(btnSearch );
    topLayout->addWidget(btnAnd);
    topLayout->addWidget(btnOr);
    //setting layout for radio buttons
    radioBtnLayout->addWidget(sortRankBtn);
    radioBtnLayout->addWidget(sortNameBtn);
//setting layout for bottom buttons
    bottomLayout->addWidget(btnInfo);
    bottomLayout->addWidget(btnQuit);
//putting layouts together
    mainLayout->addLayout(topLayout, 0);
    mainLayout->addLayout(radioBtnLayout);
    mainLayout->addWidget(resultsList, 1);
    mainLayout->addLayout(bottomLayout);
//connecting buttons
    connect(btnSearch, SIGNAL(clicked()), this, SLOT(doSearch()));
    connect(btnAnd, SIGNAL(clicked()), this, SLOT(doAnd()));
    connect(btnOr, SIGNAL(clicked()), this, SLOT(doOr()));
    connect(btnInfo, SIGNAL(clicked()), this, SLOT(showInfo()));
    connect(btnQuit, SIGNAL(clicked()), this, SLOT(close()));
    connect(resultsList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(displayPage(QListWidgetItem*)));

}
void MainWin::addPagesFromFile(char* filename)
{
	ifstream ifile(filename);
	string pagename;
	ifile >> pagename;
	while (!ifile.fail())//read in all the webpages
	{
		try
		{
		  if (pagename.size() > 0)
		    {
			//int s = pages.size();
			//cout << s << endl;
			WebPage * w = new WebPage(pagename.c_str());
			pages[pagename] = w;
			//cerr << pagename << endl;
		    }
		}
		catch (exception &e)
		{
			cout << e.what();
		}
		ifile >> pagename;
	}
	for (map<string, WebPage*>::iterator it = pages.begin(); it != pages.end(); ++it)//iterate through all webpages
	{
		WebPage* w = it->second;
		w->parse(pages);
	//	cerr << *w;
		Set<string> words = w->allWords();
		for (Set<string>::iterator it2 = words.begin(); it2 != words.end(); ++it2)
		{
			string nextword = *it2;
		    //	cerr << nextword << endl;
			try
			{
				queries[nextword].insert(w);
			//	cerr << "added webpage for " << nextword << endl;
			}
			catch (exception & e)//if nextword does not exist as key in Map query
			{
				Set<WebPage*> temp;
				temp.insert(w);
				queries[nextword] = temp;
			}
		}
	}
}
MainWin::~MainWin()
{
for (map<string, WebPage*>::iterator it = pages.begin(); it != pages.end(); ++it)
	{
		delete it->second;
	}
}
void MainWin::doSearch(void)
{
    resultsList->clear();
    //retrieve text from textfield
    string text = txtQuery->text().toStdString();
    try
	{
		Set<WebPage*> pagelist = queries[text];
		displayResults(pagelist);
		//	cerr << "finished calling display" << endl;

	}
	catch (exception e)
	{
		cout << "That word does not exist in a page" << endl;
	}
	resultsList->show();
}
void MainWin::doAnd(void)
{
    resultsList->clear();
    string text = txtQuery->text().toStdString();
    deque<string> words;
    stringstream ss(text);
    string s;
    while (!ss.fail())
    {
	ss >> s;
	words.push_front(toLowerCase(s));
    }
    	Set<WebPage*> firstpage;
	string word;
		try
		{
			word = words[0];
			firstpage = queries.at(word); //find all pages containing the first word
		}
		catch (exception e)
		{
			cout << "word isn't in a page" << endl;
			return;
		}
		for (deque<string>::iterator it = words.begin(); it != words.end(); ++it) //iterate through rest of words
		{
			string name = (*it);
			try{
				Set<WebPage*> pageswithwords = queries.at(name);
				firstpage = firstpage.setIntersection(pageswithwords);
			}
			catch (exception &e)
			{
				cout << "Word doesn't exist in query" << endl;
			}
		}
		displayResults(firstpage);


}
void MainWin::doOr(void)
{
    resultsList->clear();
    string text = txtQuery->text().toStdString();
    deque<string> words;
    stringstream ss(text);
    string s;
    while (!ss.fail())
    {
	ss >> s;
	words.push_front(toLowerCase(s));
    }
    	Set<WebPage* > firstpage;
	string word;
		for (deque<string>::iterator it = words.begin(); it != words.end(); ++it)
		{
			string name = (*it);
			try {
				Set<WebPage*> pageswithwords = queries.at(name);
				firstpage = firstpage.setUnion(pageswithwords);
			}
			catch (exception &e){}
		}
		displayResults(firstpage);


}
void MainWin::showInfo(void)
{
    QMessageBox::information(this, tr("Info"), tr("For a single query, enter one word and press Search. For AND and OR queries, enter the words separated by spaces. Double click links to view the web pages."));
}
void MainWin::displayPage(QListWidgetItem * item)
{
    //xcerr<< "test" << endl;
    //create new page info doc with given name
    //retrieve the webpage of the given filename
    string pagename = item->text().toStdString();
    WebPage * w = pages[pagename];
    PageWin * p = new PageWin(w, pages);
    p->show();

}
void MainWin::displayResults(Set<WebPage* > &  w)
{
  //check to see what type of sorting is being done
  Set<WebPage* > T = w;
  deque<WebPage*> sorted;
  for (WebPage* temp : w)
    {
      T = T.setUnion(temp->allOutgoingLinks());
      T = T.setUnion(temp->allIncomingLinks());
    }
    calcPageRank(T);
  for (WebPage* t : T)
    {
      sorted.push_back(t);
    }
  PageRankComp rankComparator;
  PageNameComp nameComparator;
  if (sortRankBtn->isChecked())
    {
      // cerr << "test"<< endl;
      mergeSort(sorted, rankComparator);
    }
  else //sortNameBtn is checked
    {
      //  cerr << "chkpt 1" << endl;
      mergeSort(sorted, nameComparator);
      //  cerr << "chkpt 2" << endl;
    }
  for (unsigned int i = 0; i < sorted.size(); i++)
    {
      QListWidgetItem * item = new QListWidgetItem(QString::fromStdString(sorted[i]->filename()));
      resultsList->addItem(item);
    
    }
}
