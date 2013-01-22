/* 
 * File:   Fusion.h
 * Author: XXX
 *
 * Created on 21 janvier 2013, 15:00
 */

#ifndef FUSION_H
#define	FUSION_H

#include"ui_Fusion.h"
#include <QImage>
#include <QWidget>

class Fusion : public QDialog {
    Q_OBJECT
public:
    Fusion(QImage im, QImage im2);
    virtual ~Fusion();
public slots:
    void on_horizontalSlider_valueChanged();
private:
    Ui::Fusion widget;
    QImage img1;
    QImage img2;
    QImage* imgResult;
    void setLabelSize(QSize s);
    void setImage(QImage i);
    int h1,w1;

};

#endif	/* FUSION_H */
