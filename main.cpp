#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Workaround for windows
    #if (defined (_WIN32) || defined (_WIN64))
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(42,197,136));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    qApp->setPalette(p);
    #endif

    MainWindow w;
    w.show();
    return a.exec();
}
