/*
 * File:   MainMenu.cpp
 * Author: Samy
 *
 * Created on 9 janvier 2013, 05:19
 */

#include "MainMenu.h"
#include "newForm.h"
#include <QtGui>

MainMenu::MainMenu() {
    widget.setupUi(this);
}

MainMenu::~MainMenu() {
}

void MainMenu::on_actionOuvrir_triggered() {
    QSize resultSize(300, 300);
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir image");
    QImage image;
    if (!fileName.isEmpty()) {

        newForm* form = new newForm();
        image.load(fileName);
        resultSize.setHeight(image.height());
        resultSize.setWidth(image.width());
        form->setLabelSize(resultSize);
 //       QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        //fixedImage = form->resize(image, 1500, 1500);

        form->setImage(image);
        form->setWindowTitle(fileName);
        form->show();

    }
}
