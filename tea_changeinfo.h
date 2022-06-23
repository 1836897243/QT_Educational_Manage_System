#ifndef TEA_CHANGEINFO_H
#define TEA_CHANGEINFO_H

#include <QMainWindow>

namespace Ui {
class Tea_changeInfo;
}

class Tea_changeInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tea_changeInfo(QWidget *parent = nullptr);
    void Welcome(const QString &str);
    ~Tea_changeInfo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Tea_changeInfo *ui;
};

#endif // TEA_CHANGEINFO_H
