/* Author: Evgenij Markin
 * Development framework: Qt5.12.9
 * Description: вьювер zip-архивов.
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
