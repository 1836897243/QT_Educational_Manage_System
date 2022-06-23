#include "manager_tea.h"
#include "ui_manager_tea.h"
#include "manager_menu.h"
#include"Education/manager.h"
#include"Education/teacher.h"
#include"Global.h"
Manager_tea::Manager_tea(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager_tea)
{
    ui->setupUi(this);
}

Manager_tea::~Manager_tea()
{
    delete ui;
}

void Manager_tea::Welcome(const QString &str){
    ui->label_3->setText(str);
    updateTeaTable();
}

void Manager_tea::updateTeaTable()
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
    assert(isSuccess);

    vector<Teacher> teachers=Teacher::getInstitudeTeacher(M.getIName());
    QStandardItemModel*model = new QStandardItemModel();

    /* 设置列数 */
    model->setColumnCount(6);
    model->setHeaderData(0, Qt::Horizontal, "教工号");
    model->setHeaderData(1, Qt::Horizontal, "教师姓名");
    model->setHeaderData(2, Qt::Horizontal, "教师学院");
    model->setHeaderData(3, Qt::Horizontal, "教师电话");
    model->setHeaderData(4, Qt::Horizontal, "教师工资");
    model->setHeaderData(5, Qt::Horizontal, "教师账号密码");

    //得到学生上的课,对应成绩，以数组形式返回

    /* 设置行数 */
    model->setRowCount(teachers.size());
    //        model->setHeaderData(0, Qt::Vertical, "");

    ui->TeatableView->setModel(model);
    /* 行颜色交替显示 */
    ui->TeatableView->setAlternatingRowColors(true);
    /* 不允许在图形界面修改内容 */
  //  ui->StuTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->TeatableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->TeatableView->setItemDelegateForColumn(2, readOnlyDelegate);

    IntDelegate*intDelegate=new IntDelegate();
    ui->TeatableView->setItemDelegateForColumn(4,intDelegate);
    // 遍历结果集，并添加记录到ListView
    for(unsigned i=0;i<teachers.size();i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(teachers[i].getTID())));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(teachers[i].getTName())));
        model->setItem(i, 2, new QStandardItem(QString::fromStdString(teachers[i].getIName())));
        model->setItem(i, 3, new QStandardItem(QString::fromStdString(teachers[i].getPhoneNum())));
        model->setItem(i, 4, new QStandardItem(QString::number(teachers[i].getSalary())));
        model->setItem(i, 5, new QStandardItem(QString::fromStdString(teachers[i].getPasswd())));
    }
    ui->TeatableView->adjustSize();
    ui->TeatableView->show();
}

void Manager_tea::saveTeaTable()
{
    QStandardItemModel*model=(QStandardItemModel*)ui->TeatableView->model();
    for(int i=0;i<model->rowCount();i++)
    {
        string Tid = model->data(model->index(i,0)).toString().toStdString();
        string Tname=model->data(model->index(i,1)).toString().toStdString();
        string Iname = model->data(model->index(i,2)).toString().toStdString();
        string Phone=model->data(model->index(i,3)).toString().toStdString();
        int Salary=model->data(model->index(i,4)).toString().toInt();
        string Passwd = model->data(model->index(i,5)).toString().toStdString();
        Teacher T(Tid,Tname,Iname,Phone,Salary,Passwd);
        T.updata2DB();
    }
    QMessageBox::information(this,"提示","保存成功");
}

void Manager_tea::on_pushButton_clicked()
{
    this->close();
    Manager_menu *manager_menu=new Manager_menu();
    manager_menu->Welcome(ui->label_3->text());
    manager_menu->show();
}

void Manager_tea::on_save_clicked()
{
    saveTeaTable();
}

void Manager_tea::on_pushButton_4_clicked()
{
    updateTeaTable();
}

void Manager_tea::on_pushButton_2_clicked()
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
    assert(isSuccess);
    Teacher teacher(ui->account0->text().toStdString(),ui->name0->text().toStdString(),M.getIName(),ui->phone0->text().toStdString(),(float)ui->salary0->value(),
                    ui->password0->text().toStdString());
    if(Teacher::Rigister(teacher).first){
        QMessageBox::warning(this,"通知","添加成功");
         updateTeaTable();
    }
    else{
        QMessageBox::warning(this,"警告","添加失败");
    }
}

void Manager_tea::on_pushButton_3_clicked()
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
    assert(isSuccess);
    Teacher teacher(ui->account0->text().toStdString(),ui->name0->text().toStdString(),M.getIName(),ui->phone0->text().toStdString(),(float)ui->salary0->value(),
                        ui->password0->text().toStdString());
        if(teacher.deleteFromDB()){
            QMessageBox::warning(this,"通知","删除成功");
            updateTeaTable();
        }
        else{
            QMessageBox::warning(this,"警告","删除失败");
        }
}
