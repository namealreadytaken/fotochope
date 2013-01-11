/* 
 * File:   resize.h
 * Author: XXX
 *
 * Created on 11 janvier 2013, 11:36
 */

#ifndef _RESIZE_H
#define	_RESIZE_H
#include "newForm.h"
#include "ui_resize.h"
#include <QPainter>
#include <QWidget>

class Resize : public QDialog {
    Q_OBJECT
public:
    Resize();
    Resize(newForm* p,QImage im);
    virtual ~Resize();
    QImage resizeI(QImage image, int width, int height);
public slots:   
void on_cancelButton_clicked();
void on_okButton_clicked();
private:
    Ui::resize widget;
    QImage image;
    newForm* pere;
};

#endif	/* _RESIZE_H */
