#ifndef STU_TAKELESSION_H
#define STU_TAKELESSION_H

#include <QMainWindow>

namespace Ui {
class Stu_takeLession;
}

class Stu_takeLession : public QMainWindow
{
    Q_OBJECT

public:
    explicit Stu_takeLession(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    void Update();
    ~Stu_takeLession();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Stu_takeLession *ui;
};

#endif // STU_TAKELESSION_H
