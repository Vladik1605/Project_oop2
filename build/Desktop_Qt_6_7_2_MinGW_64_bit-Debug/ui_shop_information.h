/********************************************************************************
** Form generated from reading UI file 'shop_information.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOP_INFORMATION_H
#define UI_SHOP_INFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Shop_Information
{
public:
    QWidget *formLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLineEdit *lineEdit_Name;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *lineEdit_Director;
    QHBoxLayout *horizontalLayout;
    QPushButton *WorkersButton;
    QPushButton *ProductsButton;
    QPushButton *DirectorButton;
    QPushButton *DeleteButton;
    QLabel *label_2;
    QLineEdit *lineEdit_Spec;
    QLabel *label_8;
    QLabel *label_4;
    QLineEdit *lineEdit_Address;
    QLabel *label_7;
    QPushButton *RedactButton;

    void setupUi(QDialog *Shop_Information)
    {
        if (Shop_Information->objectName().isEmpty())
            Shop_Information->setObjectName("Shop_Information");
        Shop_Information->resize(439, 383);
        formLayoutWidget = new QWidget(Shop_Information);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(40, 20, 379, 315));
        gridLayout = new QGridLayout(formLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(7);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(15, 0, 15, 0);
        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(0, 20));
        label_6->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(label_6, 2, 1, 1, 1);

        lineEdit_Name = new QLineEdit(formLayoutWidget);
        lineEdit_Name->setObjectName("lineEdit_Name");

        gridLayout->addWidget(lineEdit_Name, 1, 1, 1, 1);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(0, 0));
        label_5->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(label_5, 0, 1, 1, 1);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEdit_Director = new QLineEdit(formLayoutWidget);
        lineEdit_Director->setObjectName("lineEdit_Director");

        gridLayout->addWidget(lineEdit_Director, 5, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        WorkersButton = new QPushButton(formLayoutWidget);
        WorkersButton->setObjectName("WorkersButton");
        WorkersButton->setAutoDefault(false);

        horizontalLayout->addWidget(WorkersButton);

        ProductsButton = new QPushButton(formLayoutWidget);
        ProductsButton->setObjectName("ProductsButton");
        ProductsButton->setAutoDefault(false);

        horizontalLayout->addWidget(ProductsButton);

        DirectorButton = new QPushButton(formLayoutWidget);
        DirectorButton->setObjectName("DirectorButton");
        DirectorButton->setAutoDefault(false);

        horizontalLayout->addWidget(DirectorButton);

        DeleteButton = new QPushButton(formLayoutWidget);
        DeleteButton->setObjectName("DeleteButton");
        DeleteButton->setAutoDefault(false);

        horizontalLayout->addWidget(DeleteButton);


        gridLayout->addLayout(horizontalLayout, 9, 0, 1, 2);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        lineEdit_Spec = new QLineEdit(formLayoutWidget);
        lineEdit_Spec->setObjectName("lineEdit_Spec");

        gridLayout->addWidget(lineEdit_Spec, 7, 1, 1, 1);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName("label_8");
        label_8->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(label_8, 6, 1, 1, 1);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        lineEdit_Address = new QLineEdit(formLayoutWidget);
        lineEdit_Address->setObjectName("lineEdit_Address");

        gridLayout->addWidget(lineEdit_Address, 3, 1, 1, 1);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName("label_7");
        label_7->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(label_7, 4, 1, 1, 1);

        RedactButton = new QPushButton(formLayoutWidget);
        RedactButton->setObjectName("RedactButton");
        RedactButton->setAutoDefault(false);

        gridLayout->addWidget(RedactButton, 8, 0, 1, 2);


        retranslateUi(Shop_Information);

        QMetaObject::connectSlotsByName(Shop_Information);
    } // setupUi

    void retranslateUi(QDialog *Shop_Information)
    {
        Shop_Information->setWindowTitle(QCoreApplication::translate("Shop_Information", "Dialog", nullptr));
        label_6->setText(QString());
        label_5->setText(QString());
        label_3->setText(QCoreApplication::translate("Shop_Information", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200", nullptr));
        label->setText(QCoreApplication::translate("Shop_Information", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 ", nullptr));
        WorkersButton->setText(QCoreApplication::translate("Shop_Information", "\320\240\320\260\320\261\320\276\321\202\320\275\320\270\320\272\320\270", nullptr));
        ProductsButton->setText(QCoreApplication::translate("Shop_Information", "\320\237\321\200\320\276\320\264\321\203\320\272\321\202\321\213", nullptr));
        DirectorButton->setText(QCoreApplication::translate("Shop_Information", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200", nullptr));
        DeleteButton->setText(QCoreApplication::translate("Shop_Information", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("Shop_Information", "\320\220\320\264\321\200\320\265\321\201 ", nullptr));
        label_8->setText(QString());
        label_4->setText(QCoreApplication::translate("Shop_Information", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        label_7->setText(QString());
        RedactButton->setText(QCoreApplication::translate("Shop_Information", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Shop_Information: public Ui_Shop_Information {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOP_INFORMATION_H
