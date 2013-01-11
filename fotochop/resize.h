/* 
 * File:   resize.h
 * Author: XXX
 *
 * Created on 11 janvier 2013, 11:36
 */

#ifndef _RESIZE_H
#define	_RESIZE_H

#include "ui_resize.h"
#include <QPainter>
#include <QWidget>

class Resize : public QDialog {
    Q_OBJECT
public:
    Resize();
    Resize(QImage image);
    virtual ~Resize();
    QImage resizeI(QImage image, int width, int height);
private:
    Ui::resize widget;
};

#endif	/* _RESIZE_H */
