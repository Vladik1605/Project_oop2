/********************************************************************************
** Form generated from reading UI file 'addingshop.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDINGSHOP_H
#define UI_ADDINGSHOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddingShop
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *lineEdit_Name;
    QLabel *label_6;
    QLabel *label_2;
    QLineEdit *lineEdit_Address;
    QLabel *label_7;
    QLabel *label_4;
    QLineEdit *lineEdit_Director;
    QLabel *label_8;
    QLabel *label_5;
    QLineEdit *lineEdit_Spec;
    QPushButton *SaveButton;
    QLabel *label_9;

    void setupUi(QDialog *AddingShop)
    {
        if (AddingShop->objectName().isEmpty())
            AddingShop->setObjectName("AddingShop");
        AddingShop->resize(588, 325);
        formLayoutWidget = new QWidget(AddingShop);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(0, 10, 581, 313));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(15, 0, 15, 0);
        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::FieldRole, label_3);

        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        lineEdit_Name = new QLineEdit(formLayoutWidget);
        lineEdit_Name->setObjectName("lineEdit_Name");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_Name->sizePolicy().hasHeightForWidth());
        lineEdit_Name->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_Name);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName("label_6");

        formLayout->setWidget(3, QFormLayout::FieldRole, label_6);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_2);

        lineEdit_Address = new QLineEdit(formLayoutWidget);
        lineEdit_Address->setObjectName("lineEdit_Address");

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_Address);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName("label_7");

        formLayout->setWidget(5, QFormLayout::FieldRole, label_7);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_4);

        lineEdit_Director = new QLineEdit(formLayoutWidget);
        lineEdit_Director->setObjectName("lineEdit_Director");

        formLayout->setWidget(6, QFormLayout::FieldRole, lineEdit_Director);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName("label_8");

        formLayout->setWidget(7, QFormLayout::FieldRole, label_8);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_5);

        lineEdit_Spec = new QLineEdit(formLayoutWidget);
        lineEdit_Spec->setObjectName("lineEdit_Spec");
        lineEdit_Spec->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(8, QFormLayout::FieldRole, lineEdit_Spec);

        SaveButton = new QPushButton(formLayoutWidget);
        SaveButton->setObjectName("SaveButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SaveButton->sizePolicy().hasHeightForWidth());
        SaveButton->setSizePolicy(sizePolicy1);
        SaveButton->setAutoDefault(false);
        SaveButton->setFlat(false);

        formLayout->setWidget(10, QFormLayout::SpanningRole, SaveButton);

        label_9 = new QLabel(formLayoutWidget);
        label_9->setObjectName("label_9");

        formLayout->setWidget(9, QFormLayout::FieldRole, label_9);


        retranslateUi(AddingShop);

        QMetaObject::connectSlotsByName(AddingShop);
    } // setupUi

    void retranslateUi(QDialog *AddingShop)
    {
        AddingShop->setWindowTitle(QCoreApplication::translate("AddingShop", "Dialog", nullptr));
        label_3->setText(QString());
        label->setText(QCoreApplication::translate("AddingShop", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\274\320\260\320\263\320\260\320\267\320\270\320\275\320\260:", nullptr));
        label_6->setText(QString());
        label_2->setText(QCoreApplication::translate("AddingShop", "\320\220\320\264\321\200\320\265\321\201 \320\274\320\260\320\263\320\260\320\267\320\270\320\275\320\260:", nullptr));
        label_7->setText(QString());
        label_4->setText(QCoreApplication::translate("AddingShop", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200 \320\274\320\260\320\263\320\260\320\267\320\270\320\275\320\260:", nullptr));
        label_8->setText(QString());
        label_5->setText(QCoreApplication::translate("AddingShop", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217 \320\274\320\260\320\263\320\260\320\267\320\270\320\275\320\260:", nullptr));
        SaveButton->setText(QCoreApplication::translate("AddingShop", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddingShop: public Ui_AddingShop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDINGSHOP_H
