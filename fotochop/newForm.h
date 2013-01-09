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
	QImage resize(QImage image, int width, int height);
public slots:
    void on_pushButton_clicked();
    void on_cropButton_clicked();
private:
    Ui::newForm widget;
    QImage protu;
    bool crop;
    QPoint pstart;
    bool eventFilter(QObject* watched, QEvent* event);
};

#endif	/* _NEWFORM_H */

