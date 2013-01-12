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
    this->a = r;
    this->b = g;
    this->c = b;


}

Pipette::~Pipette() {
}

void Pipette::on_YUV_toggled() {
    int A, B, C;
    double tempa, tempb, tempc;
    if (widget.YUV->isChecked()) {
        tempa = 0.299 * a + 0.587 * b + 0.114 * c;
        tempb = -0.14713 * a - 0.28886 * b + 0.436 * c;
        tempc = 0.615 * a - 0.51498 * b - 0.10001 * c;
        A = tempa;
        B = tempb;
        C = tempc;
        a = tempa;
        b = tempb;
        c = tempc;
        char buffer [33];
        itoa(A, buffer, 10);
        widget.line1->setText(buffer);
        itoa(B, buffer, 10);
        widget.line2->setText(buffer);
        itoa(C, buffer, 10);
        widget.line3->setText(buffer);
    } else {
        tempa = a + 1.13983 * c;
        tempb = a - 0.39465 * b - 0.5806 * c;
        tempc = a + 2.03211 * b;
        A = tempa;
        B = tempb;
        C = tempc;
        a = tempa;
        b = tempb;
        c = tempc;
        char buffer [33];
        itoa(A, buffer, 10);
        widget.line1->setText(buffer);
        itoa(B, buffer, 10);
        widget.line2->setText(buffer);
        itoa(C, buffer, 10);
        widget.line3->setText(buffer);
    }
}

