/*
 * File:   newForm.cpp
 * Author: Samy
 *
 * Created on 7 janvier 2013, 17:28
 */
#include "Histogramme.h"
#include "newForm.h"
#include "resize.h"
#include "Pipette.h"
#include <QtGui>
#include <iostream>

newForm::newForm() {
    widget.setupUi(this);
    widget.resultLabel->installEventFilter(this);
    crop = false;
    pipette = false;
}

newForm::~newForm() {
}

void newForm::on_loadButton_clicked() {

    QString fileName = QFileDialog::getOpenFileName(this, "Choisir l'image", "", tr("Images (*.png *.jpg *.gif *.pnm)"));
    QImage image;
    if (!fileName.isEmpty()) {
        image.load(fileName);
        setImage(image);
        img = image;
    }
}

void newForm::on_cropButton_clicked() {
    crop = true;
}

void newForm::on_pipetteButton_clicked() {
    pipette = true;
}

void newForm::on_greyButton_clicked() {
    greyScale();
}

void newForm::on_blurButton_clicked() {
    blur();
}

void newForm::on_saveButton_clicked() {
    QImage image = widget.resultLabel->pixmap()->toImage();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer l'image"), "", tr("Image PNG (*.png);;Image JPG (*.jpg)"));
    if (!fileName.isEmpty()) {
        image.save(fileName);
    }

}

void newForm::setLabelSize(QSize s) {
    widget.resultLabel->setMinimumHeight(s.height());
    widget.resultLabel->setMinimumWidth(s.width());
    widget.resultLabel->setMaximumHeight(s.height());
    widget.resultLabel->setMaximumWidth(s.width());
    widget.scrollAreaWidgetContents->adjustSize();
}

void newForm::setImage(QImage i) {
    setLabelSize(i.size());
    widget.resultLabel->setPixmap(QPixmap::fromImage(i));
}

void newForm::on_resizeButton_clicked() {
    Resize* r = new Resize(this, widget.resultLabel->pixmap()->toImage());
    r->show();
}

void newForm::on_histoButton_clicked() {
    Histogramme* h = new Histogramme(widget.resultLabel->pixmap()->toImage());
    h->show();
}

bool newForm::eventFilter(QObject* watched, QEvent* event) {
    if (watched != widget.resultLabel)
        return false;
    if (event->type() != QEvent::MouseButtonPress && event->type() != QEvent::MouseButtonRelease)
        return false;
    const QMouseEvent * const me = static_cast<const QMouseEvent*> (event);
    QPoint p = me->globalPos();
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
            setImage(*cropped);
            crop = false;
        }
    } else if (pipette) {
        QRgb px = widget.resultLabel->pixmap()->toImage().pixel(p.x(), p.y());
        Pipette* pi = new Pipette(qRed(px), qGreen(px), qBlue(px));
        pi->show();
        pipette = false;
    }
    return false;
}

void newForm::greyScale() {
    QImage image = widget.resultLabel->pixmap()->toImage();
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            image.setPixel(i, j, pxToGrey(image.pixel(i, j)));
        }
    }
    setImage(image);
}

QRgb newForm::pxToGrey(QRgb px) {
    int a = (qRed(px)*0.21 + 0.71 * qGreen(px) + 0.07 * qBlue(px)); //d'apr�s la C.I.E (Commission Internationale de l'�clairage)
    return qRgba(a, a, a, qAlpha(px));
}

void newForm::blur() {
    int sum[4];
    int radius = 2, out;

    QImage image = widget.resultLabel->pixmap()->toImage();
    QImage dest = image;
    QImage tmp = image;
    QRgb rgb;
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            for (int s = 0; s < 4; s++)
                sum[s] = 0;
            out = 0;
            for (int kx = -radius; kx <= radius; ++kx) {
                if (i + kx < image.width() && i + kx >= 0) {
                    rgb = image.pixel(i + kx, j);
                    sum[0] += qRed(rgb);
                    sum[1] += qGreen(rgb);
                    sum[2] += qBlue(rgb);
                    sum[3] += qAlpha(rgb);
                } else {
                    out++;
                }
            }
            tmp.setPixel(i, j, qRgba(sum[0] / (radius * 2 + 1 - out), sum[1] / (radius * 2 + 1 - out), sum[2] / (radius * 2 + 1 - out), sum[3] / (radius * 2 + 1 - out)));
        }
    }
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            for (int s = 0; s < 4; s++)
                sum[s] = 0;
            out = 0;
            for (int ky = -radius; ky <= radius; ++ky) {

                if (j + ky < image.height() && j + ky >= 0) {
                    rgb = tmp.pixel(i, j + ky);
                    sum[0] += qRed(rgb);
                    sum[1] += qGreen(rgb);
                    sum[2] += qBlue(rgb);
                    sum[3] += qAlpha(rgb);
                } else {
                    out++;
                }
            }
            dest.setPixel(i, j, qRgba(sum[0] / (radius * 2 + 1 - out), sum[1] / (radius * 2 + 1 - out), sum[2] / (radius * 2 + 1 - out), sum[3] / (radius * 2 + 1 - out)));
        }
    }
    setImage(dest);
}

void newForm::Sobel() {
    int GX[3][3];
    int GY[3][3];
    /* 3x3 GX Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
    GX[0][0] = -1;
    GX[0][1] = 0;
    GX[0][2] = 1;
    GX[1][0] = -2;
    GX[1][1] = 0;
    GX[1][2] = 2;
    GX[2][0] = -1;
    GX[2][1] = 0;
    GX[2][2] = 1;

    /* 3x3 GY Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
    GY[0][0] = 1;
    GY[0][1] = 2;
    GY[0][2] = 1;
    GY[1][0] = 0;
    GY[1][1] = 0;
    GY[1][2] = 0;
    GY[2][0] = -1;
    GY[2][1] = -2;
    GY[2][2] = -1;
    QImage source = widget.resultLabel->pixmap()->toImage();
    QImage sobelDestination = source;
    int width = source.width();
    int height = source.height();
    int I, J;
    long sumX, sumY;
    int SUM;
    uint rawColour;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (y == 0 || y >= height - 1 || x == 0 || x >= width - 1) {
                SUM = 0;
            } else {
                sumX = 0;
                sumY = 0;
                /*-------X and Y GRADIENT APPROXIMATION------*/
                for (I = -1; I <= 1; I++) {
                    for (J = -1; J <= 1; J++) {
                        rawColour = source.pixel(x + I, y + J);
                        sumX = sumX + ((qRed(rawColour) + qGreen(rawColour) + qBlue(rawColour)) / 3) * GX[I + 1][J + 1];
                        sumY = sumY + ((qRed(rawColour) + qGreen(rawColour) + qBlue(rawColour)) / 3) * GY[I + 1][J + 1];
                    }
                }
                SUM = abs(sumX) + abs(sumY); /*---GRADIENT MAGNITUDE APPROXIMATION (Myler p.218)----*/
                if (SUM > 255)
                    SUM = 255;

            }
            sobelDestination.setPixel(x, y, qRgb(SUM, SUM, SUM));
        }
        setImage(sobelDestination);
    }
}
