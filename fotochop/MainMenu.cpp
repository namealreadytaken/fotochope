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
        resultSize.setHeight(1500);
        resultSize.setWidth(1500);
        form->setLabelSize(resultSize);
        resultSize.setHeight(image.height());
        resultSize.setWidth(image.width());
        QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        fixedImage = form->resize(image, 1500, 1500);

        form->setImage(fixedImage);
        form->setWindowTitle(fileName);
        form->show();

    }
}
