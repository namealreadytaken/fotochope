/*
 * File:   greyScale.cpp
 * Author: XXX
 *
 * Created on 31 janvier 2013, 01:46
 */

#include "greyScale.h"
#include <algorithm> 

greyScale::greyScale(baseWindow* p) {
    widget.setupUi(this);
    pere = p;
}

greyScale::~greyScale() {
}

void greyScale::on_okButton_clicked() {
    QImage image = pere->img;
    if (widget.greyType->currentText() == "Average") {
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j++) {
                image.setPixel(i, j, pxToGreyAverage(image.pixel(i, j)));
            }
        }
    }
    if (widget.greyType->currentText() == "CEI") {
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j++) {
                image.setPixel(i, j, pxToGreyCEI(image.pixel(i, j)));
            }
        }
    }
    if (widget.greyType->currentText() == "Desaturation") {
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j++) {
                image.setPixel(i, j, pxToGreyDesaturation(image.pixel(i, j)));
            }
        }

    }
    pere->setImage(image);
    this->close();
}

QRgb greyScale::pxToGreyAverage(QRgb px) {
    int a = (qRed(px) + qGreen(px) + qBlue(px)) / 3;
    return qRgba(a, a, a, qAlpha(px));
}

QRgb greyScale::pxToGreyCEI(QRgb px) {
    int a = (qRed(px)*0.21 + 0.71 * qGreen(px) + 0.07 * qBlue(px)); //d'après la C.I.E (Commission Internationale de l'Éclairage)
    return qRgba(a, a, a, qAlpha(px));
}

QRgb greyScale::pxToGreyDesaturation(QRgb px) {
    int a = (std::max(std::max(qRed(px), qGreen(px)), qBlue(px)) + std::min(std::min(qRed(px), qGreen(px)), qBlue(px))) / 2;
    return qRgba(a, a, a, qAlpha(px));
}