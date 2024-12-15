#ifndef ADDDIRECTOR_H
#define ADDDIRECTOR_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTimer>
#include "classes.h"
#include <QLineEdit>

namespace Ui {
class AddDirector;
}

/**
 * @brief Класс AddDirector
 *
 * Этот класс представляет диалоговое окно для добавления нового директора.
 * Он наследует от QDialog и содержит необходимые элементы управления и слоты.
 */
class AddDirector : public QDialog
{
    Q_OBJECT

public:

    explicit AddDirector(QWidget *parent = nullptr, shop* shop=nullptr);


    ~AddDirector();

private slots:

    void on_lineEdit_FIO_editingFinished();


    void on_lineEdit_Birth_editingFinished();

    void on_lineEdit_Phone_editingFinished();


    void on_lineEdit_Pasport_editingFinished();

    void on_lineEdit_WA_editingFinished();

    void on_lineEdit_Salary_editingFinished();

    void on_lineEdit_Wards_editingFinished();

    void on_SaveButton_clicked();

    void fadeOut();

    void enableButton();

    void on_SkipButton_clicked();

private:
    Ui::AddDirector *ui; ///< Указатель на интерфейс пользователя
    shop* shop1; ///< Указатель на объект магазина
    QSqlDatabase db; ///< Объект базы данных
    QTimer *timer; ///< Таймер для различных операций
    QTimer *buttonTimer; ///< Таймер для управления кнопками
    Director* worker; ///< Указатель на объект директора
};

#endif // ADDDIRECTOR_H
