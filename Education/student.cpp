#include "student.h"
#include<QSqlQuery>
#include<functional>
#include<QMessageBox>
#include<QVariant>
tuple<bool,string,Student> Student::LoadFromDB(string Sid)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select S_name,I_name,gender,birthday,phone,passwd from student where SID="+addQuotation(Sid);
    Student res(Sid,"null","null","null","null","null","null");
    string info="操作成功";
    if(!query.exec(QString::fromStdString(sql)))
    {
        info="数据库操作失败";
        return make_tuple(false,info,res);
    }
    if(!query.next())
    {
        info="不存在学号为"+Sid+"的学生";
        return make_tuple(false,info,res);
    }
    res.SName=query.value("S_name").toString().toStdString();
    res.IName=query.value("I_name").toString().toStdString();
    res.Gender=query.value("gender").toString().toStdString();
    res.Birthday=query.value("birthday").toString().toStdString();
    res.PhoneNum=query.value("phone").toString().toStdString();
    res.PassWd=query.value("passwd").toString().toStdString();
    return make_tuple(true,info,res);
}

bool Student::cancelCourse(string CourseId){
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="delete from takes where SID="+addQuotation(SID)+" and CID="+addQuotation(CourseId);;
    return query.exec(QString::fromStdString(sql));
}


vector<pair<string, int>> Student::getCoursesIdScore()
{
    vector<pair<string, int>>res;
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select*from takes where SID="+addQuotation(SID);
    if(!query.exec(QString::fromStdString(sql)))
    {
        QMessageBox::warning(NULL,"error","数据库操作失败");
        return res;
    }
    while(query.next())
    {
        res.push_back(make_pair(query.value("CID").toString().toStdString(),query.value("Grade").toInt()));
    }
    return res;
}
bool Student::takeCourse(string CourseId)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="insert into takes values("+addQuotation(SID)+","+addQuotation(CourseId)+",-1"+")";
    return query.exec(QString::fromStdString(sql));
}
bool Student::updata2DB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="update Student set S_name="+addQuotation(SName)+",I_name="+addQuotation(IName)+",gender="
            +addQuotation(Gender)+",birthday="+addQuotation(Birthday)+",phone="+addQuotation(PhoneNum)+",passwd="+addQuotation(PassWd)
            +"where SID="+addQuotation(SID);
     return query.exec(QString::fromStdString(sql));
}
bool Student::insert2DB()
{

    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="insert into Student values("+addQuotation(SID)+","+addQuotation(SName)+","+addQuotation(IName)+","
            +addQuotation(Gender)+","+addQuotation(Birthday)+","+addQuotation(PhoneNum)+","+addQuotation(PassWd)+")";
    return query.exec(QString::fromStdString(sql));
}

pair<bool,string> Student::Login(string sid, string passwd)
{
    bool isSuccess;
    string info;
    Student S(sid,"null","null","null","null","null","null");
    std::tie(isSuccess,info,S)=Student::LoadFromDB(sid);
    if(isSuccess)
    {
        if(S.PassWd==passwd)
            return make_pair(true,"登陆成功");
        else
            return make_pair(false,"密码错误");
    }
    else
        return make_pair(isSuccess,info);
}

pair<bool,string> Student::Rigister(Student Stu)
{
    bool isSuccess;
    string info;
    Student S(Stu.SID,"null","null","null","null","null","null");
    std::tie(isSuccess,info,S)=Student::LoadFromDB(Stu.SID);
    if(!isSuccess)
    {
        bool flag=Stu.insert2DB();
        if(flag)
            return make_pair(flag,"注册成功");
         else
            return make_pair(flag,"注册失败");
    }
    return make_pair(false,"已存在此账号");
}

bool Student::deleteFromDB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql=string("delete from Student ")+"where SID="+addQuotation(SID);
    return query.exec(QString::fromStdString(sql));
}

vector<Student> Student::getInstitudeStudents(string I_name)
{
    vector<Student>res;
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select SID from Student where I_name="+addQuotation(I_name);
    if(!query.exec(QString::fromStdString(sql)))
    {
        return res;
    }
    while(query.next())
    {
        bool isSuccess;
        string info;
        Student S("null","null","null","null","null","null","null");
        std::tie(isSuccess,info,S)=Student::LoadFromDB(query.value("SID").toString().toStdString());
        if(isSuccess)
            res.push_back(S);
    }
    return res;
}

void Student::setGender(string gender)
{
    Gender=gender;
}

void Student::setInstitute(string Iname)
{
    IName=Iname;
}

string Student::getSID()
{
    return SID;
}

string Student::getSName()
{
    return SName;
}

string Student::getINmae()
{
    return IName;
}

string Student::getGender()
{
    return Gender;
}

string Student::getBirthday()
{
    return Birthday;
}

string Student::getPhone()
{
    return PhoneNum;
}

string Student::getPasswd()
{
    return PassWd;
}

void Student::setBirthday(string birthday)
{
    Birthday = birthday;
}

void Student::setPhoneNum(string num)
{
    PhoneNum = num;
}
void Student::setPassWd(string passwd)
{
    PassWd = passwd;
}
