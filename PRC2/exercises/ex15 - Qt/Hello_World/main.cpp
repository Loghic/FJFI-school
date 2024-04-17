#include <QApplication>
#include "QPushButton"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QPushButton btnHello(QObject::tr("&Hello Qt!")); // btnHello name of the instance; QObject passing name on button
    btnHello.show(); // to show the object
    QObject::connect(&btnHello, SIGNAL(clicked()), &a, SLOT(quit()));


    return a.exec();
}
