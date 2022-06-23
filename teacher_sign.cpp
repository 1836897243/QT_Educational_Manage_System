#include "teacher_sign.h"
#include "ui_teacher_sign.h"
#include "login.h"
#include "Education/teacher.h"
#include "QMessageBox"
#include"Global.h"
Teacher_sign::Teacher_sign(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Teacher_sign)
{
    ui->setupUi(this);
    addInstitude2ComboBox(ui->comboBoxInstitute);
}

Teacher_sign::~Teacher_sign()
{
    delete ui;
}

void Teacher_sign::on_pushButton_clicked()
{
    this->close();
    Login *login=new Login();
    login->show();
}

void Teacher_sign::on_pushButton_2_clicked()
{
    Teacher teacher(ui->account0->text().toStdString(),ui->name0->text().toStdString(),ui->comboBoxInstitute->currentText().toStdString(),ui->phone0->text().toStdString(),(float)ui->salary0->value(),
                    ui->password0->text().toStdString());
    if(Teacher::Rigister(teacher).first){
        QMessageBox::information(this,"通知","注册成功");
        this->close();
        Login *login=new Login();
        login->show();
    }
    else{
        QMessageBox::warning(this,"警告","注册失败");
    }
}
