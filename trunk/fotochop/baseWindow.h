/* 
 * File:   baseWindow.h
 * Author: XXX
 *
 * Created on 22 janvier 2013, 22:45
 */

#ifndef _BASEWINDOW_H
#define	_BASEWINDOW_H

#define MAXHIST 5

#include "ui_baseWindow.h"

class baseWindow : public QMainWindow {
    Q_OBJECT
public:
    baseWindow();
    virtual ~baseWindow();
    void setLabelSize(QSize s);
    void setImage(QImage i);
    void setPixmap(QImage i);
    //void greyScale();
    void blur();
    QImage Sobel(QImage source);
    void contentAware(int width, int height);
    void filtrer(int filtre[3][3], int div);
    QImage img;
public slots:
    //void on_loadButton_clicked();
    void on_cropButton_clicked();
    //void on_saveButton_clicked();
    void on_resizeButton_clicked();
    void on_pipetteButton_clicked();
    void on_greyButton_clicked();
    void on_blurButton_clicked();
    void on_histoButton_clicked();
    void on_filtreButton_clicked();
    void on_fusionButton_clicked();
    void on_selectButton_clicked();
    //void on_cancelButton_clicked();
    //void on_redoButton_clicked();
    void on_negButton_clicked();
    void on_actionQuitter_triggered();
    void on_actionCharger_triggered();
    void on_actionEnregistrer_triggered();
    void on_actionAnnuler_triggered();
    void on_actionRefaire_triggered();
private:
    Ui::MainWindow widget;
    bool selectSet;
    bool selectZone;
    bool pipette;
    QPoint pstart;
    QPoint pend;
    QPoint pdragstart;
    QPoint pdragend;
    bool eventFilter(QObject* watched, QEvent* event);
    //QRgb pxToGrey(QRgb px);
    //int actHist;
    /*
        typedef struct Element {
            QImage valeur;
            Element* suivant;
        } Element;

        Element* liste;
        Element * histAct;
     * */
    QImage hist[MAXHIST];
    int actHist;
    int min, max;
    QImage* null;
};
int sortpx(const void* x, const void* y);
#endif	/* _BASEWINDOW_H */

