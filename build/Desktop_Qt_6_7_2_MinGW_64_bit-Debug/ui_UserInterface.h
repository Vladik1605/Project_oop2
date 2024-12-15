/********************************************************************************
** Form generated from reading UI file 'UserInterface.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINTERFACE_H
#define UI_USERINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *pushButton;
    QToolButton *toolButton;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(586, 597);
        pushButton = new QPushButton(Form);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(220, 170, 83, 29));
        toolButton = new QToolButton(Form);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(350, 300, 25, 27));
        checkBox = new QCheckBox(Form);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(190, 280, 93, 26));
        checkBox_2 = new QCheckBox(Form);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(150, 390, 93, 26));
        buttonBox = new QDialogButtonBox(Form);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(210, 460, 167, 29));
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "PushButton", nullptr));
        toolButton->setText(QCoreApplication::translate("Form", "...", nullptr));
        checkBox->setText(QCoreApplication::translate("Form", "CheckBox", nullptr));
        checkBox_2->setText(QCoreApplication::translate("Form", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINTERFACE_H
