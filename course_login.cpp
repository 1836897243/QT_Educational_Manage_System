#include "course_login.h"
#include "ui_course_login.h"
#include "manager_menu.h"
#include"Education/institute.h"
#include"Education/course.h"
#include"Education/manager.h"
#include "Global.h"
Course_login::Course_login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Course_login)
{
    ui->setupUi(this);
}

Course_login::~Course_login()
{
    delete ui;
}

void Course_login::Welcome(const QString &str){
    ui->label_3->setText(str);
    updateCourseTable();
}

void Course_login::updateCourseTable()
{
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
    assert(isSuccess);
    vector<Course> CoursesInfo=Course::getInstituteCourses(M.getIName());
    QStandardItemModel*model = new QStandardItemModel();

    /* 设置列数 */
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "课程编号");
    model->setHeaderData(1, Qt::Horizontal, "课程名称");
    model->setHeaderData(2, Qt::Horizontal, "课程学分");
    model->setHeaderData(3, Qt::Horizontal, "已选人数");
    model->setHeaderData(4, Qt::Horizontal, "上限人数");;

    //得到学生上的课,对应成绩，以数组形式返回


    model->setRowCount(CoursesInfo.size());
    //        model->setHeaderData(0, Qt::Vertical, "");

    ui->tableViewCourses->setModel(model);

    ui->tableViewCourses->setAlternatingRowColors(true);

  //  ui->StuTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->tableViewCourses->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->tableViewCourses->setItemDelegateForColumn(3, readOnlyDelegate);
    CreditsDelegate*creditsDelegate=new CreditsDelegate();
    ui->tableViewCourses->setItemDelegateForColumn(2, creditsDelegate);

    IntDelegate*intDelegate=new IntDelegate();
    ui->tableViewCourses->setItemDelegateForColumn(4, intDelegate);
    // 遍历结果集，并添加记录到ListView
    for(unsigned i=0;i<CoursesInfo.size();i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(CoursesInfo[i].getCID())));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(CoursesInfo[i].getCName())));
        model->setItem(i, 2, new QStandardItem(QString::number(CoursesInfo[i].getCredits())));
        model->setItem(i, 3, new QStandardItem(QString::number(CoursesInfo[i].getStuNumber())));
        model->setItem(i, 4, new QStandardItem(QString::number(CoursesInfo[i].getQuota())));
    }
    ui->tableViewCourses->adjustSize();
    ui->tableViewCourses->show();
}

void Course_login::saveCoursTable()
{
    QStandardItemModel*model=(QStandardItemModel*)ui->tableViewCourses->model();
    bool isSuccess;
    string info;
    Manager M("null","null","null","null");
    std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
    assert(isSuccess);
    for(int i=0;i<model->rowCount();i++)
    {
        string cid = model->data(model->index(i,0)).toString().toStdString();
        string CName=model->data(model->index(i,1)).toString().toStdString();
        float Credits=model->data(model->index(i,2)).toFloat();
        int quota=model->data(model->index(i,4)).toInt();
        Course C(cid,CName,M.getIName(),Credits,quota);
        C.updata2DB();
    }
    QMessageBox::information(this,"提示","保存成功");
}

void Course_login::on_pushButton_clicked()
{
    this->close();
    Manager_menu *manager_menu=new Manager_menu();
    manager_menu->Welcome(ui->label_3->text());
    manager_menu->show();
}

void Course_login::on_addCourse_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("User input:"));
    // 课程编号
    QString CID = QString("课程编号: ");
    QLineEdit *LEcid = new QLineEdit(&dialog);
    form.addRow(CID, LEcid);
    // 课程名称
    QString CName = QString("课程名称: ");
    QLineEdit *LECName = new QLineEdit(&dialog);
    form.addRow(CName, LECName);

    // 课程学分
    QString Credits = QString("课程学分: ");
    QLineEdit *LECredits = new QLineEdit(&dialog);
    QRegExp regx("^(5|[0-4]?(\\.\\d{1,1})?)$");
    QValidator *validator = new QRegExpValidator(regx, LECredits );
    LECredits->setValidator(validator);
    form.addRow(Credits, LECredits);

    // 上限人数
    QString Quota = QString("上限人数: ");
    QSpinBox *SBQupta = new QSpinBox(&dialog);
    form.addRow(Quota, SBQupta);
    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Process when OK button is clicked
    if (dialog.exec() == QDialog::Accepted) {
        // Do something here
        string Scid=LEcid->text().toStdString();
        string Scname=LECName->text().toStdString();
        float Scredits=LECredits->text().toFloat();
        int  Squota=SBQupta->value();

        bool isSuccess;
        string info;
        Manager M("null","null","null","null");
        std::tie(isSuccess,info,M)=Manager::LoadFromDB(ui->label_3->text().toStdString());
        assert(isSuccess);
        Course C(Scid,Scname,M.getIName(),Scredits,Squota);
        if(C.insert2DB())
        {
            QMessageBox::information(this,"提示","添加成功");
            updateCourseTable();
        }
        else
            QMessageBox::warning(this,"警告","添加失败");
    }
}

void Course_login::on_pushButton_3_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("User input:"));
    // 课程编号
    QString CID = QString("课程编号: ");
    QLineEdit *LEcid = new QLineEdit(&dialog);
    form.addRow(CID, LEcid);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    if (dialog.exec() == QDialog::Accepted) {
        bool isSuccess;
        string info;
        Course C("null","null","null",0.0,0);
        tie(isSuccess,info,C)=Course::LoadFromDB(LEcid->text().toStdString());
        if(isSuccess)
        {
            C.deleteFromDB();
            QMessageBox::information(this,"提示","删除成功");
            updateCourseTable();
        }
        else
            QMessageBox::warning(this,"警告","删除失败");
    }
}

void Course_login::on_save_clicked()
{
    saveCoursTable();
}

void Course_login::on_pushButton_4_clicked()
{
     updateCourseTable();
}
