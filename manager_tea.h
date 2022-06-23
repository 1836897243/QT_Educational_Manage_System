#ifndef MANAGER_TEA_H
#define MANAGER_TEA_H

#include <QMainWindow>

namespace Ui {
class Manager_tea;
}

class Manager_tea : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager_tea(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    ~Manager_tea();
private:
    void updateTeaTable();
    void saveTeaTable();
private slots:
    void on_pushButton_clicked();

    void on_save_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Manager_tea *ui;
};

#endif // MANAGER_TEA_H
