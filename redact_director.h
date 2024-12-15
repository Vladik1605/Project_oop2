#ifndef REDACT_DIRECTOR_H
#define REDACT_DIRECTOR_H

#include <QDialog>
#include <QSqlDatabase>
#include "classes.h"

namespace Ui {
class Redact_Director;
}

/**
 * @brief Класс Redact_Director
 *
 * Класс предоставляет функционал для редактирования данных о директоре магазина.
 */
class Redact_Director : public QDialog {
    Q_OBJECT

public:

    explicit Redact_Director(QWidget *parent = nullptr, QString director_id = "");

    ~Redact_Director();

private slots:
    void on_lineEdit_FIO_editingFinished();


    void on_lineEdit_Birth_editingFinished();

    void on_lineEdit_Phone_editingFinished();


    void on_lineEdit_Pasport_editingFinished();

    void on_lineEdit_WA_editingFinished();

    void on_lineEdit_Salary_editingFinished();

    void on_lineEdit_Wards_editingFinished();

    void on_SaveButton_clicked();



private:
    Ui::Redact_Director *ui; ///< Указатель на интерфейс пользователя
    QSqlDatabase db; ///< Объект подключения к базе данных
    bool firstClick; ///< Флаг для обработки первого клика
    Director* worker; ///< Указатель на объект директора
    QString director_id; ///< Идентификатор редактируемого директора
    QString shop_id; ///< Идентификатор магазина, к которому относится директор
};

#endif // REDACT_DIRECTOR_H
