#ifndef MANAGER_STU_H
#define MANAGER_STU_H

#include <QMainWindow>

namespace Ui {
class Manager_stu;
}

class Manager_stu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager_stu(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    ~Manager_stu();
private:
    void updateStuTable();
    void saveStuTable();
private slots:
    void on_pushButton_clicked();

    void on_save_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Manager_stu *ui;
};

#endif // MANAGER_STU_H
