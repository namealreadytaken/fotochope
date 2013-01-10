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
    this->setWindowTitle("protu");




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
        QPainter painter(&fixedImage);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(fixedImage.rect(), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QPoint(0, 0), image);
        painter.end();
        fixedImage = form->resize(fixedImage, 1500, 1500);

        form->setImage(fixedImage);
        form->setWindowTitle(fileName);
        form->show();

    }
}
