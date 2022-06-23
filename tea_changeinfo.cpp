#include "tea_changeinfo.h"
#include "ui_tea_changeinfo.h"
#include "tea_menu.h"
#include "Education/teacher.h"
#include "QMessageBox"
#include"Global.h"

Tea_changeInfo::Tea_changeInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tea_changeInfo)
{
    ui->setupUi(this);
    addInstitude2ComboBox(ui->comboBoxInstitute);
}

Tea_changeInfo::~Tea_changeInfo()
{
    delete ui;
}

void Tea_changeInfo::Welcome(const QString &str){
    ui->label_3->setText(str);
    std::string teacherId=ui->label_3->text().toStdString();
    bool isSuccess;
    std::string info;
    Teacher T(teacherId,"null","null","null",0.0,"null");
    std::tie(isSuccess,info,T)=Teacher::LoadFromDB(teacherId);
    ui->comboBoxInstitute->setCurrentText(QString::fromStdString(T.getIName()));
    ui->password0->setText(QString::fromStdString(T.getPasswd()));
    ui->phone0->setText(QString::fromStdString(T.getPhoneNum()));
    ui->salary0->setValue(T.getSalary());
}

void Tea_changeInfo::on_pushButton_clicked()
{
    this->close();
    Tea_menu *tea_menu=new Tea_menu();
    tea_menu->Welcome(ui->label_3->text());
    tea_menu->show();
}

void Tea_changeInfo::on_pushButton_2_clicked()
{
    std::string teacherId=ui->label_3->text().toStdString();
    bool isSuccess;
    std::string info;
    Teacher T(teacherId,"null","null","null",0.0,"null");
    std::tie(isSuccess,info,T)=Teacher::LoadFromDB(teacherId);
    T.setInstitute(ui->comboBoxInstitute->currentText().toStdString());
    T.setPassWd(ui->password0->text().toStdString());
    T.setPhoneNum(ui->phone0->text().toStdString());
    T.setSalary((float)ui->salary0->value());
    if(T.updata2DB()==true){
        QMessageBox::information(this,"通知","修改成功");
        this->close();
        Tea_menu *tea_menu=new Tea_menu();
        tea_menu->Welcome(ui->label_3->text());
        tea_menu->show();
    }
    else{
        QMessageBox::warning(this,"警告","修改失败");
    }
}
