/*
 * File:   resize.cpp
 * Author: XXX
 *
 * Created on 11 janvier 2013, 11:36
 */

#include "resize.h"
#include <QtGui>
#include <iostream>

QImage image;

Resize::Resize() {
    widget.setupUi(this);
}

Resize::Resize(newForm* p, QImage im) {
    widget.setupUi(this);
    image = im;
    pere = p;
}

Resize::~Resize() {
}

void Resize::on_cancelButton_clicked() {
    this->close();
}

void Resize::on_okButton_clicked() {
    bool a = false;
    bool b = false;
    widget.height->text().toInt(&a);
    widget.width->text().toInt(&b);
    if (a && b) {
        pere->setImage(resizeI(image, widget.width->text().toInt(), widget.height->text().toInt()));
        this->close();
    }

}

QImage resizeI(QImage image, int width, int height) {
    QRgb px;
    double ratiov = double(image.height()) / double(height);
    double ratioh = double(image.width()) / double(width);
    std::cout << ratiov << ratioh << std::endl;
    QImage* image2 = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    QImage* image3 = new QImage(image.width(), height, QImage::Format_ARGB32_Premultiplied);
    if (ratiov > 1) {// on fait la diminution verticale
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j += ratiov) {
                image3->setPixel(i, j / ratiov, image.pixel(i, j));
            }
        }
    } else {
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j++) {
                px = image.pixel(i, j);
                for (int k = j * ((double) 1 / ratiov); k <= j * ((double) 1 / ratiov) + ((double) 1 / ratiov); k++) {
                    image3->setPixel(i, k, px);
                }
            }
        }
    }

    if (ratioh > 1) {// on fait la diminution horizontale
        for (int i = 0; i < image3->width(); i += ratioh) {
            for (int j = 0; j < image3->height(); j++) {
                image2->setPixel(i / ratioh, j, image3->pixel(i, j));
            }
        }
    } else {
        for (int i = 0; i < image3->width(); i++) {
            for (int j = 0; j < image3->height(); j++) {
                px = image3->pixel(i, j);
                for (int k = i * ((double) 1 / ratioh); k <= i * ((double) 1 / ratioh) +((double) 1 / ratioh); k++) {
                    image2->setPixel(k, j, px);
                }
            }
        }
    }
    return *image2;
}