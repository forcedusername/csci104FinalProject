#ifndef FIRSTSCREEN_H
#define FIRSTSCREEN_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QString>
#include <string>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFormLayout>
#include <QDataStream>
#include <cstdlib>
#include "secondscreen.h"
using namespace std;

class searchApp;
class ad_display;
class FirstScreen : public QMainWindow
{
    Q_OBJECT

    public:
        FirstScreen(std::string datafileName, QWidget *parent = 0);
        ~FirstScreen();
         void print_to_list(std::vector<std::string> queryMatches, QListWidget* listWidget);


    protected:
       // void closeEvent(QCloseEvent *event);


    private slots:
        void alphaSort();
        void rankSort();
        void Search();
        void showAbout();
        void listWidgetDoubleClicked(QListWidgetItem * item);
       // void print_to_list();

    private:
        bool opened;
        secondscreen* save;

        QPushButton * btnSearch;
        QPushButton * btnAbout;
        QPushButton * btnQuit;
        QLineEdit   * lineEditInput;
        QListWidget   * listWidget;

        QPushButton * aSort;
        QPushButton * rSort;
        //Layouts
        QHBoxLayout * inputLine;
        QHBoxLayout * sortLine;
        QHBoxLayout * bottomLine;
        QVBoxLayout * mainLayout;
        QWidget * mainWidget;

        searchApp   * searchApplication;
        ad_display* advertisements;

};


#endif // FIRSTSCREEN_H
