#include "mainwindow.h"
#include "addingshoptest.h"
#include <QApplication>
#include <QTest>
#include <QStringList>
#include "addingshop.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QStringList args = QCoreApplication::arguments();

    if (args.contains("--run-tests")) {
        AddingShopTest test;
        return QTest::qExec(&test);
    }


    MainWindow w;
    w.show();
    setupLogging();

    return app.exec();
}
