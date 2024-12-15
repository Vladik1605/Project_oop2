/********************************************************************************
** Form generated from reading UI file 'director.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRECTOR_H
#define UI_DIRECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Director
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_6;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QLabel *label_6;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_7;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton;
    QLabel *label_10;

    void setupUi(QDialog *Director)
    {
        if (Director->objectName().isEmpty())
            Director->setObjectName("Director");
        Director->resize(690, 678);
        gridLayoutWidget = new QWidget(Director);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(60, 10, 553, 621));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setVerticalSpacing(7);
        gridLayout->setContentsMargins(15, 7, 15, 10);
        lineEdit_6 = new QLineEdit(gridLayoutWidget);
        lineEdit_6->setObjectName("lineEdit_6");

        gridLayout->addWidget(lineEdit_6, 12, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 13, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 9, 0, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout->addWidget(lineEdit_2, 4, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 11, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(140, 0));
        pushButton_2->setAutoDefault(false);

        gridLayout->addWidget(pushButton_2, 16, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        lineEdit_7 = new QLineEdit(gridLayoutWidget);
        lineEdit_7->setObjectName("lineEdit_7");

        gridLayout->addWidget(lineEdit_7, 14, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(gridLayoutWidget);
        lineEdit_4->setObjectName("lineEdit_4");

        gridLayout->addWidget(lineEdit_4, 8, 0, 1, 1);

        lineEdit_3 = new QLineEdit(gridLayoutWidget);
        lineEdit_3->setObjectName("lineEdit_3");

        gridLayout->addWidget(lineEdit_3, 6, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        lineEdit_5 = new QLineEdit(gridLayoutWidget);
        lineEdit_5->setObjectName("lineEdit_5");

        gridLayout->addWidget(lineEdit_5, 10, 0, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(140, 0));
        pushButton->setAutoDefault(false);

        gridLayout->addWidget(pushButton, 15, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font: 700 22pt \"Segoe UI\";"));

        gridLayout->addWidget(label_10, 0, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);


        retranslateUi(Director);

        QMetaObject::connectSlotsByName(Director);
    } // setupUi

    void retranslateUi(QDialog *Director)
    {
        Director->setWindowTitle(QCoreApplication::translate("Director", "Dialog", nullptr));
        label_7->setText(QCoreApplication::translate("Director", "\320\241\320\265\320\272\321\202\320\276\321\200 \320\274\320\260\320\263\320\260\320\267\320\270\320\275\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("Director", "\320\237\320\260\321\201\320\277\320\276\321\200\321\202\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265(\321\201\320\265\321\200\320\270\321\217 \320\270 \320\275\320\276\320\274\320\265\321\200)", nullptr));
        label_5->setText(QCoreApplication::translate("Director", "\320\240\320\260\320\261\320\276\321\207\320\270\320\271 \321\201\321\202\320\260\320\266", nullptr));
        label_6->setText(QCoreApplication::translate("Director", "\320\227\320\260\321\200. \320\277\320\273\320\260\321\202\320\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Director", "\320\237\321\200\320\276\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("Director", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        label->setText(QCoreApplication::translate("Director", "\320\244\320\230\320\236", nullptr));
        label_3->setText(QCoreApplication::translate("Director", "\320\235\320\276\320\274\320\265\321\200 \321\202\320\265\320\273\320\265\321\204\320\276\320\275\320\260", nullptr));
        pushButton->setText(QCoreApplication::translate("Director", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_10->setText(QCoreApplication::translate("Director", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\200\320\260\320\261\320\276\321\202\320\275\320\270\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Director: public Ui_Director {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRECTOR_H
