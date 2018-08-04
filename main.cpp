#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
 QApplication app(argc, argv);
 app.setStyle("plastique");

 MainWindow w;
 w.show();

 app.setQuitOnLastWindowClosed(1);
 return app.exec();
}
