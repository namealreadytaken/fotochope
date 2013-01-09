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
        resultSize.setHeight(image.height());
        resultSize.setWidth(image.width());
        form->setLabelSize(resultSize);
        QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&fixedImage);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(fixedImage.rect(), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QPoint((resultSize.width() - image.width()) / 2, (resultSize.height() - image.height()) / 2), image);
        painter.end();
        form->setImage(fixedImage);
        form->setWindowTitle(fileName);
        form->show();
        
    }
}
