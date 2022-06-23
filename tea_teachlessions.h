#ifndef TEA_TEACHLESSIONS_H
#define TEA_TEACHLESSIONS_H

#include <QMainWindow>

namespace Ui {
class Tea_teachLessions;
}

class Tea_teachLessions : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tea_teachLessions(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    void Update();
    ~Tea_teachLessions();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Tea_teachLessions *ui;
};

#endif // TEA_TEACHLESSIONS_H
