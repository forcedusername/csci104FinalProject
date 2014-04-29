#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QRadioButton>
#include <lib/Set.h>
#include "WebPage.h"
#include <map>
#include <deque>
#include <sstream>
#include <fstream>

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();
    void addPagesFromFile(char* filename);
    void displayResults(Set<WebPage*> &  w);
    void calcPageRank(Set<WebPage * > & w);
private slots:
    void doSearch();
    void doAnd();
    void doOr();
    void showInfo();
    void displayPage(QListWidgetItem * item);

private:
    QVBoxLayout * mainLayout;
    QHBoxLayout * topLayout;
    QHBoxLayout * radioBtnLayout;
    QHBoxLayout * bottomLayout;
    QLineEdit * txtQuery;
    QPushButton * btnSearch;
    QPushButton * btnAnd;
    QPushButton * btnOr;
    QListWidget * resultsList;
    QWidget * centerWidget;
    QPushButton * btnInfo;
    QPushButton * btnQuit;
    QRadioButton * sortRankBtn;
    QRadioButton * sortNameBtn;
    
    map< string, WebPage*> pages; //maps filenames to WebPage pointers
    map< string, Set<WebPage*> > queries; //maps string query to  webpage pointer

    string toLowerCase(string s);
};

#endif // MAINWIN_H
