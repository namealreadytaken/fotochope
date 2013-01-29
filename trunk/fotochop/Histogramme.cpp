/*
 * File:   Histogramme.cpp
 * Author: XXX
 *
 * Created on 11 janvier 2013, 16:41
 */
#include <iostream>
#include "Histogramme.h"
#include "baseWindow.h"
#include <QtGui>

Histogramme::Histogramme(baseWindow* p, QImage im) {

    img = im;
    pere = p;

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

void Histogramme::on_egalizeButton_clicked() {
    egalize();
}

void Histogramme::on_spreadButton_clicked() {
    spread();
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

void Histogramme::egalize() {

    int hist[256];

    for (int i = 0; i < 256; i++) {
        hist[i] = 0;
    }

    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            QColor p = img.pixel(i, j);
            hist[p.toHsv().value()]++;
        }
    }

    for (int i = 1; i < 256; i++) {
        hist[i] = (hist[i] + hist[i - 1]);
    }

    for (int i = 0; i < 256; i++) {
        hist[i] = 255 * hist[i] / nb_pixel;
    }

    int h, s, v;
    QColor* c;
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            c = new QColor(img.pixel(i, j));
            h = c->hue();
            s = c->saturation();
            v = hist[c->value()];
            c->setHsv(h, s, v);
            img.setPixel(i, j, c->rgb());
        }
    }
    pere->setImage(img);

    changer_affichage_histo();
}

/*void Histogramme::spread(){
    int minR=0,minG=0,minB=0;
    int maxR=255,maxG=255,maxB=255;
    while (histR[minR] == 0 && minR<256 ){
        minR++;
    }
    while (histG[minG] == 0 && minG<256){
        minG++;
    }
    while (histB[minB] == 0 && minB<256){
        minB++;
    }
    while (histR[maxR] == 0 && maxR>=0){
        maxR--;
    }
    while (histG[maxG] == 0 && maxG>=0){
        maxG--;
    }
    while (histB[maxB] == 0 && maxB>=0){
        maxR--;
    }
    int penteR,penteG,penteB;
    penteR= 255/(maxR-minR);
    penteG= 255/(maxG-minG);
    penteB= 255/(maxB-minB);
    
    int oaoR,oaoG,oaoB;
    oaoR = -penteR*minR;
    oaoG = -penteG*minG;
    oaoB = -penteB*minB;
    
    int newValR[256],newValG[256],newValB[256];
    
    for (int i = 0; i<256;i++){
        newValR[i]=std::min(255,std::max(0,penteR*i+oaoR));
        newValG[i]=std::min(255,std::max(0,penteG*i+oaoG));
        newValB[i]=std::min(255,std::max(0,penteB*i+oaoB));
    }
    
    int r,g,b;
    QColor* c;
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            c = new QColor(img.pixel(i, j));
            r= newValR[c->red()];
            g= newValG[c->green()];
            b= newValB[c->blue()];
            c->setRgb(r,g,b);
            img.setPixel(i,j,c->rgb());
        }
    }
    pere->setImage(img);
    
    changer_affichage_histo();
}*/

void Histogramme::spread() {

    int hist[256];

    for (int i = 0; i < 256; i++) {
        hist[i] = 0;
    }

    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            QColor p = img.pixel(i, j);
            hist[p.toHsv().value()]++;
        }
    }


    int min = 0, max = 255;

    while (hist[min] == 0 || hist[max] == 0) {
        if (hist[min] == 0 && min < 256) min++;
        if (hist[max] == 0 && max >= 0) max--;
    }
std::cout << max << "  & min :" << min << std::endl;
    int pente, oao;
    pente = 255 / (max - min);
    oao = -pente*min;

    int newVal[256];

    for (int i = 0; i < 256; i++) {
  //      newVal[i] = std::min(255, std::max(0, pente * i + oao));
        newVal[i] = std::min(std::max(0,255*(i-min)/(max-min)),255);
    }

    int h, s, v;
    QColor* c;
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            c = new QColor(img.pixel(i, j));
            h = c->hue();
            s = c->saturation();
            v = newVal[c->value()];
            c->setHsv(h, s, v);
            //if (v >200 ) std::cout << v << std::endl;
            img.setPixel(i, j, c->rgb());
        }
    }
    pere->setImage(img);
    
    for (int i = 0; i < 256; i++) {
        hist[i] = 0;
    }

    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            QColor p = img.pixel(i, j);
            hist[p.toHsv().value()]++;
        }
    }
    
    min = 0; max = 255;
     while (hist[min] == 0 || hist[max] == 0) {
        if (hist[min] == 0 && min < 256) min++;
        if (hist[max] == 0 && max >= 0) max--;
    }
std::cout << max << "  & min :" << min << std::endl;


    changer_affichage_histo();

}


