#include "student_sign.h"
#include "ui_student_sign.h"
#include "login.h"
#include "Education/student.h"
#include "QMessageBox"
#include"Global.h"
Student_sign::Student_sign(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Student_sign)
{
    ui->setupUi(this);
    addSex2ComboBox(ui->comboBoxGender);
    addInstitude2ComboBox(ui->comboBoxIntitude);
}

Student_sign::~Student_sign()
{
    delete ui;
}

void Student_sign::on_pushButton_clicked()
{
    this->close();
    Login *login=new Login();
    login->show();
}

void Student_sign::on_pushButton_2_clicked()
{
    Student student(ui->account0->text().toStdString(),ui->name0->text().toStdString(),ui->comboBoxIntitude->currentText().toStdString(),ui->comboBoxGender->currentText().toStdString(),
                    ui->birthday0->date().toString().toStdString(),ui->phone0->text().toStdString(),ui->password0->text().toStdString());
    if(Student::Rigister(student).first){
        QMessageBox::information(this,"通知","注册成功");
        this->close();
        Login *login=new Login();
        login->show();
    }
    else{
        QMessageBox::warning(this,"警告","注册失败");
    }
}
