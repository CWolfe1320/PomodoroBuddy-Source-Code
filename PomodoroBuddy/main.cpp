#include "widget.h"
#include "alertbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Main function of PomodoroBuddy program. Not very flashy. Creates Widget object w and shows it. The w object is the PomodoroBuddy application.

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
