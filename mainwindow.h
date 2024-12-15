#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QMainWindow>
#include <QtUiTools>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QScrollArea>

namespace Ui {
class MainWindow;
}

/**
 * @brief Основной класс приложения, представляющий главное окно.
 *
 * Класс MainWindow предоставляет функционал для работы с главным интерфейсом приложения,
 * включая управление кнопками, выпадающим меню и диалоговыми окнами.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_AddButton_clicked(bool checked);

    void on_ChooseButton_clicked();

    void on_SaveButton_clicked();

    void on_UploadButton_clicked();

private:
    QSqlDatabase db; ///< Объект подключения к базе данных
    Ui::MainWindow *ui; ///< Указатель на интерфейс главного окна
    QScrollArea *scrollArea; ///< Прокручиваемая область для меню
    QWidget *menuContainer; ///< Контейнер для элементов меню
    QVBoxLayout *menuLayout; ///< Вертикальный компоновщик для меню
    bool firstClick; ///< Флаг для обработки первого клика

    void removeButtonByName(const QString& buttonName);

public slots:

    void handleRemoveButtonRequest(const QString& buttonName) {
        removeButtonByName(buttonName);
    }
};

#endif // MAINWINDOW_H
