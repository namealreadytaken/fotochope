/*
 * File:   newForm.cpp
 * Author: Samy
 *
 * Created on 7 janvier 2013, 17:28
 */

#include "newForm.h"
#include "resize.h"
#include <QtGui>
#include <iostream>


newForm::newForm() {
    widget.setupUi(this);
    widget.resultLabel->installEventFilter(this);
    //   widget.pushButton->setAutoDefault(false);
    //    connect(widget.pushButton, SIGNAL(clicked()), this, SLOT(checkValues()));
    crop = false;
}

newForm::~newForm() {
}

void newForm::on_loadButton_clicked() {

    QSize resultSize(300, 300);
    protu = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir l'image", "", tr("Images (*.png *.jpg)"));
    QImage image;
    if (!fileName.isEmpty()) {

        image.load(fileName);
        resultSize.setHeight(image.height());
        resultSize.setWidth(image.width());
        widget.resultLabel->setMinimumHeight(resultSize.height());
        widget.resultLabel->setMinimumWidth(resultSize.width());
        //        image = image.scaled(resultSize, Qt::KeepAspectRatio);
        QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&fixedImage);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(fixedImage.rect(), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QPoint((resultSize.width() - image.width()) / 2,
                (resultSize.height() - image.height()) / 2), image);
        painter.end();
        widget.resultLabel->setPixmap(QPixmap::fromImage(fixedImage));

    }

}

void newForm::on_cropButton_clicked() {
    crop = true;

}
void newForm::on_saveButton_clicked() {
     QImage img = widget.resultLabel->pixmap()->toImage();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer l'image"), "", tr("Image PNG (*.png);;Image JPG (*.jpg)"));
    if (!fileName.isEmpty()) {
         img.save(fileName);
    }

}

void newForm::setLabelSize(QSize s) {
    widget.resultLabel->setMinimumHeight(s.height());
    widget.resultLabel->setMinimumWidth(s.width());
    widget.scrollAreaWidgetContents->adjustSize();
}


void newForm::setImage(QImage i) {
    widget.resultLabel->setPixmap(QPixmap::fromImage(i));
}

void newForm::on_resizeButton_clicked(){
    Resize* r = new Resize(widget.resultLabel->pixmap()->toImage());
    r->show();
}

bool newForm::eventFilter(QObject* watched, QEvent* event) {
    if (watched != widget.resultLabel)
        return false;
    if (event->type() != QEvent::MouseButtonPress && event->type() != QEvent::MouseButtonRelease)
        return false;
    const QMouseEvent * const me = static_cast<const QMouseEvent*> (event);
    //might want to check the buttons here
    QPoint p = me->globalPos(); //...or ->globalPos();
    p = widget.resultLabel->mapFromGlobal(p);
    pipette=true;
    if (crop) {
        if (event->type() == QEvent::MouseButtonPress) {
            pstart = p;
        } else if (event->type() == QEvent::MouseButtonRelease) {
            QImage img = widget.resultLabel->pixmap()->toImage();
            QImage* cropped = new QImage(abs(pstart.x() - p.x()), abs(pstart.y() - p.y()), QImage::Format_ARGB32_Premultiplied);
            for (int i = std::min(pstart.x(), p.x()); i < std::max(pstart.x(), p.x()); i++) {
                for (int j = std::min(pstart.y(), p.y()); j < std::max(pstart.y(), p.y()); j++) {
                    cropped->setPixel(i - std::min(pstart.x(), p.x()), j - std::min(pstart.y(), p.y()), img.pixel(i, j));
                }
            }
            widget.resultLabel->setPixmap(QPixmap::fromImage(*cropped));
            widget.resultLabel->adjustSize();
            widget.scrollAreaWidgetContents->adjustSize();

            crop = false;
        }
    }
    else if(pipette)
    {
        QRgb px = widget.resultLabel->pixmap()->toImage().pixel(p.x(), p.y());
        QColor* color = new QColor(px);
        int r,g,b,a;
        color->getRgb(&r,&g,&b,&a);
        std::cout<<r<<g<<b<<a<<std::endl;
        pipette=false;
    }
    return false;
}
