/* 
 * File:   filtre.h
 * Author: Samy
 *
 * Created on 17 janvier 2013, 14:53
 */

#ifndef _Filtre_H
#define	_Filtre_H
#include "newForm.h"
#include "ui_filtre.h"

class Filtre : public QDialog {
    Q_OBJECT
public:
    Filtre();
    Filtre(newForm* p);
    virtual ~Filtre();
public slots:
    void on_okButton_clicked();
private:
    Ui::filtre widget;
    newForm* pere;
};

#endif	/* _Filtre_H */

