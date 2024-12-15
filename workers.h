#ifndef WORKERS_H
#define WORKERS_H

#include <QDialog>
#include <QTableWidget>
#include <QSqlDatabase>
#include "classes.h"
#include "addingworker.h"

namespace Ui {
class Workers;
}

/**
 * @brief Класс Workers
 *
 * Этот класс предоставляет интерфейс для работы с сотрудниками магазина.
 * Включает функционал добавления, редактирования, удаления и просмотра информации о сотрудниках.
 */
class Workers : public QDialog {
    Q_OBJECT

public:

    explicit Workers(QWidget *parent = nullptr, QString shop_id = "");

    ~Workers();

private slots:

    void on_AddWorkerButton_clicked();

    void on_SaveButton_clicked();

    void on_RedactButton_clicked();

    void on_DeleteButton_clicked();

private:
    Ui::Workers *ui; ///< Указатель на интерфейс пользователя
    QTableWidget *tableWidget; ///< Таблица для отображения сотрудников
    QString shop_id; ///< Идентификатор магазина
    QSqlDatabase db; ///< Объект подключения к базе данных
    int row; ///< Индекс текущей строки таблицы
    Asistant* worker; ///< Указатель на объект сотрудника
    CustomLineEdit *ld_FIO, *ld_Birth, *ld_Phone, *ld_Pasport, *ld_WA, *ld_Salary, *ld_Sector, *ld_Over; ///< Поля ввода данных сотрудников
    QVector<QString> all_id; ///< Список идентификаторов всех сотрудников
    QVector<bool> isRowSaved; ///< Флаги сохранения состояния строк таблицы
};

#endif // WORKERS_H
