/********************************************************************************
** Form generated from reading UI file 'redact_director.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REDACT_DIRECTOR_H
#define UI_REDACT_DIRECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "addingworker.h"

QT_BEGIN_NAMESPACE

class Ui_Redact_Director
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    CustomLineEdit *lineEdit_WA;
    CustomLineEdit *lineEdit_Phone;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_10;
    CustomLineEdit *lineEdit_Pasport;
    CustomLineEdit *lineEdit_Wards;
    QLabel *label_4;
    QLabel *label_6;
    CustomLineEdit *lineEdit_Salary;
    QLabel *label_2;
    QLabel *label_8;
    QPushButton *SaveButton;
    CustomLineEdit *lineEdit_FIO;
    QLabel *label_5;
    CustomLineEdit *lineEdit_Birth;

    void setupUi(QDialog *Redact_Director)
    {
        if (Redact_Director->objectName().isEmpty())
            Redact_Director->setObjectName("Redact_Director");
        Redact_Director->resize(676, 623);
        gridLayoutWidget = new QWidget(Redact_Director);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(70, 0, 553, 621));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setVerticalSpacing(7);
        gridLayout->setContentsMargins(15, 7, 15, 10);
        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        lineEdit_WA = new CustomLineEdit(gridLayoutWidget);
        lineEdit_WA->setObjectName("lineEdit_WA");

        gridLayout->addWidget(lineEdit_WA, 10, 0, 1, 1);

        lineEdit_Phone = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Phone->setObjectName("lineEdit_Phone");

        gridLayout->addWidget(lineEdit_Phone, 6, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 13, 0, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font: 700 22pt \"Segoe UI\";"));

        gridLayout->addWidget(label_10, 0, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        lineEdit_Pasport = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Pasport->setObjectName("lineEdit_Pasport");

        gridLayout->addWidget(lineEdit_Pasport, 8, 0, 1, 1);

        lineEdit_Wards = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Wards->setObjectName("lineEdit_Wards");

        gridLayout->addWidget(lineEdit_Wards, 14, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 11, 0, 1, 1);

        lineEdit_Salary = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Salary->setObjectName("lineEdit_Salary");

        gridLayout->addWidget(lineEdit_Salary, 12, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 16, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

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

        lineEdit_FIO = new CustomLineEdit(gridLayoutWidget);
        lineEdit_FIO->setObjectName("lineEdit_FIO");

        gridLayout->addWidget(lineEdit_FIO, 2, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 9, 0, 1, 1);

        lineEdit_Birth = new CustomLineEdit(gridLayoutWidget);
        lineEdit_Birth->setObjectName("lineEdit_Birth");

        gridLayout->addWidget(lineEdit_Birth, 4, 0, 1, 1);


        retranslateUi(Redact_Director);

        QMetaObject::connectSlotsByName(Redact_Director);
    } // setupUi

    void retranslateUi(QDialog *Redact_Director)
    {
        Redact_Director->setWindowTitle(QCoreApplication::translate("Redact_Director", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("Redact_Director", "\320\235\320\276\320\274\320\265\321\200 \321\202\320\265\320\273\320\265\321\204\320\276\320\275\320\260", nullptr));
        label->setText(QCoreApplication::translate("Redact_Director", "\320\244\320\230\320\236", nullptr));
        label_7->setText(QCoreApplication::translate("Redact_Director", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\276\320\264\321\207\320\270\320\275\320\265\320\275\320\275\321\213\321\205", nullptr));
        label_10->setText(QCoreApplication::translate("Redact_Director", "\320\230\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\265 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("Redact_Director", "\320\237\320\260\321\201\320\277\320\276\321\200\321\202\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265(\321\201\320\265\321\200\320\270\321\217 \320\270 \320\275\320\276\320\274\320\265\321\200)", nullptr));
        label_6->setText(QCoreApplication::translate("Redact_Director", "\320\227\320\260\321\200. \320\277\320\273\320\260\321\202\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("Redact_Director", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        label_8->setText(QString());
        SaveButton->setText(QCoreApplication::translate("Redact_Director", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        label_5->setText(QCoreApplication::translate("Redact_Director", "\320\240\320\260\320\261\320\276\321\207\320\270\320\271 \321\201\321\202\320\260\320\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Redact_Director: public Ui_Redact_Director {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REDACT_DIRECTOR_H
