#include "MainWindow.hpp"

#include <QApplication>
#include <QIcon>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a{ argc, argv };
    MainWindow w;
    w.show();

    if (argc > 1)
        w.loadFile(argv[1]);

    return a.exec();
}
