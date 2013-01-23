/* 
 * File:   baseWindow.h
 * Author: XXX
 *
 * Created on 22 janvier 2013, 22:45
 */

#ifndef _BASEWINDOW_H
#define	_BASEWINDOW_H

#include "ui_baseWindow.h"

class baseWindow : public QMainWindow {
    Q_OBJECT
public:
    baseWindow();
    virtual ~baseWindow();
    void setLabelSize(QSize s);
    void setImage(QImage i);
    void greyScale();
    void blur();
    void Sobel();
    void filtrer(int filtre[3][3], int div);
public slots:
    void on_loadButton_clicked();
    void on_cropButton_clicked();
    void on_saveButton_clicked();
    void on_resizeButton_clicked();
    void on_pipetteButton_clicked();
    void on_greyButton_clicked();
    void on_blurButton_clicked();
    void on_histoButton_clicked();
    void on_filtreButton_clicked();
    void on_fusionButton_clicked();
private:
    Ui::MainWindow widget;
    QImage img;
    bool crop;
    bool pipette;
    QPoint pstart;
    bool eventFilter(QObject* watched, QEvent* event);
    QRgb pxToGrey(QRgb px);

};

#endif	/* _BASEWINDOW_H */

