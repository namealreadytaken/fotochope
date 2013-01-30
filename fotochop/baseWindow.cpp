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
#include <algorithm>
#include <vector> 

baseWindow::baseWindow() {

    widget.setupUi(this);
    widget.resultLabel->installEventFilter(this);
    pipette = false;
    selectZone = false;
    selectSet = false;
    //actHist = -1;
    /*liste = NULL;
    histAct = new Element;*/
    actHist = -1;
    min = -1;
    max = -1;
    null = new QImage();
    for (int i = 0; i < MAXHIST; i++) {
        hist[i] = *null;
    }

}

baseWindow::~baseWindow() {
}

void baseWindow::on_actionCharger_triggered() {

    QString fileName = QFileDialog::getOpenFileName(this, "Choisir l'image", "", tr("Images (*.png *.jpg *.gif *.pnm)"));
    QImage image;
    if (!fileName.isEmpty()) {
        image.load(fileName);
        setWindowTitle(fileName);
        setImage(image);
        img = image;
    }
}

void baseWindow::on_cropButton_clicked() {
    if (pstart != pend) {
        QImage image = img;
        QImage* cropped = new QImage(abs(pstart.x() - pend.x()), abs(pstart.y() - pend.y()), QImage::Format_ARGB32_Premultiplied);
        for (int i = std::min(pstart.x(), pend.x()); i < std::max(pstart.x(), pend.x()); i++) {
            for (int j = std::min(pstart.y(), pend.y()); j < std::max(pstart.y(), pend.y()); j++) {
                cropped->setPixel(i - std::min(pstart.x(), pend.x()), j - std::min(pstart.y(), pend.y()), image.pixel(i, j));
            }
        }
        selectSet = false;
        pstart = pend;
        setImage(*cropped);
    }
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

void baseWindow::on_actionEnregistrer_triggered() {
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
    //std::cout << "min : " << min << " max : " << max << " courant : " << actHist << std::endl;

    /* Element* e = new Element;
     e->valeur = i;
     e->suivant = NULL;

     if (liste == NULL) {

         liste = e;
     } else {
         Element* eT = liste;
         while (eT->suivant != NULL) {
             eT = eT->suivant;
         }
         eT->suivant = e;
     }
     std::cout << "bla" << std::endl;
     *histAct = *e;
     std::cout << "bla" << std::endl;
     */

    if (actHist != max) {
        actHist = (actHist + 1) % MAXHIST;
        for (int hi = actHist; hi != max; hi = (hi + 1) % MAXHIST)
            hist[hi] = *null;
        max = actHist;
    } else {
        actHist = (actHist + 1) % MAXHIST;
        max = (max + 1) % MAXHIST;
        if (hist[actHist] != *null || min == max || min < 0) {
            min = (min + 1) % MAXHIST;
        }
    }
    hist[actHist] = i;
    setLabelSize(i.size());
    img = i;
    widget.resultLabel->setPixmap(QPixmap::fromImage(i));
}

void baseWindow::on_actionQuitter_triggered() {
    this->close();
}

void baseWindow::on_actionAnnuler_triggered() {
    if (actHist != min) {
        actHist = (actHist - 1) % MAXHIST;
        if (actHist == -1)
            actHist = MAXHIST - 1;
        img = hist[actHist];
        setLabelSize(img.size());
        widget.resultLabel->setPixmap(QPixmap::fromImage(img));
    }

    /*
        Element* eT = liste;
        if (liste != NULL) {
            if (liste->suivant != NULL) {
                // while (eT->suivant->suivant != NULL) {
                while (eT->suivant != histAct) {
                    eT = eT->suivant;
                }
                img = eT->valeur;
                // eT->suivant = NULL;
                setLabelSize(img.size());
                widget.resultLabel->setPixmap(QPixmap::fromImage(img));
            }
        }
     */
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

void baseWindow::on_actionRefaire_triggered() {
    //setImage(histAct->suivant->valeur);
    if (actHist != max) {
        actHist = (actHist + 1) % MAXHIST;
        img = hist[actHist];
        setLabelSize(img.size());
        widget.resultLabel->setPixmap(QPixmap::fromImage(img));
    }
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
                    selectZone = false;
                    selectSet = false;
                    pstart = pend;
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

QImage baseWindow::Sobel(QImage source) {
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
                SUM = abs(sumX) + abs(sumY);
                if (SUM > 255) {
                    SUM = 255;
                }
            }
            sobelDestination.setPixel(x, y, qRgb(SUM, SUM, SUM));
        }
    }
    //    setImage(sobelDestination);
    return sobelDestination;
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
                if ((sum[s]) <= 0) {
                    sum[s] = -sum[s];
                }
                if ((sum[s] / (div - out)) > 255) {
                    sum[s] = 255 * (div - out);
                }
            }
            dest.setPixel(x, y, qRgba(((sum[0]) / (div - out)), ((sum[1]) / (div - out)), ((sum[2]) / (div - out)), ((sum[3]) / (div - out))));
        }
    }
    setImage(dest);
}

void baseWindow::on_negButton_clicked() {
    QImage dest = img;
    QRgb rgb;
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            rgb = img.pixel(i, j);
            dest.setPixel(i, j, qRgba(255 - qRed(rgb), 255 - qGreen(rgb), 255 - qBlue(rgb), 255 - qAlpha(rgb)));
        }
    }
    setImage(dest);
}

void baseWindow::contentAware(int width, int height) {

    QImage image = Sobel(img);
    QImage* temp = new QImage(img.width(), height, QImage::Format_ARGB32_Premultiplied);
    QImage* dest = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    double ratiov = double(img.height()) / double(height);
    double ratioh = double(img.width()) / double(width);
    bool todelete = false;
    int diffh = std::abs(img.height() - height);
    int diffw = std::abs(img.width() - width);
    int nbdeleted = 0;
    int w[image.width()][2], w2[image.width()][2]; //0= pos du px, 1= somme de la colonne
    int h[image.height()][2], h2[image.height()][2];
    int rgb;
    int wmaxval, hmaxval;
    //calcul de la somme
    for (int i = 0; i < image.height(); i++) {
        h[i][0] = i;
        h2[i][0] = i;
        h[i][1] = 0;
        h2[i][1] = 0;
    }
    for (int i = 0; i < image.width(); i++) {
        w[i][0] = i;
        w[i][1] = 0;
        w2[i][0] = i;
        w2[i][1] = 0;
        for (int j = 0; j < image.height(); j++) {
            rgb = qRed(image.pixel(i, j));
            w[i][1] += rgb - 10;
            h[j][1] += rgb - 10;
            w2[i][1] += rgb - 10;
            h2[j][1] += rgb - 10;
        }
    }

    std::qsort(w2, image.width(), sizeof (int[2]), &sortpx);
    std::qsort(h2, image.height(), sizeof (int[2]), &sortpx);





    if (ratiov > 1) {// on fait la diminution verticale
        hmaxval = h2[diffh][1];
        for (int j = 0; j < img.height(); j++) {
            todelete = false;
            if (h[j][1] <= hmaxval && nbdeleted < diffh) {
                todelete = true;
                nbdeleted++;
            }
            if (!todelete) {
                for (int i = 0; i < img.width(); i++) {
                    temp->setPixel(i, j - nbdeleted, img.pixel(i, j));
                }
            }
        }
    } else {

        hmaxval = std::min(h2[diffh][1], h2[image.height() / 2][1]);
        int hmaxpos = std::min(h2[diffh][0], h2[image.height() / 2][0]);


        for (int j = 0; j < img.height(); j++) {
            todelete = false;
            if (h[j][1] <= hmaxval && nbdeleted < diffw) {
                todelete = true;
            }
            if (!todelete) {
                for (int i = 0; i < img.width(); i++) {
                    temp->setPixel(i, j + nbdeleted, img.pixel(i, j));
                }
            } else {
                for (int i = 0; i < img.width(); i++) {
                    for (int k = j; k <= j + ((double) 1 / ratiov); k++) {
                        temp->setPixel(i, k + nbdeleted, img.pixel(i, j));
                    }
                }
                nbdeleted += ((double) 1 / ratiov);
            }
        }
    }
    if (ratioh > 1) {// on fait la diminution horizontale
        wmaxval = w2[diffw][1];
        nbdeleted = 0;
        for (int i = 0; i < image.width(); i++) {
            todelete = false;
            if (w[i][1] <= wmaxval && nbdeleted < diffw) {
                todelete = true;
                nbdeleted++;
            }
            if (!todelete) {
                for (int j = 0; j < height; j++) {
                    dest->setPixel(i + nbdeleted, j, temp->pixel(i, j));
                }
            }
        }
    } else {

        wmaxval = std::min(w2[diffw][1], w2[image.width() / 2][1]);
        int wmaxpos = std::min(w2[diffw][0], w2[image.height() / 2][0]);
        nbdeleted = 0;
        for (int i = 0; i < image.width(); i++) {
            todelete = false;
            if (w[i][1] <= wmaxval && nbdeleted < diffw) {
                todelete = true;
            }
            if (!todelete) {
                for (int j = 0; j < height; j++) {
                    dest->setPixel(i + nbdeleted, j, temp->pixel(i, j));
                }
            } else {
                for (int j = 0; j < height; j++) {
                    for (int k = i; k <= i + ((double) 1 / ratioh); k++) {
                        dest->setPixel(k + nbdeleted, j, temp->pixel(i, j));
                    }
                }
                nbdeleted += ((double) 1 / ratioh);
            }
        }
    }

    setImage(*dest);


}

int sortpx(const void* x, const void* y) {
    int* a = (int*) x;
    int* b = (int*) y;
    if (a[1] == b[1])
        return 0;
    return a[1] > b[1] ? +1 : -1;
}
