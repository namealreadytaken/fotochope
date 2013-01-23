/*
 * File:   baseWindow.cpp
 * Author: XXX
 *
 * Created on 22 janvier 2013, 22:45
 */

#include "Histogramme.h"
#include "baseWindow.h"
#include "resize.h"
#include "Pipette.h"
#include "Fusion.h"
#include "filtre.h"
#include <QtGui>
#include <iostream>
#include <QDesktopWidget>

baseWindow::baseWindow() {

    widget.setupUi(this);
    widget.resultLabel->installEventFilter(this);
    pipette = false;
    selectZone = false;
    selectSet = false;
}

baseWindow::~baseWindow() {
}

void baseWindow::on_loadButton_clicked() {

    QString fileName = QFileDialog::getOpenFileName(this, "Choisir l'image", "", tr("Images (*.png *.jpg *.gif *.pnm)"));
    QImage image;
    if (!fileName.isEmpty()) {
        image.load(fileName);
        setImage(image);
        img = image;
    }
}

void baseWindow::on_cropButton_clicked() {
    QImage image = img;
    QImage* cropped = new QImage(abs(pstart.x() - pend.x()), abs(pstart.y() - pend.y()), QImage::Format_ARGB32_Premultiplied);
    for (int i = std::min(pstart.x(), pend.x()); i < std::max(pstart.x(), pend.x()); i++) {
        for (int j = std::min(pstart.y(), pend.y()); j < std::max(pstart.y(), pend.y()); j++) {
            cropped->setPixel(i - std::min(pstart.x(), pend.x()), j - std::min(pstart.y(), pend.y()), image.pixel(i, j));
        }
    }
    selectSet = false;
    setImage(*cropped);
}

void baseWindow::on_selectButton_clicked() {
    selectZone = true;
}

void baseWindow::on_pipetteButton_clicked() {
    pipette = true;
}

void baseWindow::on_greyButton_clicked() {
    greyScale();
}

void baseWindow::on_blurButton_clicked() {
    blur();
}

void baseWindow::on_fusionButton_clicked() {


    QString fileName = QFileDialog::getOpenFileName(this, "Choisir l'image", "", tr("Images (*.png *.jpg *.gif *.pnm)"));
    QImage image;
    if (!fileName.isEmpty()) {
        image.load(fileName);
        Fusion* f = new Fusion(this, img, image);
        f->showMaximized();
    }

}

void baseWindow::on_filtreButton_clicked() {

    Filtre* f = new Filtre(this);
    f->show();
}

void baseWindow::on_saveButton_clicked() {
    QImage image = img;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer l'image"), "", tr("Image PNG (*.png);;Image JPG (*.jpg);;Image BMP (*.bmp);;Image TIFF (*.tiff)"));
    if (!fileName.isEmpty()) {
        image.save(fileName);
    }
}

void baseWindow::setLabelSize(QSize s) {
    widget.resultLabel->setMinimumSize(s);
    widget.resultLabel->setMaximumSize(s);
    //this->adjustSize();
}

void baseWindow::setImage(QImage i) {
    setLabelSize(i.size());
    img = i;
    widget.resultLabel->setPixmap(QPixmap::fromImage(i));
}

void baseWindow::setPixmap(QImage i) {
    setLabelSize(i.size());
    widget.resultLabel->setPixmap(QPixmap::fromImage(i));
}

void baseWindow::on_resizeButton_clicked() {
    Resize* r = new Resize(this, img);
    r->show();
}

void baseWindow::on_histoButton_clicked() {
    Histogramme* h = new Histogramme(this, img);
    h->show();
}

bool baseWindow::eventFilter(QObject* watched, QEvent* event) {
    if (watched != widget.resultLabel)
        return false;
    if (event->type() != QEvent::MouseButtonPress && event->type() != QEvent::MouseButtonRelease)
        return false;
    const QMouseEvent * const me = static_cast<const QMouseEvent*> (event);
    QPoint p = me->globalPos();
    p = widget.resultLabel->mapFromGlobal(p);
    if (pipette) {
        QRgb px = img.pixel(p.x(), p.y());
        Pipette* pi = new Pipette(qRed(px), qGreen(px), qBlue(px));
        pi->show();
        pipette = false;
    } else if (selectZone) {
        if (selectSet) {
            if (event->type() == QEvent::MouseButtonPress) {
                if (p.x() >= std::min(pstart.x(), pend.x()) && p.x() <= std::max(pstart.x(), pend.x()) && p.y() >= std::min(pstart.y(), pend.y()) && p.y() <= std::max(pstart.y(), pend.y())) {
                    pdragstart = p;
                } else {
                    setImage(img);
                    selectZone = !selectZone;
                }
            } else if (event->type() == QEvent::MouseButtonRelease) {
                pdragend = p;
                QImage image = img;
                pstart.setX(pstart.x() + pdragend.x() - pdragstart.x());
                pstart.setY(pstart.y() + pdragend.y() - pdragstart.y());
                pend.setX(pend.x() + pdragend.x() - pdragstart.x());
                pend.setY(pend.y() + pdragend.y() - pdragstart.y());
                for (int i = std::min(pstart.x(), pend.x()); i <= std::max(pstart.x(), pend.x()); i++) {
                    for (int j = std::min(pstart.y(), pend.y()); j <= std::max(pstart.y(), pend.y()); j++) {
                        if (i == pend.x() || i == pstart.x() || j == pend.y() || j == pstart.y()) {
                            image.setPixel(i, j, qRgb(0, 0, 0));
                        }
                    }
                }
                setPixmap(image);

            }
        } else {
            if (event->type() == QEvent::MouseButtonPress) {
                pstart = p;
            } else if (event->type() == QEvent::MouseButtonRelease) {
                pend = p;
                QImage image = img;
                for (int i = std::min(pstart.x(), pend.x()); i <= std::max(pstart.x(), pend.x()); i++) {
                    for (int j = std::min(pstart.y(), pend.y()); j <= std::max(pstart.y(), pend.y()); j++) {
                        if (i == pend.x() || i == pstart.x() || j == pend.y() || j == pstart.y()) {
                            image.setPixel(i, j, qRgb(0, 0, 0));
                        }
                    }
                }
                setPixmap(image);
                selectSet = true;
            }

        }
    }

    return false;
}

void baseWindow::greyScale() {
    QImage image = widget.resultLabel->pixmap()->toImage();
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            image.setPixel(i, j, pxToGrey(image.pixel(i, j)));
        }
    }
    setImage(image);

    //Sobel();
}

QRgb baseWindow::pxToGrey(QRgb px) {
    int a = (qRed(px)*0.21 + 0.71 * qGreen(px) + 0.07 * qBlue(px)); //d'après la C.I.E (Commission Internationale de l'Éclairage)
    return qRgba(a, a, a, qAlpha(px));
}

void baseWindow::blur() {
    int sum[4];
    int radius = 2, out;
    QImage image = img;
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

void baseWindow::Sobel() {
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

    QImage source = img;
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

void baseWindow::filtrer(int filtre[3][3], int div) {
    int width = img.width();
    int height = img.height();
    QImage dest = img;
    int out;
    int sum[4];
    int I, J;
    QRgb rgb;

    if (div == 0)
        div++;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int s = 0; s < 4; s++)
                sum[s] = 0;
            out = 0;
            for (I = -1; I <= 1; I++) {
                for (J = -1; J <= 1; J++) {
                    if (y + I < height && y + I >= 0 && x + J < width && x + J >= 0) {
                        rgb = img.pixel(x + J, y + I);
                        sum[0] += qRed(rgb) * filtre[I + 1][J + 1];
                        sum[1] += qGreen(rgb) * filtre[I + 1][J + 1];
                        sum[2] += qBlue(rgb) * filtre[I + 1][J + 1];
                        sum[3] += qAlpha(rgb) * filtre[I + 1][J + 1];
                    } else {
                        out += filtre[I + 1][J + 1];
                    }
                }
            }
            if (div - out == 0) {
                out--;
            }
            for (int s = 0; s < 4; s++) {
                if ((sum[s] / (div - out)) > 255) {
                    sum[s] = 255 * (div - out);
                    //                std::cout << "lol"<<sum[s]<<div - out << std::endl;
                } else if ((sum[s]) <= 0) {
                    sum[s] = -sum[s];
                }
            }
            dest.setPixel(x, y, qRgba(((sum[0]) / (div - out)), ((sum[1]) / (div - out)), ((sum[2]) / (div - out)), ((sum[3]) / (div - out))));
        }
    }
    setImage(dest);
}


