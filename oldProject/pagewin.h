#ifndef PAGEWIN_H
#define PAGEWIN_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QString>
#include <QTextEdit>
#include <lib/Set.h>
#include "WebPage.h"
#include <map>
#include <deque>
#include <sstream>
#include <fstream>


class PageWin : public QMainWindow
{
    Q_OBJECT

public:
    PageWin(WebPage* w, map<string, WebPage*> pages, QWidget *parent = 0);
    ~PageWin();
private slots:
    void recreate(QListWidgetItem* item);
private:
    QWidget * centerWidget;
    QHBoxLayout * mainLayout;
    QVBoxLayout * rightLayout;
    QTextEdit * textArea;
    QLabel * labelIncoming;
    QLabel * labelOutgoing;
    QListWidget * listIncoming;
    QListWidget * listOutgoing;
    map<string, WebPage*> _pages;
   // WebPage * _webpage;

    
};
#endif // PAGEWIN_H
