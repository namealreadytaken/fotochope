/*
 * File:   Pipette.cpp
 * Author: Samy
 *
 * Created on 12 janvier 2013, 13:11
 */

#include "Pipette.h"

Pipette::Pipette() {
    widget.setupUi(this);
}

Pipette::Pipette(int r, int g, int b) {
    widget.setupUi(this);
    char buffer [33];
    itoa(r, buffer, 10);
    widget.line1->setText(buffer);
    itoa(g, buffer, 10);
    widget.line2->setText(buffer);
    itoa(b, buffer, 10);
    widget.line3->setText(buffer);
}

Pipette::~Pipette() {
}

void Pipette::on_YUV_toggled() {
    int R, G, B, Y, U, V;
    if (widget.YUV->isChecked()) {
        R = widget.line1->text().toInt();
        G = widget.line2->text().toInt();
        B = widget.line3->text().toInt();
        Y = 0.299 * (double) R + 0.587 * (double) G + 0.114 * (double) B;
        U = -0.14713 * (double) R - 0.28886 * (double) G + 0.436 * (double) B;
        V = 0.615 * (double) R - 0.51498 * (double) G - 0.10001 * (double) B;
        char buffer [33];
        itoa(Y, buffer, 10);
        widget.line1->setText(buffer);
        itoa(U, buffer, 10);
        widget.line2->setText(buffer);
        itoa(V, buffer, 10);
        widget.line3->setText(buffer);
    } else {
        Y = widget.line1->text().toInt();
        U = widget.line2->text().toInt();
        V = widget.line3->text().toInt();
        R = Y + 1.13983 * (double) V;
        G = Y - 0.39465 * (double) U - 0.58060 * (double) V;
        B = Y + 2.03211 * (double) U;
        char buffer [33];
        itoa(R, buffer, 10);
        widget.line1->setText(buffer);
        itoa(G, buffer, 10);
        widget.line2->setText(buffer);
        itoa(B, buffer, 10);
        widget.line3->setText(buffer);
    }
}

