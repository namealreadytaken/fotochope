/* 
 * File:   Histogramme.h
 * Author: XXX
 *
 * Created on 11 janvier 2013, 16:41
 */

#ifndef _HISTOGRAMME_H
#define	_HISTOGRAMME_H

#include "ui_Histogramme.h"

class Histogramme : public QDialog {
    Q_OBJECT
public:
    Histogramme(QImage im);
    virtual ~Histogramme();
public slots:
    void on_checkR_stateChanged();
    void on_checkG_stateChanged();
    void on_checkB_stateChanged();
    void on_YUVradio_toggled();
private:
    Ui::Histogramme widget;
    QGraphicsScene *scene;
    QGraphicsEllipseItem * ell;
    void histo(QImage im);
    int histR[256];
    int histG[256];
    int histB[256];
    int histY[256];
    int histU[224];
    int histV[316];
    int maxR, maxG, maxB, maxY, maxU, maxV;
    int baseU,baseV;
    void changer_affichage_histo();

};

#endif	/* _HISTOGRAMME_H */
