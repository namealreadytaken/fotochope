/*
 * File:   MainMenu.cpp
 * Author: Samy
 *
 * Created on 9 janvier 2013, 05:19
 */

#include "MainMenu.h"
#include "baseWindow.h"
#include <QtGui>

MainMenu::MainMenu() {
    widget.setupUi(this);
}

MainMenu::~MainMenu() {
}

void MainMenu::on_actionOuvrir_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir l'image", "", tr("Images (*.png *.jpg *.gif *.pnm)"));
    QImage image;
    if (!fileName.isEmpty()) {

        baseWindow* form = new baseWindow();
        image.load(fileName);
        form->setImage(image);
        form->setWindowTitle(fileName);
        form->showMaximized();

    }
}
