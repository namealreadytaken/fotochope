/* 
 * File:   greyScale.h
 * Author: XXX
 *
 * Created on 31 janvier 2013, 01:46
 */

#ifndef _GREYSCALE_H
#define	_GREYSCALE_H

#include "ui_greyScale.h"
#include "baseWindow.h"

class greyScale : public QDialog {
    Q_OBJECT
public:
    greyScale(baseWindow* p);
    virtual ~greyScale();
public slots:
    void on_okButton_clicked();
private:
    QRgb pxToGreyCEI(QRgb px);
    QRgb pxToGreyAverage(QRgb px);
    QRgb pxToGreyDesaturation(QRgb px);
    Ui::greyScale widget;
    baseWindow* pere;
};

#endif	/* _GREYSCALE_H */
