#include "msort.h"
#include "firstscreen.h"
#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc < 2)
    {
        std::cout << "No datafile name given\n";
        return 0;
    }
    FirstScreen window(argv[1]);
    window.setWindowTitle("Search Application");
    window.show();

    return a.exec();
}
