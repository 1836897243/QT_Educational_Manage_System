#ifndef MANAGER_MENU_H
#define MANAGER_MENU_H

#include <QMainWindow>

namespace Ui {
class Manager_menu;
}

class Manager_menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager_menu(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    ~Manager_menu();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Manager_menu *ui;
};

#endif // MANAGER_MENU_H
