#include "tea_grade.h"
#include "ui_tea_grade.h"
#include "tea_menu.h"
#include"Education/teacher.h"
#include"Global.h"
using namespace  std;
void Tea_grade::updateStuTable(Course c)
{
    vector<pair<string,int>> StuSco=c.getStudentsIdScore();
    QStandardItemModel*model = new QStandardItemModel();

    /* 设置列数 */
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "学生学号");
    model->setHeaderData(1, Qt::Horizontal, "学生姓名");
    model->setHeaderData(2, Qt::Horizontal, "学生性别");
    model->setHeaderData(3, Qt::Horizontal, "学生学院");
    model->setHeaderData(4, Qt::Horizontal, "学生成绩");

    //得到学生上的课,对应成绩，以数组形式返回

    /* 设置行数 */
    model->setRowCount(StuSco.size());
    //        model->setHeaderData(0, Qt::Vertical, "");

    ui->StuTableView->setModel(model);
    /* 行颜色交替显示 */
    ui->StuTableView->setAlternatingRowColors(true);
    /* 不允许在图形界面修改内容 */
  //  ui->StuTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->StuTableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->StuTableView->setItemDelegateForColumn(1, readOnlyDelegate);
    ui->StuTableView->setItemDelegateForColumn(2, readOnlyDelegate);
    ui->StuTableView->setItemDelegateForColumn(3, readOnlyDelegate);
    IntDelegate*intDelegate=new IntDelegate();
    ui->StuTableView->setItemDelegateForColumn(4, intDelegate);
    // 遍历结果集，并添加记录到ListView
    for(unsigned i=0;i<StuSco.size();i++)
    {
        bool isSuccess1=false;
        std::string info1;
        Student S("null","null","null","null","null","null","null");
        std::tie(isSuccess1,info1,S)=Student::LoadFromDB(StuSco[i].first);
        assert(isSuccess1);
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(S.getSID())));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(S.getSName())));
        model->setItem(i, 2, new QStandardItem(QString::fromStdString(S.getGender())));
        model->setItem(i, 3, new QStandardItem(QString::fromStdString(S.getINmae())));
        model->setItem(i, 4, new QStandardItem(QString::number(StuSco[i].second)));
    }
    ui->StuTableView->adjustSize();
    ui->StuTableView->show();

}

void Tea_grade::saveStuTable()
{
    QStandardItemModel*model=(QStandardItemModel*)ui->StuTableView->model();
    bool flag=true;
    for(int i=0;i<model->rowCount();i++)
    {
        string sid = model->data(model->index(i,0)).toString().toStdString();
        bool isSuccess;
        string info;
        Course C("null","null","null",0.0,0);;
        std::tie(isSuccess,info,C)=Course::LoadFromDB(ui->comboBoxCourse->currentText().toStdString());
        if(isSuccess)
        {
            bool ok=false;
            int score=model->data(model->index(i,4)).toInt(&ok);
            if(ok)
            {
                if(!C.updataScore(sid,score))
                {
                    QMessageBox::warning(this,"警告","保存失败");
                    flag=false;
                    break;
                }
            }
            else
            {
                QMessageBox::warning(this,model->data(model->index(i,0)).toString(),"请输入正确分数格式");
                flag=false;
                break;
            }
        }
        else
        {
            QMessageBox::warning(this,"警告","保存失败");
            flag=false;
            break;
        }
    }
    if(flag)
            QMessageBox::information(this,"提示","保存成功");
}

Tea_grade::Tea_grade(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tea_grade)
{
    ui->setupUi(this);
}

Tea_grade::~Tea_grade()
{
    delete ui;
}

void Tea_grade::Welcome(const QString &str){
    ui->label_2->setText(str);
    Teacher teacher("null","null","null","null",0.0,"null");
    bool isSuccess;
    string info;
    std::tie(isSuccess,info,teacher)=Teacher::LoadFromDB(str.toStdString());
    assert(isSuccess);
    vector<pair<string,teachTime>> Scores=teacher.getCoursesId();
    for(unsigned i=0;i<Scores.size();i++)
        ui->comboBoxCourse->addItem(QString::fromStdString(Scores[i].first));
    if(!ui->comboBoxCourse->size().isEmpty())
    {
        Course C("null","null","null",0.0,0);;
        std::tie(isSuccess,info,C)=Course::LoadFromDB(ui->comboBoxCourse->currentText().toStdString());
        if(isSuccess)
            updateStuTable(C);
    }

}

void Tea_grade::on_pushButton_clicked()
{
    this->close();
    Tea_menu *tea_menu=new Tea_menu();
    tea_menu->Welcome(ui->label_2->text());
    tea_menu->show();
}
void Tea_grade::on_comboBoxCourse_currentIndexChanged(const QString &arg1)
{
    bool isSuccess;
    string info=arg1.toStdString();
    if(!ui->comboBoxCourse->size().isEmpty())
    {
        Course C("null","null","null",0.0,0);;
        std::tie(isSuccess,info,C)=Course::LoadFromDB(ui->comboBoxCourse->currentText().toStdString());
        if(isSuccess)
            updateStuTable(C);
    }
}

void Tea_grade::on_save_clicked()
{
    saveStuTable();
}


