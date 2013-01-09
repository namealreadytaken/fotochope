/* 
 * File:   MainMenu.h
 * Author: Samy
 *
 * Created on 9 janvier 2013, 05:19
 */

#ifndef _MAINMENU_H
#define	_MAINMENU_H

#include "ui_MainMenu.h"

class MainMenu : public QMainWindow {
    Q_OBJECT
public:
    MainMenu();
    virtual ~MainMenu();
private:
    Ui::MainMenu widget;
public slots:
    void on_actionOuvrir_triggered();
};

#endif	/* _MAINMENU_H */

