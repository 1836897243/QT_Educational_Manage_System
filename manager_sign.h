#ifndef MANAGER_SIGN_H
#define MANAGER_SIGN_H

#include <QMainWindow>

namespace Ui {
class Manager_sign;
}

class Manager_sign : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager_sign(QWidget *parent = nullptr);
    ~Manager_sign();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Manager_sign *ui;
};

#endif // MANAGER_SIGN_H
