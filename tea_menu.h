#ifndef TEA_MENU_H
#define TEA_MENU_H

#include <QMainWindow>

namespace Ui {
class Tea_menu;
}

class Tea_menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tea_menu(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    ~Tea_menu();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Tea_menu *ui;
};

#endif // TEA_MENU_H
