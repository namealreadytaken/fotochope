/*
 * File:   newForm.cpp
 * Author: Samy
 *
 * Created on 7 janvier 2013, 17:28
 */

#include "newForm.h"
#include <QtGui>
#include <iostream>
newForm::newForm() {
    widget.setupUi(this);
    //   widget.pushButton->setAutoDefault(false);
    //    connect(widget.pushButton, SIGNAL(clicked()), this, SLOT(checkValues()));

}

newForm::~newForm() {
}

void newForm::on_pushButton_clicked() {

    QSize resultSize(300, 300);
    protu = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir l'image","",tr("Images (*.png *.jpg)"));
    QImage image;
    if (!fileName.isEmpty()) {
       
        image.load(fileName);
        resultSize.setHeight(image.height());
        resultSize.setWidth(image.width());
        widget.resultLabel->setMinimumHeight(resultSize.height());
        widget.resultLabel->setMinimumWidth(resultSize.width());
        
        this->setWindowTitle("LOLILOL");
        image = image.scaled(resultSize, Qt::KeepAspectRatio);
        QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&fixedImage);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(fixedImage.rect(), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QPoint((resultSize.width() - image.width()) / 2,
                (resultSize.height() - image.height()) / 2), image);
        painter.end();
        widget.resultLabel->setPixmap(QPixmap::fromImage(fixedImage));
fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer l'image"),"",tr("Image PNG (*.png);;Image JPG (*.jpg)"));
        if (!fileName.isEmpty()) {
            fixedImage.save(fileName);
        }
    }
    
}