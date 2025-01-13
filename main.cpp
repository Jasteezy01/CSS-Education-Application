/*
 * File: main.cpp
 * Contributors:
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Added comment.
 *
 * Date of Most Recent Update:
 *   11/26/2024
 *
 * Description:
 *   Designed to be used in The Best Developers Education Application.
 */

#include "mainwindow.h"
#include "flexboxmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlexboxModel model;
    MainWindow w(model);
    w.show();
    return a.exec();
}
