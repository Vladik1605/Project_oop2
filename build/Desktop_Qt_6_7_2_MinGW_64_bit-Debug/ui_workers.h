/********************************************************************************
** Form generated from reading UI file 'workers.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKERS_H
#define UI_WORKERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Workers
{
public:
    QPushButton *AddWorkerButton;
    QPushButton *SaveButton;
    QPushButton *DeleteButton;
    QPushButton *RedactButton;

    void setupUi(QDialog *Workers)
    {
        if (Workers->objectName().isEmpty())
            Workers->setObjectName("Workers");
        Workers->resize(583, 401);
        AddWorkerButton = new QPushButton(Workers);
        AddWorkerButton->setObjectName("AddWorkerButton");
        AddWorkerButton->setGeometry(QRect(500, 330, 84, 40));
        AddWorkerButton->setMinimumSize(QSize(0, 40));
        AddWorkerButton->setStyleSheet(QString::fromUtf8("font: 600 14pt \"Segoe UI\";"));
        AddWorkerButton->setAutoDefault(false);
        SaveButton = new QPushButton(Workers);
        SaveButton->setObjectName("SaveButton");
        SaveButton->setGeometry(QRect(420, 330, 83, 40));
        SaveButton->setMinimumSize(QSize(0, 40));
        SaveButton->setAutoDefault(false);
        DeleteButton = new QPushButton(Workers);
        DeleteButton->setObjectName("DeleteButton");
        DeleteButton->setGeometry(QRect(230, 330, 83, 40));
        DeleteButton->setMinimumSize(QSize(0, 40));
        DeleteButton->setAutoDefault(false);
        RedactButton = new QPushButton(Workers);
        RedactButton->setObjectName("RedactButton");
        RedactButton->setGeometry(QRect(310, 330, 111, 40));
        RedactButton->setMinimumSize(QSize(0, 40));
        RedactButton->setAutoDefault(false);

        retranslateUi(Workers);

        QMetaObject::connectSlotsByName(Workers);
    } // setupUi

    void retranslateUi(QDialog *Workers)
    {
        Workers->setWindowTitle(QCoreApplication::translate("Workers", "Dialog", nullptr));
        AddWorkerButton->setText(QCoreApplication::translate("Workers", "+", nullptr));
        SaveButton->setText(QCoreApplication::translate("Workers", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        DeleteButton->setText(QCoreApplication::translate("Workers", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        RedactButton->setText(QCoreApplication::translate("Workers", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Workers: public Ui_Workers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKERS_H
