#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "peg.h"
#include "link.h"
#include "player.h"
#include "Game.h"

int main(int argc, char *argv[])
{
    //Game g;
    

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
