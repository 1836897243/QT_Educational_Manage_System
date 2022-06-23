#include "teacher.h"
#include<QSqlQuery>
#include<functional>
#include<QMessageBox>
#include<QVariant>
tuple<bool,string,Teacher>Teacher::LoadFromDB(string TID)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select T_name,I_name,phone,salary,passwd from teacher where TID="+addQuotation(TID);
    Teacher res(TID,"null","null","null",0.0,"null");
    string info="操作成功";
    if(!query.exec(QString::fromStdString(sql)))
    {
        info="数据库操作失败";
        return make_tuple(false,info,res);
    }
    if(!query.next())
    {
        info="不存在教工号为"+TID+"的老师";
        return make_tuple(false,info,res);
    }
    res.TName=query.value("T_name").toString().toStdString();
    res.IName=query.value("I_name").toString().toStdString();
    res.PhoneNum=query.value("phone").toString().toStdString();
    res.Salary=query.value("salary").toString().toFloat();
    res.PassWd=query.value("passwd").toString().toStdString();
    return make_tuple(true,info,res);
}

bool Teacher::cancelCourse(string CourseID)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="delete from Teaches where TID="+addQuotation(TID)+" and CID="+addQuotation(CourseID);
    return query.exec(QString::fromStdString(sql));
}


vector<pair<string,teachTime>> Teacher::getCoursesId()
{
    vector<pair<string,teachTime>>res;
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select*from Teaches where TID="+addQuotation(TID);
    if(!query.exec(QString::fromStdString(sql)))
    {
        QMessageBox::warning(NULL,"error","数据库操作失败");
        return res;
    }
    while(query.next())
    {
        res.push_back(make_pair(query.value("CID").toString().toStdString(),query.value("TeachTime").toInt()));
    }
    return res;
}
bool Teacher::updata2DB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="update Teacher set T_name="+addQuotation(TName)+",I_name="+addQuotation(IName)+",phone="
            +addQuotation(PhoneNum)+",salary="+to_string(Salary)+",passwd="+addQuotation(PassWd)
            +"where TID="+addQuotation(TID);
     return query.exec(QString::fromStdString(sql));
}
bool Teacher::insert2DB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="insert into Teacher values("+addQuotation(TID)+","+addQuotation(TName)+","+addQuotation(IName)+","
            +addQuotation(PhoneNum)+","+to_string(Salary)+","+addQuotation(PassWd)+")";
    return query.exec(QString::fromStdString(sql));
}

bool Teacher::deleteFromDB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql=string("delete from Teacher ")+"where TID="+addQuotation(TID);
    return query.exec(QString::fromStdString(sql));
}

vector<Teacher> Teacher::getInstitudeTeacher(string I_name)
{
    vector<Teacher>res;
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select TID from Teacher where I_name="+addQuotation(I_name);
    if(!query.exec(QString::fromStdString(sql)))
    {
        return res;
    }
    while(query.next())
    {
        bool isSuccess;
        string info;
        Teacher T("null","null","null","null",0.0,"null");
        std::tie(isSuccess,info,T)=Teacher::LoadFromDB(query.value("TID").toString().toStdString());
        if(isSuccess)
            res.push_back(T);
    }
    return res;
}

bool Teacher::teachCourse(string CourseID,int time)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="insert into Teaches values("+addQuotation(TID)+","+addQuotation(CourseID)+","+to_string(time)+")";
    return query.exec(QString::fromStdString(sql));
}
pair<bool,string> Teacher::Login(string tid, string passwd)
{

    bool isSuccess;
    string info;
    Teacher T(tid,"null","null","null",0.0,"null");;
    std::tie(isSuccess,info,T)=Teacher::LoadFromDB(tid);
    if(isSuccess)
    {
        if(T.PassWd==passwd)
            return make_pair(true,"登陆成功");
        else
            return make_pair(false,"密码错误");
    }
    else
        return make_pair(isSuccess,info);
}
pair<bool,string> Teacher::Rigister(Teacher teacher)
{
    bool isSuccess;
    string info;
    Teacher T(teacher.TID,"null","null","null",0.0,"null");;
    std::tie(isSuccess,info,T)=Teacher::LoadFromDB(teacher.TID);
    if(!isSuccess)
    {
        bool flag=teacher.insert2DB();
        if(flag)
            return make_pair(flag,"注册成功");
         else
            return make_pair(flag,"注册失败");
    }
    return make_pair(false,"已存在此账号");
}
string Teacher::getTID()
{
    return TID;
}

string Teacher::getTName()
{
    return TName;
}

string Teacher::getIName()
{
    return IName;
}

string Teacher::getPhoneNum()
{
    return PhoneNum;
}

float Teacher::getSalary()
{
    return Salary;
}

string Teacher::getPasswd()
{
    return PassWd;
}

void Teacher::setInstitute(string I_name)
{
    IName=I_name;
}

void Teacher::setPhoneNum(string num)
{
    PhoneNum = num;
}
void Teacher::setSalary(float salary)
{
    Salary=salary;
}
void Teacher::setPassWd(string passwd)
{
    PassWd = passwd;
}
