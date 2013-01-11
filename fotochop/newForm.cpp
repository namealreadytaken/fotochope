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
            widget.resultLabel->setPixmap(QPixmap::fromImage(*cropped));
            widget.resultLabel->adjustSize();
            widget.scrollAreaWidgetContents->adjustSize();
            crop = false;
        }
    } else if (pipette) {
        QRgb px = widget.resultLabel->pixmap()->toImage().pixel(p.x(), p.y());
        QColor* color = new QColor(px);
        int r, g, b, a;
        color->getRgb(&r, &g, &b, &a);
        std::cout << r << " " << g << " " << b << " " << a << std::endl;
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
    QColor* color = new QColor(px);
    int a = (color->red()*0.21 + 0.71 * color->green() + 0.07 * color->blue()); //d'après la C.I.E (Commission Internationale de l'Éclairage)
    color->setRed(a);
    color->setBlue(a);
    color->setGreen(a);
    return color->rgb();
}

void newForm::blur() {
    int sum[4];
    int radius = 2, out;

    QImage image = widget.resultLabel->pixmap()->toImage();
    QImage dest = image;
    QImage tmp = image;
    QColor* c = NULL;
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            for (int s = 0; s < 4; s++)
                sum[s] = 0;
            out = 0;
            for (int kx = -radius; kx <= radius; ++kx) {
                if (i + kx < image.width() && i + kx >= 0) {
                    c = new QColor(image.pixel(i + kx, j));
                    sum[0] += c->red();
                    sum[1] += c->green();
                    sum[2] += c->blue();
                    sum[3] += c->alpha();
                } else {
                    out++;
                }
            }
            c->setRgb(sum[0] / (radius * 2 + 1 - out), sum[1] / (radius * 2 + 1 - out), sum[2] / (radius * 2 + 1 - out), c->alpha() / (radius * 2 + 1 - out));
            tmp.setPixel(i, j, c->rgb());
        }
    }
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            for (int s = 0; s < 4; s++)
                sum[s] = 0;
            out = 0;
            for (int ky = -radius; ky <= radius; ++ky) {

                if (j + ky < image.height() && j + ky >= 0) {
                    c = new QColor(tmp.pixel(i, j + ky));
                    sum[0] += c->red();
                    sum[1] += c->green();
                    sum[2] += c->blue();
                    sum[3] += c->alpha();
                } else {
                    out++;
                }
            }
            c->setRgb(sum[0] / (radius * 2 + 1 - out), sum[1] / (radius * 2 + 1 - out), sum[2] / (radius * 2 + 1 - out), c->alpha() / (radius * 2 + 1 - out));
            dest.setPixel(i, j, c->rgb());
        }
    }
    setImage(dest);
}