#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QDialog>
#include "classes.h"
#include <QSqlDatabase>
#include <QLineEdit>
#include <QTableWidget>

namespace Ui {
class Products;
}

/**
 * @brief Класс Products
 *
 * Этот класс реализует функционал работы с товарами, включая их отображение,
 * редактирование, добавление и удаление в интерфейсе диалогового окна.
 */
class Products : public QDialog {
    Q_OBJECT

public:

    explicit Products(QWidget *parent = nullptr, QString shop_id = "");

    ~Products();

private slots:

    void on_AddProductButton_clicked();

    void on_SaveChangeButton_clicked();

    void on_RedactButton_clicked();

    void on_DeleteButton_clicked();

    void on_MakePdfButton_clicked();

private:
    Ui::Products *ui; ///< Указатель на интерфейс пользователя
    QSqlDatabase db; ///< Объект подключения к базе данных
    int row; ///< Индекс текущей строки таблицы
    QString shop_id; ///< Идентификатор магазина
    product_list list; ///< Список продуктов
    Product* prod; ///< Указатель на текущий продукт
    QLineEdit* ld_Name; ///< Поле ввода для параметра 3
    QLineEdit* ld_Type; ///< Поле ввода для параметра 4
    QLineEdit* ld_Size; ///< Поле ввода для параметра 5
    QLineEdit* ld_Price; ///< Поле ввода для параметра 6
    QLineEdit* ld_Stock; ///< Поле ввода для параметра 1
    QLineEdit* ld_Window; ///< Поле ввода для параметра 2
    QVector<QString> id_list; ///< Список идентификаторов продуктов
    QTableWidget *tableWidget_products; ///< Таблица для отображения продуктов
    QVector<bool> isRowSaved; ///< Флаги сохранения строк

    void loadData(QString shop_id);
};

#endif // PRODUCTS_H
