#include "manager_stu.h"
#include "ui_manager_stu.h"
#include "manager_menu.h"
#include"Education/student.h"
#include"Education/manager.h"
#include"Education/course.h"
#include"Global.h"
Manager_stu::Manager_stu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager_stu)
{
    ui->setupUi(this);
    addSex2ComboBox(ui->comboBoxGender);
}

Manager_stu::~Manager_stu()
{
    delete ui;
}

void Manager_stu::Welcome(const QString &str){
    ui->label_3->setText(str);
    updateStuTable();
}

void Manager_stu::updateStuTable()
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
    assert(isSuccess);

    vector<Student> students=Student::getInstitudeStudents(M.getIName());
    QStandardItemModel*model = new QStandardItemModel();

    /* 设置列数 */
    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, "学生学号");
    model->setHeaderData(1, Qt::Horizontal, "学生姓名");
    model->setHeaderData(2, Qt::Horizontal, "学生学院");
    model->setHeaderData(3, Qt::Horizontal, "学生性别");
    model->setHeaderData(4, Qt::Horizontal, "学生生日");
    model->setHeaderData(5, Qt::Horizontal, "学生电话");
    model->setHeaderData(6, Qt::Horizontal, "学生账号密码");

    //得到学生上的课,对应成绩，以数组形式返回

    /* 设置行数 */
    model->setRowCount(students.size());
    //        model->setHeaderData(0, Qt::Vertical, "");

    ui->StuTableView->setModel(model);
    /* 行颜色交替显示 */
    ui->StuTableView->setAlternatingRowColors(true);
    /* 不允许在图形界面修改内容 */
  //  ui->StuTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->StuTableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->StuTableView->setItemDelegateForColumn(2, readOnlyDelegate);
    SexDelegate*sexDelegate=new SexDelegate();
    ui->StuTableView->setItemDelegateForColumn(3,sexDelegate);
    DateDelegate*dateDelegate=new DateDelegate();
    ui->StuTableView->setItemDelegateForColumn(4, dateDelegate);
    // 遍历结果集，并添加记录到ListView
    for(unsigned i=0;i<students.size();i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(students[i].getSID())));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(students[i].getSName())));
        model->setItem(i, 2, new QStandardItem(QString::fromStdString(students[i].getINmae())));
        model->setItem(i, 3, new QStandardItem(QString::fromStdString(students[i].getGender())));
        model->setItem(i, 4, new QStandardItem(QString::fromStdString(students[i].getBirthday())));
        model->setItem(i, 5, new QStandardItem(QString::fromStdString(students[i].getPhone())));
        model->setItem(i, 6, new QStandardItem(QString::fromStdString(students[i].getPasswd())));
    }
    ui->StuTableView->adjustSize();
    ui->StuTableView->show();
}

void Manager_stu::saveStuTable()
{
    QStandardItemModel*model=(QStandardItemModel*)ui->StuTableView->model();
    for(int i=0;i<model->rowCount();i++)
    {
        string Sid = model->data(model->index(i,0)).toString().toStdString();
        string Sname=model->data(model->index(i,1)).toString().toStdString();
        string Iname = model->data(model->index(i,2)).toString().toStdString();
        string Gender=model->data(model->index(i,3)).toString().toStdString();
        string Birthday = model->data(model->index(i,4)).toString().toStdString();
        string Phone=model->data(model->index(i,5)).toString().toStdString();
        string Passwd = model->data(model->index(i,6)).toString().toStdString();
        Student S(Sid,Sname,Iname,Gender,Birthday,Phone,Passwd);
        S.updata2DB();
    }
    QMessageBox::information(this,"提示","保存成功");
}

void Manager_stu::on_pushButton_clicked()
{
    this->close();
    Manager_menu *manager_menu=new Manager_menu();
    manager_menu->Welcome(ui->label_3->text());
    manager_menu->show();
}

void Manager_stu::on_save_clicked()
{
    saveStuTable();
}

void Manager_stu::on_pushButton_2_clicked()
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
    assert(isSuccess);
    Student student(ui->account0->text().toStdString(),ui->name0->text().toStdString(),M.getIName(),ui->comboBoxGender->currentText().toStdString(),
                    ui->birthday0->date().toString().toStdString(),ui->phone0->text().toStdString(),ui->password0->text().toStdString());
    if(Student::Rigister(student).first){
        QMessageBox::warning(this,"通知","添加成功");
        updateStuTable();
    }
    else{
        QMessageBox::warning(this,"警告","添加失败");
    }
}

void Manager_stu::on_pushButton_4_clicked()
{
    updateStuTable();
}

void Manager_stu::on_pushButton_3_clicked()
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
    assert(isSuccess);
    Student student(ui->account0->text().toStdString(),ui->name0->text().toStdString(),M.getIName(),ui->comboBoxGender->currentText().toStdString(),
                    ui->birthday0->date().toString().toStdString(),ui->phone0->text().toStdString(),ui->password0->text().toStdString());
    if(student.deleteFromDB()){
        QMessageBox::warning(this,"通知","删除成功");
        updateStuTable();
    }
    else{
        QMessageBox::warning(this,"警告","删除失败");
    }
}
