/********************************************************************************
** Form generated from reading UI file 'Pipette.ui'
**
** Created: Tue 15. Jan 17:54:15 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIPETTE_H
#define UI_PIPETTE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_Pipette
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *line1;
    QLineEdit *line2;
    QLineEdit *line3;
    QGroupBox *horizontalGroupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *color;
    QRadioButton *RGB;
    QRadioButton *YUV;

    void setupUi(QDialog *Pipette)
    {
        if (Pipette->objectName().isEmpty())
            Pipette->setObjectName(QString::fromUtf8("Pipette"));
        Pipette->resize(400, 118);
        formLayout = new QFormLayout(Pipette);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        line1 = new QLineEdit(Pipette);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setAcceptDrops(false);
        line1->setMaxLength(3);
        line1->setReadOnly(true);

        horizontalLayout->addWidget(line1);

        line2 = new QLineEdit(Pipette);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setAcceptDrops(false);
        line2->setMaxLength(3);
        line2->setReadOnly(true);

        horizontalLayout->addWidget(line2);

        line3 = new QLineEdit(Pipette);
        line3->setObjectName(QString::fromUtf8("line3"));
        line3->setAcceptDrops(false);
        line3->setMaxLength(3);
        line3->setReadOnly(true);

        horizontalLayout->addWidget(line3);


        formLayout->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);

        horizontalGroupBox_2 = new QGroupBox(Pipette);
        horizontalGroupBox_2->setObjectName(QString::fromUtf8("horizontalGroupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(horizontalGroupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        color = new QLabel(horizontalGroupBox_2);
        color->setObjectName(QString::fromUtf8("color"));
        color->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(color);

        RGB = new QRadioButton(horizontalGroupBox_2);
        RGB->setObjectName(QString::fromUtf8("RGB"));
        RGB->setChecked(true);

        horizontalLayout_2->addWidget(RGB);

        YUV = new QRadioButton(horizontalGroupBox_2);
        YUV->setObjectName(QString::fromUtf8("YUV"));

        horizontalLayout_2->addWidget(YUV);


        formLayout->setWidget(4, QFormLayout::FieldRole, horizontalGroupBox_2);


        retranslateUi(Pipette);

        QMetaObject::connectSlotsByName(Pipette);
    } // setupUi

    void retranslateUi(QDialog *Pipette)
    {
        Pipette->setWindowTitle(QApplication::translate("Pipette", "Pipette", 0, QApplication::UnicodeUTF8));
        color->setText(QString());
        RGB->setText(QApplication::translate("Pipette", "RGB", 0, QApplication::UnicodeUTF8));
        YUV->setText(QApplication::translate("Pipette", "YUV", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Pipette: public Ui_Pipette {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIPETTE_H
