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
    widget.resultLabel->installEventFilter(this);
    //   widget.pushButton->setAutoDefault(false);
    //    connect(widget.pushButton, SIGNAL(clicked()), this, SLOT(checkValues()));
    crop = false;
}

newForm::~newForm() {
}

void newForm::on_pushButton_clicked() {

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
        fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer l'image"), "", tr("Image PNG (*.png);;Image JPG (*.jpg)"));
        if (!fileName.isEmpty()) {
            fixedImage.save(fileName);
        }
    }

}

void newForm::on_cropButton_clicked() {
    crop = true;

}

void newForm::setLabelSize(QSize s) {
    widget.resultLabel->setMinimumHeight(s.height());
    widget.resultLabel->setMinimumWidth(s.width());
    widget.scrollAreaWidgetContents->adjustSize();


}

void newForm::setImage(QImage i) {
    widget.resultLabel->setPixmap(QPixmap::fromImage(i));
}

QImage newForm::resize(QImage image, int width, int height) {

    double ratiov = double(image.height()) / double(height);
    double ratioh = double(image.width()) / double(width);
    std::cout << ratiov << ratioh << std::endl;
    QImage* image2 = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    QImage* image3 = new QImage(image.width(), height, QImage::Format_ARGB32_Premultiplied);
    if (ratiov > 1) {// on fait la diminution verticale
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j+=ratiov) {
                image3->setPixel(i, j/ratiov, image.pixel(i, j));
            }
        }
    } else {
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j++) {
                //          image3->setPixel(i, j, image.pixel(i, int(j * ratiov)));
                for (int k = j * (double) ((double) 1 / ratiov); k <= j * (double) ((double) 1 / ratiov) + (double) ((double) 1 / ratiov); k++) {
                    image3->setPixel(i, k, image.pixel(i, j));
                }
            }
        }
    }

    if (ratioh > 1) {// on fait la diminution horizontale
        for (int i = 0; i < image3->width(); i+=ratioh) {
            for (int j = 0; j < image3->height(); j++) {
                image2->setPixel(i/ratioh, j, image3->pixel(i, j));
            }
        }
    } else {
        for (int i = 0; i < image3->width(); i++) {
            for (int j = 0; j < image3->height(); j++) {
                for (int k = i * (double) ((double) 1 / ratioh); k < i * (double) ((double) 1 / ratioh) + (double) ((double) 1 / ratiov); k++) {
                    image2->setPixel(k, j, image3->pixel(i, j));
                }
            }
        }
    }
    return *image2;
    //    QImage* image2;
    //    image2 = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    //    for (int i = 0; i < image.width(); i = i + ratioh) {
    //        for (int j = 0; j < image.height(); j = j + ratiov) {
    //            image2->setPixel(i / ratioh, j / ratiov, image.pixel(i, j));
    //        }
    //    }
    //    return *image2;
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
    return false;
}
