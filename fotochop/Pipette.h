/* 
 * File:   Pipette.h
 * Author: Samy
 *
 * Created on 12 janvier 2013, 13:11
 */

#ifndef _PIPETTE_H
#define	_PIPETTE_H

#include "ui_Pipette.h"

class Pipette : public QDialog {
    Q_OBJECT
public:
    Pipette();
    Pipette(int r, int g, int b);
    virtual ~Pipette();
public slots:
    void on_YUV_toggled();
private:
    Ui::Pipette widget;
};

#endif	/* _PIPETTE_H */

