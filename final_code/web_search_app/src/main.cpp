#include "msort.h"
#include "firstscreen.h"
#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc < 4)
    {
        std::cout << "No datafile or no advertiser name given or no outputfile\n";
        return 0;
    }
    FirstScreen window(argv[1], argv [2], argv [3]);
    window.setWindowTitle("Search Application");
    window.show();

    return a.exec();
}
