/********************************************************************************
** Form generated from reading UI file 'resize.ui'
**
** Created: Fri 11. Jan 11:45:55 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESIZE_H
#define UI_RESIZE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_resize
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *width;
    QLineEdit *height;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *resize)
    {
        if (resize->objectName().isEmpty())
            resize->setObjectName(QString::fromUtf8("resize"));
        resize->resize(243, 177);
        buttonBox = new QDialogButtonBox(resize);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 130, 201, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        width = new QLineEdit(resize);
        width->setObjectName(QString::fromUtf8("width"));
        width->setGeometry(QRect(90, 40, 113, 22));
        height = new QLineEdit(resize);
        height->setObjectName(QString::fromUtf8("height"));
        height->setGeometry(QRect(90, 70, 113, 22));
        label = new QLabel(resize);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 70, 53, 16));
        label_2 = new QLabel(resize);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 40, 53, 16));

        retranslateUi(resize);
        QObject::connect(buttonBox, SIGNAL(accepted()), resize, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), resize, SLOT(reject()));

        QMetaObject::connectSlotsByName(resize);
    } // setupUi

    void retranslateUi(QDialog *resize)
    {
        resize->setWindowTitle(QApplication::translate("resize", "resize", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("resize", "Hauteur", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("resize", "Largeur", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class resize: public Ui_resize {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESIZE_H
