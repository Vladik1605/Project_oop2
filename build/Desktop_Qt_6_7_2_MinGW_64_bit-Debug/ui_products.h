/********************************************************************************
** Form generated from reading UI file 'products.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTS_H
#define UI_PRODUCTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Products
{
public:
    QPushButton *AddProductButton;
    QPushButton *SaveChangeButton;
    QPushButton *RedactButton;
    QPushButton *DeleteButton;
    QPushButton *MakePdfButton;

    void setupUi(QDialog *Products)
    {
        if (Products->objectName().isEmpty())
            Products->setObjectName("Products");
        Products->resize(602, 473);
        AddProductButton = new QPushButton(Products);
        AddProductButton->setObjectName("AddProductButton");
        AddProductButton->setGeometry(QRect(430, 350, 84, 40));
        AddProductButton->setMinimumSize(QSize(0, 40));
        AddProductButton->setStyleSheet(QString::fromUtf8("font: 600 14pt \"Segoe UI\";"));
        AddProductButton->setAutoDefault(false);
        SaveChangeButton = new QPushButton(Products);
        SaveChangeButton->setObjectName("SaveChangeButton");
        SaveChangeButton->setGeometry(QRect(350, 350, 83, 40));
        SaveChangeButton->setMinimumSize(QSize(0, 40));
        SaveChangeButton->setAutoDefault(false);
        RedactButton = new QPushButton(Products);
        RedactButton->setObjectName("RedactButton");
        RedactButton->setGeometry(QRect(240, 350, 111, 40));
        RedactButton->setMinimumSize(QSize(0, 40));
        RedactButton->setAutoDefault(false);
        DeleteButton = new QPushButton(Products);
        DeleteButton->setObjectName("DeleteButton");
        DeleteButton->setGeometry(QRect(160, 350, 83, 40));
        DeleteButton->setMinimumSize(QSize(0, 40));
        DeleteButton->setAutoDefault(false);
        MakePdfButton = new QPushButton(Products);
        MakePdfButton->setObjectName("MakePdfButton");
        MakePdfButton->setGeometry(QRect(30, 350, 131, 40));
        MakePdfButton->setMinimumSize(QSize(0, 40));
        MakePdfButton->setAutoDefault(false);

        retranslateUi(Products);

        QMetaObject::connectSlotsByName(Products);
    } // setupUi

    void retranslateUi(QDialog *Products)
    {
        Products->setWindowTitle(QCoreApplication::translate("Products", "Dialog", nullptr));
        AddProductButton->setText(QCoreApplication::translate("Products", "+", nullptr));
        SaveChangeButton->setText(QCoreApplication::translate("Products", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        RedactButton->setText(QCoreApplication::translate("Products", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        DeleteButton->setText(QCoreApplication::translate("Products", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        MakePdfButton->setText(QCoreApplication::translate("Products", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 pdf", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Products: public Ui_Products {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTS_H
