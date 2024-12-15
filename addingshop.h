#ifndef ADDINGSHOP_H
#define ADDINGSHOP_H

#include <QDialog>
#include <QString>
#include "classes.h"
#include <QSqlDatabase>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QLoggingCategory>


void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


void setupLogging();

namespace Ui {
class AddingShop;
}

/**
 * @brief Класс AddingShop
 *
 * Этот класс представляет диалоговое окно для добавления нового магазина.
 * Он наследует от QDialog и содержит необходимые элементы управления и слоты.
 */
class AddingShop : public QDialog
{
    Q_OBJECT

public:

    explicit AddingShop(QSqlDatabase* db=nullptr, QWidget *parent = nullptr);

    ~AddingShop();


private slots:

    void on_lineEdit_Name_editingFinished();

    void on_lineEdit_Address_editingFinished();

    void on_lineEdit_Director_editingFinished();

    void on_lineEdit_Spec_editingFinished();

    void on_SaveButton_clicked(bool checked);

private:
    Ui::AddingShop *ui; ///< Указатель на интерфейс пользователя
    shop *shop1; ///< Указатель на объект магазина
    QSqlDatabase db; ///< Объект базы данных
    QMap<QLabel*, QString> errors; ///< Словарь для хранения ошибок с соответствующими метками

    // AddingWorker worker; ///< Объект рабочего процесса добавления (закомментировано)
    friend class AddingShopTest; ///< Дружественный класс для тестирования
};

#endif // ADDINGSHOP_H
