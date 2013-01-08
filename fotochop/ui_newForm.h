/********************************************************************************
** Form generated from reading UI file 'newForm.ui'
**
** Created: Tue 8. Jan 15:03:41 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFORM_H
#define UI_NEWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newForm
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton;
    QLabel *resultLabel;

    void setupUi(QDialog *newForm)
    {
        if (newForm->objectName().isEmpty())
            newForm->setObjectName(QString::fromUtf8("newForm"));
        newForm->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(newForm->sizePolicy().hasHeightForWidth());
        newForm->setSizePolicy(sizePolicy);
        scrollArea = new QScrollArea(newForm);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 800, 600));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 798, 598));
        pushButton = new QPushButton(scrollAreaWidgetContents);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 93, 28));
        resultLabel = new QLabel(scrollAreaWidgetContents);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(90, 0, 200, 200));
        sizePolicy.setHeightForWidth(resultLabel->sizePolicy().hasHeightForWidth());
        resultLabel->setSizePolicy(sizePolicy);
        resultLabel->setMinimumSize(QSize(200, 200));
        resultLabel->setScaledContents(false);
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(newForm);

        QMetaObject::connectSlotsByName(newForm);
    } // setupUi

    void retranslateUi(QDialog *newForm)
    {
        newForm->setWindowTitle(QApplication::translate("newForm", "newForm", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("newForm", "Chargez!", 0, QApplication::UnicodeUTF8));
        resultLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class newForm: public Ui_newForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFORM_H
