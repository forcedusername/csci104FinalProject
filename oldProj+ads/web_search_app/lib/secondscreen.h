#ifndef secondscreen_H
#define secondscreen_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <string>

#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFormLayout>
#include <QLabel>


#include "search.h"
#include "ad_display.h"

#include <fstream>
#include <sstream>
#include <string>

class searchApp;
class secondscreen : public QMainWindow
{
    Q_OBJECT
public:
    secondscreen(QWidget *parent = 0);
    ~secondscreen();

    //void draw_screen (std::string filename, searchApp* searchApplication);

     void draw_screen (string filename, searchApp *searchApplication);
signals:

public slots:
    // connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT (listWidgetDoubleClicked(QListWidgetItem *)));

     void listIncomingDoubleClicked(QListWidgetItem * item);
     void listOutgoingDoubleClicked(QListWidgetItem * item);
private:
    QTextEdit* text_file;
    QListWidget* list_incoming;
    QListWidget* list_outcoming;
    QLabel* inLabel;
    QLabel* outLabel;

    QVBoxLayout* RightLayout;
    QGridLayout* mainLayout;
    QWidget* mainWidget;
    
    searchApp* searchApplication;
    ad_display* advertisements;

};

#endif // secondscreen_H
