/*
 * File:   filtre.cpp
 * Author: Samy
 *
 * Created on 17 janvier 2013, 14:53
 */

#include "filtre.h"

Filtre::Filtre() {
    widget.setupUi(this);
}

Filtre::Filtre(newForm* p) {
    widget.setupUi(this);
    this->pere = p;
}

Filtre::~Filtre() {
}

void Filtre::on_okButton_clicked() {
    int Filtre[3][3];
    Filtre[0][0] = widget.l1->text().toInt();
    Filtre[0][1] = widget.l2->text().toInt();
    Filtre[0][2] = widget.l3->text().toInt();
    Filtre[1][0] = widget.l4->text().toInt();
    Filtre[1][1] = widget.l5->text().toInt();
    Filtre[1][2] = widget.l6->text().toInt();
    Filtre[2][0] = widget.l7->text().toInt();
    Filtre[2][1] = widget.l8->text().toInt();
    Filtre[2][2] = widget.l9->text().toInt();
    pere->filtrer(Filtre);
    this->close();
}