#ifndef FILESAVING_H
#define FILESAVING_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTimer>
#include <QTableWidget>

namespace Ui {
class FileSaving;
}

/**
 * @brief Класс FileSaving
 *
 * Класс реализует функционал для сохранения данных из таблицы в файл.
 */
class FileSaving : public QDialog
{
    Q_OBJECT

public:

    explicit FileSaving(QWidget *parent = nullptr, QString str = "", QTableWidget* table = nullptr);

    ~FileSaving();

private slots:

    void AcceptButton();

    void ChooseButton();

    void fadeOut();

private:
    Ui::FileSaving *ui; ///< Указатель на интерфейс пользователя
    QSqlDatabase db; ///< Объект подключения к базе данных
    QTimer *timer; ///< Таймер для анимации исчезновения
    QString parent; ///< Строка, содержащая информацию о файле
    QTableWidget* table; ///< Указатель на таблицу с данными
};

#endif // FILESAVING_H
