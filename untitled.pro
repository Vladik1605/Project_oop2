QT = core
QT += uitools
QT += gui
QT += widgets
QT += sql
QT += xml
QT += printsupport
QT += testlib


LIBS += -L"C:\KDReports\build\lib" -lkdreports
INCLUDEPATH += "C:\kdreport\include\KDReports-qt6"

# Статическая линковка (уберите если библиотека динамическая)

# Использование C++17

# Для консольного приложения
CONFIG += console
CONFIG += testcase

SOURCES += \
    AddDirector.cpp \
    AddingShopTest.cpp \
    addingshop.cpp \
    addingworker.cpp \
    filesaving.cpp \
    main.cpp \
    mainwindow.cpp \
    products.cpp \
    redact_director.cpp \
    shop_information.cpp \
    workers.cpp

HEADERS += \
    AddDirector.h \
    Delegate.h \
    Exceptions.h \
    addingshop.h \
    addingshoptest.h \
    addingworker.h \
    classes.h \
    filesaving.h \
    mainwindow.h \
    products.h \
    redact_director.h \
    shop_information.h \
    workers.h

FORMS += \
    AddDirector.ui \
    addingshop.ui \
    addingworker.ui \
    filesaving.ui \
    mainwindow.ui \
    products.ui \
    redact_director.ui \
    shop_information.ui \
    tamplate_report.ui \
    workers.ui

SUBDIRS += \
    ../widgets/widgets.pro

# Для деплоя
!isEmpty(target.path): INSTALLS += target
