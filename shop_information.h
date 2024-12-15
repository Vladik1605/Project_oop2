#ifndef SHOP_INFORMATION_H
#define SHOP_INFORMATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QPushButton>
#include "classes.h"
#include "products.h"

namespace Ui {
class Shop_Information;
}

/**
 * @brief Класс Shop_Information
 *
 * Этот класс предоставляет интерфейс для отображения и редактирования информации о магазине.
 */
class Shop_Information : public QDialog {
    Q_OBJECT

public:

    explicit Shop_Information(QWidget *parent = nullptr, QString str = "");

    ~Shop_Information();

private slots:

    void on_ProductsButton_clicked();

    void on_RedactButton_clicked();

    void on_lineEdit_Name_editingFinished();

    void on_lineEdit_Address_editingFinished();

    void on_lineEdit_Director_editingFinished();

    void on_lineEdit_Spec_editingFinished();

    void on_WorkersButton_clicked();

    void on_DirectorButton_clicked();

    void on_DeleteButton_clicked();

signals:

    void requestRemoveButton(const QString& buttonName);

private:
    Ui::Shop_Information *ui; ///< Указатель на интерфейс пользователя
    QSqlDatabase db; ///< Объект подключения к базе данных
    bool firstClick; ///< Флаг для отслеживания первого клика
    shop* shop_inf; ///< Указатель на объект магазина
    QString shop_id; ///< Идентификатор магазина
    Products* new_products; ///< Указатель на окно управления продуктами
    QString shop_name; ///< Название магазина
};

#endif // SHOP_INFORMATION_H
