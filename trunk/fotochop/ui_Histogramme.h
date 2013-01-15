/********************************************************************************
** Form generated from reading UI file 'Histogramme.ui'
**
** Created: Tue 15. Jan 18:26:24 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMME_H
#define UI_HISTOGRAMME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Histogramme
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *RGBradio;
    QRadioButton *YUVradio;
    QHBoxLayout *horizontalLayout_3;
    QGraphicsView *gV;
    QFrame *verticalFrame_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkR;
    QCheckBox *checkG;
    QCheckBox *checkB;

    void setupUi(QDialog *Histogramme)
    {
        if (Histogramme->objectName().isEmpty())
            Histogramme->setObjectName(QString::fromUtf8("Histogramme"));
        Histogramme->resize(474, 209);
        Histogramme->setMouseTracking(false);
        Histogramme->setWindowOpacity(1);
        gridLayout = new QGridLayout(Histogramme);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(Histogramme);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        RGBradio = new QRadioButton(groupBox);
        RGBradio->setObjectName(QString::fromUtf8("RGBradio"));
        RGBradio->setChecked(true);

        horizontalLayout->addWidget(RGBradio);

        YUVradio = new QRadioButton(groupBox);
        YUVradio->setObjectName(QString::fromUtf8("YUVradio"));

        horizontalLayout->addWidget(YUVradio);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        gV = new QGraphicsView(Histogramme);
        gV->setObjectName(QString::fromUtf8("gV"));
        gV->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        gV->setAutoFillBackground(true);
        gV->setSceneRect(QRectF(0, -70, 257, 70));
        gV->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        horizontalLayout_3->addWidget(gV);

        verticalFrame_2 = new QFrame(Histogramme);
        verticalFrame_2->setObjectName(QString::fromUtf8("verticalFrame_2"));
        verticalFrame_2->setMinimumSize(QSize(10, 0));
        verticalLayout_2 = new QVBoxLayout(verticalFrame_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        checkR = new QCheckBox(verticalFrame_2);
        checkR->setObjectName(QString::fromUtf8("checkR"));

        verticalLayout_2->addWidget(checkR);

        checkG = new QCheckBox(verticalFrame_2);
        checkG->setObjectName(QString::fromUtf8("checkG"));

        verticalLayout_2->addWidget(checkG);

        checkB = new QCheckBox(verticalFrame_2);
        checkB->setObjectName(QString::fromUtf8("checkB"));

        verticalLayout_2->addWidget(checkB);


        horizontalLayout_3->addWidget(verticalFrame_2);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);


        retranslateUi(Histogramme);

        QMetaObject::connectSlotsByName(Histogramme);
    } // setupUi

    void retranslateUi(QDialog *Histogramme)
    {
        Histogramme->setWindowTitle(QApplication::translate("Histogramme", "Histogramme", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Histogramme", "GroupBox", 0, QApplication::UnicodeUTF8));
        RGBradio->setText(QApplication::translate("Histogramme", "RGB", 0, QApplication::UnicodeUTF8));
        YUVradio->setText(QApplication::translate("Histogramme", "YUV", 0, QApplication::UnicodeUTF8));
        checkR->setText(QApplication::translate("Histogramme", "Rouge", 0, QApplication::UnicodeUTF8));
        checkG->setText(QApplication::translate("Histogramme", "Vert", 0, QApplication::UnicodeUTF8));
        checkB->setText(QApplication::translate("Histogramme", "Bleu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Histogramme: public Ui_Histogramme {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMME_H
