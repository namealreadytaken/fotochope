/*
 * File:   Fusion.cpp
 * Author: XXX
 *
 * Created on 21 janvier 2013, 15:00
 */

#include <iostream>
#include "Fusion.h"
#include <QtGui>
#include "resize.h"


Fusion::Fusion(baseWindow * p, QImage im1, QImage im2) {
    widget.setupUi(this);
    img1 = im1; //image de base
    w1 = img1.width();
    h1 = img1.height();
    pere = p;
    img2 = resizeI(im2, w1, h1);
    setLabelSize(img1.size());
    widget.label->setPixmap(QPixmap::fromImage(im1));
}

Fusion::~Fusion() {
}

void Fusion::setImage(QImage i) {
    setLabelSize(i.size());
    widget.label->setPixmap(QPixmap::fromImage(i));
}

void Fusion::on_horizontalSlider_valueChanged() {

    imgResult = new QImage(w1, h1, QImage::Format_ARGB32_Premultiplied);
    int r, g, b;

    QRgb pix1, pix2;
    double val = (double) widget.horizontalSlider->value() / (double) 100;
    for (int i = 0; i < w1; i++) {
        for (int j = 0; j < h1; j++) {
            pix1 = img1.pixel(i, j);
            pix2 = img2.pixel(i, j);

            r = (qRed(pix1) * (1 - val) + qRed(pix2) * val * (1 - (1 - val))) / ((1 - val) + val * (1 - (1 - val)));
            g = (qGreen(pix1) * (1 - val) + qGreen(pix2) * val * (1 - (1 - val))) / ((1 - val) + val * (1 - (1 - val)));
            b = (qBlue(pix1) * (1 - val) + qBlue(pix2) * val * (1 - (1 - val))) / ((1 - val) + val * (1 - (1 - val)));

            imgResult->setPixel(i, j, qRgb(r, g, b));
        }
    }
    setLabelSize(imgResult->size());
    setImage(*imgResult);
}

void Fusion::setLabelSize(QSize s) {
    widget.label->setMinimumHeight(s.height());
    widget.label->setMinimumWidth(s.width());
    widget.label->setMaximumHeight(s.height());
    widget.label->setMaximumWidth(s.width());
}

void Fusion::on_okButton_clicked(){
    pere->setImage(*imgResult);
    this->close();
}