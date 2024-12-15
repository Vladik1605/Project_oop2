/********************************************************************************
** Form generated from reading UI file 'AddDirector.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDIRECTOR_H
#define UI_ADDDIRECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "addingworker.h"

QT_BEGIN_NAMESPACE

class Ui_AddDirector
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    CustomLineEdit *lineEdit_Birth;
    QLabel *label_5;
    QPushButton *SkipButton;
    CustomLineEdit *lineEdit_Wards;
    QLabel *label_3;
    CustomLineEdit *lineEdit_Salary;
    QLabel *label;
    QPushButton *SaveButton;
    QLabel *label_4;
    CustomLineEdit *lineEdit_Pasport;
    QLabel *label_6;
    CustomLineEdit *lineEdit_Phone;
    QLabel *label_10;
    CustomLineEdit *lineEdit_WA;
    CustomLineEdit *lineEdit_FIO;
    QLabel *label_2;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QDialog *AddDirector)
    {
        if (AddDirector->objectName().isEmpty())
            AddDirector->setObjectName("AddDirector");
        AddDirector->resize(690, 678);
        gridLayoutWidget = new QWidget(AddDirector);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(60, 10, 553, 621));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setVerticalSpacing(7);
        gridLayout->setContentsMargins(15, 7, 15, 10);
        lineEdit_Birth = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Birth->setObjectName("lineEdit_Birth");

        gridLayout->addWidget(lineEdit_Birth, 4, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 9, 0, 1, 1);

        SkipButton = new QPushButton(gridLayoutWidget);
        SkipButton->setObjectName("SkipButton");
        SkipButton->setMinimumSize(QSize(140, 0));
        SkipButton->setAutoDefault(false);

        gridLayout->addWidget(SkipButton, 16, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        lineEdit_Wards = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Wards->setObjectName("lineEdit_Wards");

        gridLayout->addWidget(lineEdit_Wards, 14, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        lineEdit_Salary = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Salary->setObjectName("lineEdit_Salary");

        gridLayout->addWidget(lineEdit_Salary, 12, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        SaveButton = new QPushButton(gridLayoutWidget);
        SaveButton->setObjectName("SaveButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SaveButton->sizePolicy().hasHeightForWidth());
        SaveButton->setSizePolicy(sizePolicy);
        SaveButton->setMinimumSize(QSize(140, 0));
        SaveButton->setAutoDefault(false);

        gridLayout->addWidget(SaveButton, 15, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        lineEdit_Pasport = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Pasport->setObjectName("lineEdit_Pasport");

        gridLayout->addWidget(lineEdit_Pasport, 8, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 11, 0, 1, 1);

        lineEdit_Phone = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Phone->setObjectName("lineEdit_Phone");

        gridLayout->addWidget(lineEdit_Phone, 6, 0, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font: 700 22pt \"Segoe UI\";"));

        gridLayout->addWidget(label_10, 0, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        lineEdit_WA = new CustomLineEdit(gridLayoutWidget);
        lineEdit_WA->setObjectName("lineEdit_WA");

        gridLayout->addWidget(lineEdit_WA, 10, 0, 1, 1);

        lineEdit_FIO = new CustomLineEdit(gridLayoutWidget);
        lineEdit_FIO->setObjectName("lineEdit_FIO");

        gridLayout->addWidget(lineEdit_FIO, 2, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 13, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 17, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);


        retranslateUi(AddDirector);

        QMetaObject::connectSlotsByName(AddDirector);
    } // setupUi

    void retranslateUi(QDialog *AddDirector)
    {
        AddDirector->setWindowTitle(QCoreApplication::translate("AddDirector", "Dialog", nullptr));
        label_5->setText(QCoreApplication::translate("AddDirector", "\320\240\320\260\320\261\320\276\321\207\320\270\320\271 \321\201\321\202\320\260\320\266", nullptr));
        SkipButton->setText(QCoreApplication::translate("AddDirector", "\320\237\321\200\320\276\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("AddDirector", "\320\235\320\276\320\274\320\265\321\200 \321\202\320\265\320\273\320\265\321\204\320\276\320\275\320\260", nullptr));
        label->setText(QCoreApplication::translate("AddDirector", "\320\244\320\230\320\236", nullptr));
        SaveButton->setText(QCoreApplication::translate("AddDirector", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("AddDirector", "\320\237\320\260\321\201\320\277\320\276\321\200\321\202\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265(\321\201\320\265\321\200\320\270\321\217 \320\270 \320\275\320\276\320\274\320\265\321\200)", nullptr));
        label_6->setText(QCoreApplication::translate("AddDirector", "\320\227\320\260\321\200. \320\277\320\273\320\260\321\202\320\260", nullptr));
        label_10->setText(QCoreApplication::translate("AddDirector", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("AddDirector", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        label_7->setText(QCoreApplication::translate("AddDirector", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\276\320\264\321\207\320\270\320\275\320\265\320\275\320\275\321\213\321\205", nullptr));
        label_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddDirector: public Ui_AddDirector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDIRECTOR_H
