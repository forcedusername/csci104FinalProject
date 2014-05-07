#include "secondscreen.h"
//#include <QPlainTextEdit>
//#include <QListWidget>
#include "search.h"
#include "setSTL.h"
#include <QGridLayout>
#include <QApplication>
#include <QString>
#include <QTextEdit>
using namespace std;
secondscreen::secondscreen(QWidget *parent) :
    QMainWindow(parent)
{
    //this->resize (800,600);

    text_file= new QTextEdit("&Text File: ", this);
    bool ro=text_file->isReadOnly();
    text_file->setReadOnly(ro);

    inLabel = new QLabel(QString("Pages linking to this page"));
    outLabel = new QLabel(QString("Pages this one is linking to"));
    list_incoming= new QListWidget(this);
    list_outcoming= new QListWidget(this);

    RightLayout = new QVBoxLayout;
    mainLayout = new QGridLayout;
    mainWidget = new QWidget;

    RightLayout->addWidget(inLabel);
    RightLayout->addWidget(list_incoming);
    RightLayout->addWidget(outLabel);
    RightLayout->addWidget(list_outcoming);

    mainLayout->addWidget(text_file, 0, 0);
    mainLayout->addLayout(RightLayout, 0, 1);

    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
    /*
    text_file->move (5,10);
    text_file->setFixedSize(500,400);

    list_incoming->setFixedSize(150, 300);
    list_outcoming->setFixedSize(150, 300);

    list_incoming->move (this->width()-list_incoming->width()-10, 10);
    list_outcoming->move (this->width()-list_outcoming->width()-10, 250);*/
    connect(list_incoming, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT (listIncomingDoubleClicked(QListWidgetItem *)));

    connect(list_outcoming, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT (listOutgoingDoubleClicked(QListWidgetItem *)));

   //connect(list_incoming, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT (draw_screen(string, searchApp*)));
   //connect(list_outcoming, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT (draw_screen(string, searchApp*)));

}


secondscreen::~secondscreen(){
    delete text_file;
    delete inLabel;
    delete outLabel;
    delete list_incoming;
    delete list_outcoming;
    delete RightLayout;
    delete mainLayout;
    delete mainWidget;

}
void secondscreen::listIncomingDoubleClicked(QListWidgetItem * item)
{
     string item_convert=item->text().toLocal8Bit().constData();
     draw_screen(item_convert, searchApplication);
}
void secondscreen::listOutgoingDoubleClicked(QListWidgetItem * item)
{
     string item_convert=item->text().toLocal8Bit().constData();
     draw_screen (item_convert, searchApplication);
}
void secondscreen::draw_screen(std::string filename, searchApp* searchApplicationIN){
    searchApplication = searchApplicationIN;
    list_incoming->clear();
    list_outcoming->clear();
    text_file->clear();

    string printer;
    //ifstream input (filename.c_str());
    vector<string> outgoing_links;
    vector<string> incoming_links;
    searchApplication->getPage(filename, printer, outgoing_links, incoming_links);

    //int outgoing_size=outgoing_links.size();
    //int incoming_size=incoming_links.size();
    QString toDisplay(printer.c_str());

    text_file->setPlainText(toDisplay);
    stringstream ss;
    for (unsigned int x=0; x<outgoing_links.size(); x++){
        ss.str(string());
        ss.clear();
        ss <<outgoing_links[x];

        QString out_string (ss.str().c_str());
        QListWidgetItem* insertItem=new QListWidgetItem(out_string);
        list_outcoming->addItem (insertItem);
    }

    stringstream yy;
    for (unsigned int x=0; x<incoming_links.size(); x++){
        yy.str(string());
        yy.clear();
        yy <<incoming_links[x];

        QString in_string (yy.str().c_str());
        QListWidgetItem* insertItem=new QListWidgetItem(in_string);
        list_incoming->addItem (insertItem);
    }
    //this->hide();
}

