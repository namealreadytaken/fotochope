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
    void greyScale();
    void blur();
public slots:
    void on_loadButton_clicked();
    void on_cropButton_clicked();
    void on_saveButton_clicked();
    void on_resizeButton_clicked();
    void on_pipetteButton_clicked();
    void on_greyButton_clicked();
    void on_blurButton_clicked();
private:
    Ui::newForm widget;
    QImage img;
    bool crop;
    bool pipette;
    QPoint pstart;
    bool eventFilter(QObject* watched, QEvent* event);
    QRgb pxToGrey(QRgb px);
};

#endif	/* _NEWFORM_H */

