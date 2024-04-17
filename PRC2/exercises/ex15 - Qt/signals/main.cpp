#include "signaldemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignalDemo w;
    QObject::connect(&w, SIGNAL(quitting()), &a, SLOT(quit())); // broadcasting information from another function
    w.show();
    return a.exec();
}
