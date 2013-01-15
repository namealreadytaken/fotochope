/********************************************************************************
** Form generated from reading UI file 'newForm.ui'
**
** Created: Tue 15. Jan 17:54:15 2013
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
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newForm
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QPushButton *cropButton;
    QPushButton *loadButton;
    QPushButton *resizeButton;
    QPushButton *saveButton;
    QLabel *resultLabel;
    QPushButton *pipetteButton;
    QPushButton *greyButton;
    QPushButton *blurButton;
    QPushButton *histoButton;

    void setupUi(QDialog *newForm)
    {
        if (newForm->objectName().isEmpty())
            newForm->setObjectName(QString::fromUtf8("newForm"));
        newForm->resize(783, 658);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(newForm->sizePolicy().hasHeightForWidth());
        newForm->setSizePolicy(sizePolicy);
        newForm->setMouseTracking(false);
        gridLayout = new QGridLayout(newForm);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(newForm);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setAutoFillBackground(false);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 778, 649));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 598));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cropButton = new QPushButton(scrollAreaWidgetContents);
        cropButton->setObjectName(QString::fromUtf8("cropButton"));
        cropButton->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(cropButton, 1, 0, 1, 1);

        loadButton = new QPushButton(scrollAreaWidgetContents);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(loadButton, 0, 0, 1, 1);

        resizeButton = new QPushButton(scrollAreaWidgetContents);
        resizeButton->setObjectName(QString::fromUtf8("resizeButton"));
        resizeButton->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(resizeButton, 2, 0, 1, 1);

        saveButton = new QPushButton(scrollAreaWidgetContents);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(saveButton, 3, 0, 1, 1);

        resultLabel = new QLabel(scrollAreaWidgetContents);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        sizePolicy.setHeightForWidth(resultLabel->sizePolicy().hasHeightForWidth());
        resultLabel->setSizePolicy(sizePolicy);
        resultLabel->setMinimumSize(QSize(200, 200));
        resultLabel->setScaledContents(false);

        gridLayout_2->addWidget(resultLabel, 0, 2, 10, 2);

        pipetteButton = new QPushButton(scrollAreaWidgetContents);
        pipetteButton->setObjectName(QString::fromUtf8("pipetteButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pipetteButton->sizePolicy().hasHeightForWidth());
        pipetteButton->setSizePolicy(sizePolicy2);
        pipetteButton->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(pipetteButton, 4, 0, 1, 1);

        greyButton = new QPushButton(scrollAreaWidgetContents);
        greyButton->setObjectName(QString::fromUtf8("greyButton"));
        greyButton->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(greyButton, 5, 0, 1, 1);

        blurButton = new QPushButton(scrollAreaWidgetContents);
        blurButton->setObjectName(QString::fromUtf8("blurButton"));
        blurButton->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(blurButton, 6, 0, 1, 1);

        histoButton = new QPushButton(scrollAreaWidgetContents);
        histoButton->setObjectName(QString::fromUtf8("histoButton"));
        histoButton->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(histoButton, 7, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        resultLabel->setBuddy(resultLabel);
#endif // QT_NO_SHORTCUT

        retranslateUi(newForm);

        QMetaObject::connectSlotsByName(newForm);
    } // setupUi

    void retranslateUi(QDialog *newForm)
    {
        newForm->setWindowTitle(QApplication::translate("newForm", "newForm", 0, QApplication::UnicodeUTF8));
        cropButton->setText(QApplication::translate("newForm", "Crop", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("newForm", "Load", 0, QApplication::UnicodeUTF8));
        resizeButton->setText(QApplication::translate("newForm", "Resize", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("newForm", "Save", 0, QApplication::UnicodeUTF8));
        resultLabel->setText(QString());
        pipetteButton->setText(QApplication::translate("newForm", "Picker", 0, QApplication::UnicodeUTF8));
        greyButton->setText(QApplication::translate("newForm", "Grey", 0, QApplication::UnicodeUTF8));
        blurButton->setText(QApplication::translate("newForm", "Blur", 0, QApplication::UnicodeUTF8));
        histoButton->setText(QApplication::translate("newForm", "Histo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class newForm: public Ui_newForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFORM_H
