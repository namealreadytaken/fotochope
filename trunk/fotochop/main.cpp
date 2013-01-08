/*
 * File:   main.cpp
 * Author: Samy
 *
 * Created on 7 janvier 2013, 16:42
 */

#include <QtGui/QApplication>
#include "newForm.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    newForm form;
    form.show();
    // create and show your widgets here
    return app.exec();
}

