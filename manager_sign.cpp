#include "manager_sign.h"
#include "ui_manager_sign.h"
#include "login.h"
#include "Education/manager.h"
#include "QMessageBox"
#include"Global.h"
Manager_sign::Manager_sign(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager_sign)
{
    ui->setupUi(this);
    addInstitude2ComboBox(ui->comboBoxInstitude);
}

Manager_sign::~Manager_sign()
{
    delete ui;
}

void Manager_sign::on_pushButton_clicked()
{
    this->close();
    Login *login=new Login();
    login->show();
}

void Manager_sign::on_pushButton_2_clicked()
{
    Manager manager(ui->account0->text().toStdString(),ui->name0->text().toStdString(),ui->comboBoxInstitude->currentText().toStdString(),ui->password0->text().toStdString());
    if(Manager::Rigister(manager).first){
        QMessageBox::information(this,"通知","注册成功");
        this->close();
        Login *login=new Login();
        login->show();
    }
    else{
        QMessageBox::warning(this,"警告","注册失败");
    }
}
