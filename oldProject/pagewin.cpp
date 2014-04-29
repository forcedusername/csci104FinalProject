#include "pagewin.h"
#include <QString>
#include <deque>

PageWin::PageWin(WebPage * w, map<string, WebPage*> pages, QWidget *parent) : QMainWindow(parent)
{
   // _webpage = w;
   _pages = pages;
    const QString title = QString::fromStdString(w->filename());
    setWindowTitle(title);

    mainLayout = new QHBoxLayout;
    rightLayout = new QVBoxLayout;

    labelIncoming = new QLabel("Incoming Links");
    labelOutgoing = new QLabel("Outgoing Links");

    listIncoming = new QListWidget;
    listIncoming->setSortingEnabled(true);
    listOutgoing = new QListWidget;
    listOutgoing->setSortingEnabled(true);
    
    centerWidget = new QWidget(this);
    centerWidget->setLayout(mainLayout);
    this->setCentralWidget(centerWidget);

    rightLayout->addWidget(labelIncoming);
    rightLayout->addWidget(listIncoming);
    rightLayout->addWidget(labelOutgoing);
    rightLayout->addWidget(listOutgoing);
           
    string text = " ";
    for (deque<string>::iterator it = w->word_lines.begin(); it != w->word_lines.end(); ++it)
    {
    	text += *it;
    }
    textArea = new QTextEdit(QString::fromStdString(text));

    mainLayout->addWidget(textArea, 0);
     mainLayout->addLayout(rightLayout, 1);


    Set<WebPage*> incomingLinks = w->allIncomingLinks();
    for (Set<WebPage*>::iterator it = incomingLinks.begin(); it != incomingLinks.end(); ++it)
    {
	listIncoming->addItem(new QListWidgetItem(QString::fromStdString((*it)->filename())));
    }
    Set<WebPage*> outgoingLinks = w->allOutgoingLinks();
    for (Set<WebPage*>::iterator it = outgoingLinks.begin(); it != outgoingLinks.end(); ++it)
    {
	listOutgoing->addItem(new QListWidgetItem(QString::fromStdString((*it)->filename())));
    }

    connect(listIncoming, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(recreate(QListWidgetItem*)));
    connect(listOutgoing, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(recreate(QListWidgetItem*)));
    this->show();
}
PageWin::~PageWin()
{
  
}
void PageWin::recreate(QListWidgetItem* item)
{
    QString title = item->text();
     listIncoming->clear();
    listOutgoing->clear();

    //cerr << "1" << endl;
    setWindowTitle(title);
    //cerr << "2" << endl;
    string filename = title.toStdString();
    WebPage * w = _pages[filename];

    string text = " ";
    for (deque<string>::iterator it = w->word_lines.begin(); it != w->word_lines.end(); ++it)
    {
    	text += *it;
    }
    textArea->clear();
    textArea->setPlainText(QString::fromStdString(text));
    Set<WebPage*> incomingLinks = w->allIncomingLinks();
    for (Set<WebPage*>::iterator it = incomingLinks.begin(); it != incomingLinks.end(); ++it)
    {
	listIncoming->addItem(new QListWidgetItem(QString::fromStdString((*it)->filename())));
    }
    Set<WebPage*> outgoingLinks = w->allOutgoingLinks();
    for (Set<WebPage*>::iterator it = outgoingLinks.begin(); it != outgoingLinks.end(); ++it)
    {
	listOutgoing->addItem(new QListWidgetItem(QString::fromStdString((*it)->filename())));
    }
    this->show();
}
