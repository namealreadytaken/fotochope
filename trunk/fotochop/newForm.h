/* 
 * File:   newForm.h
 * Author: Samy
 *
 * Created on 7 janvier 2013, 17:28
 */

#ifndef _NEWFORM_H
#define	_NEWFORM_H

#include "ui_newForm.h"
#include <QPainter>
#include <QWidget>

class newForm : public QDialog {
    Q_OBJECT
public:
    newForm();
    virtual ~newForm();
    void setLabelSize(QSize s);
    void setImage(QImage i);
public slots:
    void on_pushButton_clicked();
private:
    Ui::newForm widget;
    QImage protu;
};

#endif	/* _NEWFORM_H */

