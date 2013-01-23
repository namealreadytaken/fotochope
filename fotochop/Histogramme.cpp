/*
 * File:   Histogramme.cpp
 * Author: XXX
 *
 * Created on 11 janvier 2013, 16:41
 */
#include <iostream>
#include "Histogramme.h"
#include <QtGui>

Histogramme::Histogramme(QImage im) {
    
    img = im;

    baseU = 112;
    baseV = 158;

    maxR = 0;
    maxG = 0;
    maxB = 0;

    maxY = 0;
    maxU = 0;
    maxV = 0;

    for (int i = 0; i < 256; ++i) {
        histR[i] = 0;
        histG[i] = 0;
        histB[i] = 0;

        histY[i] = 0;
        histU[i] = 0;
        histV[i] = 0;
    }
    
    nb_pixel = im.width() * im.height();

    for (int i = 0; i < im.width(); i++) {
        for (int j = 0; j < im.height(); j++) {
            QColor* color = new QColor(im.pixel(i, j));

            histR[color->red()]--;
            histG[color->green()]--;
            histB[color->blue()]--;


            int Y = 0.299 * color->red() + 0.587 * color->green() + 0.114 * color->blue();
            int U = -0.14713 * color->red() - 0.28886 * color->green() + 0.436 * color->blue();
            int V = 0.615 * color->red() - 0.51498 * color->green() - 0.10001 * color->blue();

            histY[Y]--;
            histU[baseU + U]--;
            histV[baseV + V]--;
        }
    }

    for (int i = 0; i < 256; ++i) {
        if (maxR > histR[i])
            maxR = histR[i];
        if (maxG > histG[i])
            maxG = histG[i];
        if (maxB > histB[i])
            maxB = histB[i];

        if (maxY > histY[i])
            maxY = histY[i];
        if (maxU > histU[i])
            maxU = histU[i];
        if (maxV > histV[i])
            maxV = histV[i];
    }

    std::cout << "Max R" << maxR;
    std::cout << "Max G" << maxG;
    std::cout << "Max B" << maxV;


    widget.setupUi(this);



}

Histogramme::~Histogramme() {

}

void Histogramme::on_checkR_stateChanged() {
    changer_affichage_histo();
}

void Histogramme::on_checkG_stateChanged() {
    changer_affichage_histo();
}

void Histogramme::on_checkB_stateChanged() {
    changer_affichage_histo();
}

void Histogramme::changer_affichage_histo() {
    if (widget.RGBradio->isChecked()) {
        scene = new QGraphicsScene(this);
        widget.gV->setScene(scene);

        QRect a = widget.gV->geometry();
        a.setHeight(120);
        widget.gV->setGeometry(a);

        if (widget.checkR->isChecked()) {
            QPen redP(Qt::red);
            for (int i = 0; i <= 256; i++)
                scene->addLine(QLineF(i, 0, i, histR[i]*100 / (-maxR)), redP);
        }
        if (widget.checkG->isChecked()) {
            QPen greenP(Qt::green);
            for (int i = 0; i <= 256; i++)
                scene->addLine(QLineF(i, 0, i, histG[i]*100 / (-maxG)), greenP);
        }
        if (widget.checkB->isChecked()) {
            QPen blueP(Qt::blue);
            for (int i = 0; i <= 256; i++)
                scene->addLine(QLineF(i, 0, i, histB[i]*100 / (-maxB)), blueP);
        }
    } else {
        scene = new QGraphicsScene(this);
        widget.gV->setScene(scene);

        QRect a = widget.gV->geometry();
        a.setHeight(120);
        widget.gV->setGeometry(a);

        if (widget.checkR->isChecked()) {
            QPen redP(Qt::red);
            for (int i = 0; i <= 256; i++)
                scene->addLine(QLineF(i, 0, i, histY[i]*100 / (-maxY)), redP);

        }
        if (widget.checkG->isChecked()) {
            QPen greenP(Qt::green);
            for (int i = 0; i <= 224; i++)
                scene->addLine(QLineF(i, 0, i, histU[i]*100 / (-maxU)), greenP);

        }
        if (widget.checkB->isChecked()) {
            QPen blueP(Qt::blue);
            for (int i = 0; i <= 316; i++)
                scene->addLine(QLineF(i, 0, i, histV[i]*100 / (-maxV)), blueP);

        }
    }
}

void Histogramme::on_egalizeButton_clicked(){
    egalize();
}

void Histogramme::on_YUVradio_toggled() {
    if (widget.YUVradio->isChecked()) {
        widget.RGBradio->setChecked(false);
        widget.checkR->setText("Y");
        widget.checkG->setText("U");
        widget.checkB->setText("V");
        widget.checkR->setChecked(false);
        widget.checkG->setChecked(false);
        widget.checkB->setChecked(false);
        scene = new QGraphicsScene(this);
        widget.gV->setScene(scene);
    } else {
        widget.YUVradio->setChecked(false);
        widget.checkR->setText("Rouge");
        widget.checkG->setText("Vert");
        widget.checkB->setText("Bleu");
        widget.checkR->setChecked(false);
        widget.checkG->setChecked(false);
        widget.checkB->setChecked(false);
        scene = new QGraphicsScene(this);
        widget.gV->setScene(scene);
    }
}

void Histogramme::egalize(){
    
    int histRcummul[256];
    int histGcummul[256];
    int histBcummul[256];
    
    for (int i = 0; i < 256; i++){
        histRcummul[i] = 0;
        histGcummul[i] = 0;
        histBcummul[i] = 0;
      }
    
    histRcummul[0] = histR[0];
    histGcummul[0] = histG[0];
    histBcummul[0] = histB[0];
    
    for (int i = 1; i < 256; i++){
        histRcummul[i] = histR[i] + histRcummul[i-1] ;
        histGcummul[i] = histG[i] + histGcummul[i-1] ;
        histBcummul[i] = histB[i] + histBcummul[i-1] ;
    }
    
    int newValR[256];
    int newValG[256];
    int newValB[256];
    
    for (int i = 0; i < 256; i++){
        newValR[i] = -(255*histRcummul[i])/nb_pixel;
        newValG[i] = -(255*histGcummul[i])/nb_pixel;
        newValB[i] = -(255*histBcummul[i])/nb_pixel;
    }
    
    int histRtmp[256];
    int histGtmp[256];
    int histBtmp[256];
    
    for (int i = 0; i < 256; i++){
        histRtmp[i] = histR[i];
        histR[i]=0;
        histGtmp[i] = histG[i];
        histG[i] = 0;
        histBtmp[i] = histB[i];
        histB[i]= 0;
      }
    
    for (int i = 0; i < 256; i++){
        histR[newValR[i]]= histR[i] + histRtmp[newValR[i]];
        histG[newValG[i]]= histG[i] + histGtmp[newValG[i]];
        histB[newValB[i]]= histB[i] + histBtmp[newValB[i]];
    }
    
    maxY = 0;
    maxU = 0;
    maxV = 0;
    
    for (int i = 0; i < 256; ++i) {
        if (maxR > histR[i])
            maxR = histR[i];
        if (maxG > histG[i])
            maxG = histG[i];
        if (maxB > histB[i])
            maxB = histB[i];

        if (maxY > histY[i])
            maxY = histY[i];
        if (maxU > histU[i])
            maxU = histU[i];
        if (maxV > histV[i])
            maxV = histV[i];
    }
    
    changer_affichage_histo();
}

