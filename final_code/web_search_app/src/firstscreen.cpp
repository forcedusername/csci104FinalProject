#include "firstscreen.h"

#include "secondscreen.h"
#include "msort.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <QGridLayout>
#include <QApplication>
#include "webpageSTL.h"
#include "search.h"
#include "ad_display.h"
#include "setSTL.h"

using namespace std;

FirstScreen::FirstScreen(string datafileName, string advertfile, string outputfile, QWidget *parent) : QMainWindow(parent)
{
    opened = false;

    //this->resize(600,500);
    btnSearch = new QPushButton("&Search", this);
    btnQuit   = new QPushButton("&Quit", this);
    btnAbout  = new QPushButton("&About", this);

    aSort = new QPushButton ("&AlphaSort", this);
    rSort = new QPushButton ("&RankSort", this);

    lineEditInput = new QLineEdit(this);
    listWidget      = new QListWidget(this);

    inputLine = new QHBoxLayout;
    sortLine = new QHBoxLayout;
    bottomLine = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    mainWidget = new QWidget;

    inputLine->addWidget(lineEditInput);
    inputLine->addWidget(btnSearch);
    sortLine->addWidget(aSort);
    sortLine->addWidget(rSort);
    bottomLine->addWidget(btnAbout);
    bottomLine->addWidget(btnQuit);

    mainLayout->addLayout(inputLine);
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(sortLine);
    mainLayout->addLayout(bottomLine);

    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
    /*
    lineEditInput->move(5,10);
    lineEditInput->setFixedSize(256, btnSearch->height());
    btnSearch->move(this->width() - btnSearch->width() - 20, lineEditInput->y());
    listWidget->move(lineEditInput->x(), lineEditInput->y() + lineEditInput->height() + 20);
    listWidget->setFixedSize(400, btnSearch->height()+300);

    btnQuit->move(this->width() - 20 - btnQuit->width(), this->height() - btnQuit->height() - 20);
    btnAbout->move (this->width() - 20 - btnQuit->width() - btnAbout->width() - 20, btnQuit->y());
*/
    // place buttons and textbox in the window with move and setFixedSize functions
    // move: http://qt-project.org/doc/qt-4.8/qwidget.html#pos-prop
    // set size: http://qt-project.org/doc/qt-4.8/qwidget.html#setFixedSize
    // get height: http://qt-project.org/doc/qt-4.8/qwidget.html#height-prop
    // get width: http://qt-project.org/doc/qt-4.8/qwidget.html#width-prop
    // get x and y: http://qt-project.org/doc/qt-4.8/qwidget.html#x-prop

    // connect clicked signal of each button to the right slot
    connect(btnAbout, SIGNAL(clicked()), this, SLOT(showAbout()));
    connect(btnSearch, SIGNAL(clicked()), this, SLOT (Search()));
    //connect (btnSearch, SIGNAL (clicked()), this, SLOT (Advertising()));

    connect (btnQuit, SIGNAL (clicked()), this, SLOT (Billing()));
    connect(btnQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    connect(aSort, SIGNAL(clicked()), this, SLOT (alphaSort()));
    connect(rSort, SIGNAL(clicked()), this, SLOT (rankSort()));

    searchApplication = new searchApp(datafileName);

    //this is the ad file name
    advertisements=new ad_display (advertfile.c_str(),outputfile);
  
    searchApplication->loadPagesAndParse();
	
	//how to figure out which one you clicked?
    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT (listWidgetDoubleClicked(QListWidgetItem *)));
}

FirstScreen::~FirstScreen()
{
    //advertisements->write_out ();
    delete btnSearch;
    delete btnAbout;
    delete btnQuit;
    delete lineEditInput;
    delete listWidget;
    delete searchApplication;
	
	
    delete advertisements;

    delete inputLine;
    delete bottomLine;
    delete mainLayout;
    delete mainWidget;
}

void FirstScreen::Billing (){
	advertisements->write_out ();
}


void FirstScreen::Search (){
    listWidget->clear(); //To clear the list each time we do a search

    //stringstream get_text;
    //get_text<<lineEditInput->text().toLocal8Bit().constData();
    string query = lineEditInput->text().toStdString();
    //string query;

    //for (int i=0; get_text>>query; i++);
    //get_text.clear();
    vector<string> queryMatches;
    searchApplication->searchQuery(query, queryMatches);

    advertisements->query=query;
    //const char* query_c= query.c_str();

    print_to_list(queryMatches, listWidget);
   // QMessageBox::information (this, tr ("Search"), tr (query_c) );
   advertisements->write_out();
}


void FirstScreen::showAbout()
{
    // ref: http://qt-project.org/doc/qt-5/qmessagebox.html#information
    QMessageBox::information(this, tr("About"), tr("This program takes in a search query and finds the query in files. "));
}

void FirstScreen::print_to_list(vector<string> queryMatches, QListWidget *listWidget){
    //listWidget->clear();
    stringstream ss;
    for (unsigned int x=0; x<queryMatches.size(); x++){
        ss.str(string());
        ss.clear();
        ss <<queryMatches[x];

        QString query_q (ss.str().c_str());
        QListWidgetItem* insertItem=new QListWidgetItem(query_q);
        listWidget->addItem (insertItem);
	// cout<<"filling this..."<<endl;

        //QDataStream out;
        //insertItem->write(&out);
        //out<<insertItem;

    }
    cout<<"exited for loop."<<endl;
    //so after you display the search results, display the ads...
    vector <string> results;
    getQueryVector (advertisements->query,results);
	advertisements->queryVector=results;
	//getQueryVector is a global function? from where
	
	vector <advertiserBid> unsort=advertisements->match_ads();
	vector <advertiserBid> sort= advertisements->sort_ads (unsort);

    for (unsigned int f=sort.size(); f>0;f--){
      cout<<"Entering ad loop."<<endl;
        ss.str (string());
        ss.clear();
        ss<<sort[f-1].company;

        QString query_q (ss.str().c_str());
        QListWidgetItem* insertItem= new QListWidgetItem (query_q);
        listWidget->addItem (insertItem);

    }
    
}

void FirstScreen::alphaSort ()
{
    vector<string> result;
    while ((listWidget->count())>0)
    {
        QListWidgetItem* temp = listWidget->takeItem(0);
        string buff = temp->text().toStdString();
        //cout << buff << endl;
        result.push_back(buff);
    }
    AlphaStrComp comp;
    mergeSortStarter(result, comp);
    for (unsigned int i=0; i<result.size(); i++)
    {
        QString listobject (result[i].c_str());
        QListWidgetItem* insertItem = new QListWidgetItem(listobject);
        listWidget->addItem(insertItem);
    }
}

void FirstScreen::rankSort ()
{
    vector<string> result;
    while ((listWidget->count())>0)
    {
        QListWidgetItem* temp = listWidget->takeItem(0);
        string buff = temp->text().toStdString();
        //cout << buff << endl;
        result.push_back(buff);
    }
    /*cout << "hi" << endl;
    for (unsigned int i=0; i<result.size(); i++)
    {
        cout << result[i] << endl;
    }
    cout << endl;*/
    //listWidget->clear();
    
    searchApplication->sortRank(result);
    for (unsigned int i=0; i<result.size(); i++)
    {

        QString listobject (result[i].c_str());
        QListWidgetItem* insertItem = new QListWidgetItem(listobject);
        listWidget->addItem(insertItem);
    }
}


void FirstScreen::listWidgetDoubleClicked(QListWidgetItem * item)
{
    if (!opened)
    {
        opened = true;
        save = new secondscreen; save->show();
    }
    //secondscreen* window_clone= new secondscreen;
        string item_convert=item->text().toLocal8Bit().constData();
    //Set<
	
		//if item_convert is in ad bank, then it's an ad? how do you check this?
		
		vector <advertiserBid> temp= advertisements->match_ads();
		vector <advertiserBid> temp1= advertisements->sort_ads (temp);
		
		advertiserBid placehold;
		placehold.company=item_convert;
		bool ad=false;
		for (unsigned int i=0; i<temp1.size();i++){
			if (temp1[i].company==placehold.company){
				cout<<"You're at an ad."<<endl;
				ad=true;
				QMessageBox::information (this, tr ("Advertisement"), tr (item->text().toLocal8Bit().constData()));
				temp1[i].clicks++;
				//ad=true;
				break;
			}
			
		}
		
		if (ad==false) {
			//you're at a filename
			save->draw_screen(item_convert, searchApplication);

			save->show();
		}
    //window_clone->hide();
    //QMessageBox::information(this, tr("ListSelected"), tr(item->text().toLocal8Bit().constData()));

   // window_clone.show();

}

