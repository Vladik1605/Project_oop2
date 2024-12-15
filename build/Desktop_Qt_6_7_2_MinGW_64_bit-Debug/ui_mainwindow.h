/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *AddButton;
    QPushButton *SaveButton;
    QPushButton *UploadButton;
    QPushButton *ChooseButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(617, 403);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        action = new QAction(MainWindow);
        action->setObjectName("action");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(200, 130, 191, 141));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 0, 10, 0);
        AddButton = new QPushButton(verticalLayoutWidget);
        AddButton->setObjectName("AddButton");
        AddButton->setMinimumSize(QSize(138, 29));

        verticalLayout->addWidget(AddButton, 0, Qt::AlignmentFlag::AlignHCenter);

        SaveButton = new QPushButton(verticalLayoutWidget);
        SaveButton->setObjectName("SaveButton");
        SaveButton->setEnabled(true);
        SaveButton->setMinimumSize(QSize(138, 29));

        verticalLayout->addWidget(SaveButton, 0, Qt::AlignmentFlag::AlignHCenter);

        UploadButton = new QPushButton(verticalLayoutWidget);
        UploadButton->setObjectName("UploadButton");
        UploadButton->setMinimumSize(QSize(138, 29));

        verticalLayout->addWidget(UploadButton, 0, Qt::AlignmentFlag::AlignHCenter);

        ChooseButton = new QPushButton(verticalLayoutWidget);
        ChooseButton->setObjectName("ChooseButton");
        ChooseButton->setMinimumSize(QSize(138, 29));

        verticalLayout->addWidget(ChooseButton, 0, Qt::AlignmentFlag::AlignHCenter);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\274\320\265\320\275\321\216", nullptr));
        AddButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\274\320\260\320\263\320\260\320\267\320\270\320\275", nullptr));
        SaveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 \321\204\320\260\320\271\320\273", nullptr));
        UploadButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", nullptr));
        ChooseButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\274\320\260\320\263\320\260\320\267\320\270\320\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
