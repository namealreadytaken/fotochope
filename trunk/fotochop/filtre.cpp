/*
 * File:   filtre.cpp
 * Author: Samy
 *
 * Created on 17 janvier 2013, 14:53
 */

#include <iostream>

#include "filtre.h"

Filtre::Filtre() {
    widget.setupUi(this);
}

Filtre::Filtre(baseWindow* p) {
    widget.setupUi(this);
    this->pere = p;
}

Filtre::~Filtre() {
}

void Filtre::on_okButton_clicked() {
    int Filtre[3][3];
    int div;
    Filtre[0][0] = widget.l1->text().toInt();
    Filtre[0][1] = widget.l2->text().toInt();
    Filtre[0][2] = widget.l3->text().toInt();
    Filtre[1][0] = widget.l4->text().toInt();
    Filtre[1][1] = widget.l5->text().toInt();
    Filtre[1][2] = widget.l6->text().toInt();
    Filtre[2][0] = widget.l7->text().toInt();
    Filtre[2][1] = widget.l8->text().toInt();
    Filtre[2][2] = widget.l9->text().toInt();
    div = widget.diviseur->text().toInt();
    pere->filtrer(Filtre, div);
    this->close();
}

void Filtre::on_presets_activated(int i) {
    if (i == 0) {
        widget.l1->setText("0");
        widget.l2->setText("0");
        widget.l3->setText("0");
        widget.l4->setText("0");
        widget.l5->setText("1");
        widget.l6->setText("0");
        widget.l7->setText("0");
        widget.l8->setText("0");
        widget.l9->setText("0");
        widget.diviseur->setText("1");
    } else if (i == 1) {
        widget.l1->setText("0");
        widget.l2->setText("0");
        widget.l3->setText("0");
        widget.l4->setText("0");
        widget.l5->setText("1");
        widget.l6->setText("0");
        widget.l7->setText("0");
        widget.l8->setText("0");
        widget.l9->setText("0");
        widget.diviseur->setText("-1");
    } else if (i == 2) {
        widget.l1->setText("0");
        widget.l2->setText("-1");
        widget.l3->setText("0");
        widget.l4->setText("-1");
        widget.l5->setText("9");
        widget.l6->setText("-1");
        widget.l7->setText("0");
        widget.l8->setText("-1");
        widget.l9->setText("0");
        widget.diviseur->setText("5");
    } else if (i == 3) {
        widget.l1->setText("0");
        widget.l2->setText("0");
        widget.l3->setText("0");
        widget.l4->setText("0");
        widget.l5->setText("1");
        widget.l6->setText("0");
        widget.l7->setText("0");
        widget.l8->setText("0");
        widget.l9->setText("0");
        widget.diviseur->setText("1");
    }
}