#include "stu_changeinfo.h"
#include "ui_stu_changeinfo.h"
#include "student_menu.h"
#include "Education/student.h"
#include "QMessageBox"
#include"Global.h"
#include<QDate>
Stu_changeInfo::Stu_changeInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Stu_changeInfo)
{
    ui->setupUi(this);
    addInstitude2ComboBox(ui->comboBoxInstitute);
    addSex2ComboBox(ui->comboBoxGender);
}

Stu_changeInfo::~Stu_changeInfo()
{
    delete ui;
}

void Stu_changeInfo::Welcome(const QString &str){
    ui->label_3->setText(str);
    std::string studentId=ui->label_3->text().toStdString();
    bool isSuccess;
    std::string info;
    Student S(studentId,"null","null","null","null","null","null");
    std::tie(isSuccess,info,S)=Student::LoadFromDB(studentId);
    ui->comboBoxGender->setCurrentText(QString::fromStdString(S.getGender()));
    ui->comboBoxInstitute->setCurrentText(QString::fromStdString(S.getINmae()));
    ui->password0->setText(QString::fromStdString(S.getPasswd()));
    ui->phone0->setText(QString::fromStdString(S.getPhone()));
    ui->birthday0->setDate(QDate::fromString(QString::fromStdString(S.getBirthday())));
}

void Stu_changeInfo::on_pushButton_clicked()
{
    this->close();
    Student_menu *student_menu=new Student_menu();
    student_menu->Welcome(ui->label_3->text());
    student_menu->show();
}

void Stu_changeInfo::on_pushButton_2_clicked()
{
    std::string studentId=ui->label_3->text().toStdString();
    bool isSuccess;
    std::string info;
    Student S(studentId,"null","null","null","null","null","null");
    std::tie(isSuccess,info,S)=Student::LoadFromDB(studentId);

    S.setGender(ui->comboBoxGender->currentText().toStdString());
    S.setInstitute(ui->comboBoxInstitute->currentText().toStdString());
    S.setPassWd(ui->password0->text().toStdString());
    S.setPhoneNum(ui->phone0->text().toStdString());
    S.setBirthday(ui->birthday0->date().toString().toStdString());
    if(S.updata2DB()==true){
        QMessageBox::information(this,"通知","修改成功");
        this->close();
        Student_menu *student_menu=new Student_menu();
        student_menu->Welcome(ui->label_3->text());
        student_menu->show();
    }
    else{
        QMessageBox::warning(this,"警告","修改失败");
    }
}
