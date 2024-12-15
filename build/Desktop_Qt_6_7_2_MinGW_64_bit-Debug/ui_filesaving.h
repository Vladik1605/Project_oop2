/********************************************************************************
** Form generated from reading UI file 'filesaving.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESAVING_H
#define UI_FILESAVING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileSaving
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *ChooseButton;
    QLineEdit *lineEdit;
    QPushButton *AcceptButton;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QDialog *FileSaving)
    {
        if (FileSaving->objectName().isEmpty())
            FileSaving->setObjectName("FileSaving");
        FileSaving->resize(782, 270);
        gridLayoutWidget = new QWidget(FileSaving);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(80, 60, 591, 151));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setVerticalSpacing(7);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ChooseButton = new QPushButton(gridLayoutWidget);
        ChooseButton->setObjectName("ChooseButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChooseButton->sizePolicy().hasHeightForWidth());
        ChooseButton->setSizePolicy(sizePolicy);
        ChooseButton->setAutoDefault(false);

        gridLayout->addWidget(ChooseButton, 1, 2, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        AcceptButton = new QPushButton(gridLayoutWidget);
        AcceptButton->setObjectName("AcceptButton");
        sizePolicy.setHeightForWidth(AcceptButton->sizePolicy().hasHeightForWidth());
        AcceptButton->setSizePolicy(sizePolicy);
        AcceptButton->setStyleSheet(QString::fromUtf8("font: 10pt \"Segoe UI\";"));
        AcceptButton->setAutoDefault(false);

        gridLayout->addWidget(AcceptButton, 2, 1, 1, 2, Qt::AlignmentFlag::AlignHCenter);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(16777215, 40));

        verticalLayout->addWidget(label_2, 0, Qt::AlignmentFlag::AlignHCenter);


        gridLayout->addLayout(verticalLayout, 3, 1, 1, 2);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 40));
        label->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Segoe UI\";"));

        gridLayout->addWidget(label, 0, 1, 1, 2, Qt::AlignmentFlag::AlignHCenter);


        retranslateUi(FileSaving);

        QMetaObject::connectSlotsByName(FileSaving);
    } // setupUi

    void retranslateUi(QDialog *FileSaving)
    {
        FileSaving->setWindowTitle(QCoreApplication::translate("FileSaving", "Dialog", nullptr));
        ChooseButton->setText(QCoreApplication::translate("FileSaving", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        AcceptButton->setText(QCoreApplication::translate("FileSaving", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        label_2->setText(QString());
        label->setText(QCoreApplication::translate("FileSaving", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\277\321\203\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileSaving: public Ui_FileSaving {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESAVING_H
