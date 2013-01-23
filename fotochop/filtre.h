/* 
 * File:   filtre.h
 * Author: Samy
 *
 * Created on 17 janvier 2013, 14:53
 */

#ifndef _Filtre_H
#define	_Filtre_H
#include "baseWindow.h"
#include "ui_filtre.h"

class Filtre : public QDialog {
    Q_OBJECT
public:
    Filtre();
    Filtre(baseWindow* p);
    virtual ~Filtre();
public slots:
    void on_okButton_clicked();
    void on_presets_activated(int);
private:
    Ui::filtre widget;
    baseWindow* pere;
};

#endif	/* _Filtre_H */

