#include "course.h"
#include<QSqlQuery>
#include<functional>
#include<QMessageBox>
#include<QVariant>

tuple<bool,string,Course> Course::LoadFromDB(string CID)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select C_name,I_name,credits,quota from course where CID="+addQuotation(CID);
    Course res(CID,"null","null",0.0,0);
    string info="操作成功";
    if(!query.exec(QString::fromStdString(sql)))
    {
        info="数据库操作失败";
        return make_tuple(false,info,res);
    }
    if(!query.next())
    {
        info="不存在课程号为"+CID+"的课程";
        return make_tuple(false,info,res);
    }
    res.CName=query.value("C_name").toString().toStdString();
    res.IName=query.value("I_name").toString().toStdString();
    res.Credits=query.value("credits").toString().toFloat();
    res.Quota=query.value("quota").toString().toInt();
    return make_tuple(true,info,res);
}

vector<Course> Course::getInstituteCourses(string I_name)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql;
    if(I_name!=""){

        sql="select CID from Course where I_name="+addQuotation(I_name);
    }
    else{
        sql="select CID from Course";
    }
    query.exec(QString::fromStdString(sql));
    vector<Course>res;
    while(query.next())
    {
        bool isSucces=false;
        string info;
        Course C("null","null","null",0.0,0);
        std::tie(isSucces,info,C)=Course::LoadFromDB(query.value("CID").toString().toStdString());
        if(isSucces)
            res.push_back(C);
    }
    return res;
}

vector<pair<string, int>> Course::getStudentsIdScore()
{
    vector<pair<string, int>>res;
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select*from takes where CID="+addQuotation(CId);
    if(!query.exec(QString::fromStdString(sql)))
    {
        QMessageBox::warning(NULL,"error","数据库操作失败");
        return res;
    }
    while(query.next())
    {
        res.push_back(make_pair(query.value("SID").toString().toStdString(),query.value("Grade").toInt()));
    }
    return res;
}

pair<string,teachTime> Course::getTeacherIdTime()
{
    pair<string,teachTime> res=make_pair("null",-1);
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select*from Teaches where CID="+addQuotation(CId);
    if(!query.exec(QString::fromStdString(sql)))
    {
        QMessageBox::warning(NULL,"error","数据库操作失败");
        return res;
    }
    while(query.next())
    {
        res=make_pair(query.value("TID").toString().toStdString(),query.value("TeachTime").toInt());
    }
    return res;
}

bool Course::updataScore(string sid,int score)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="update takes set Grade="+to_string(score)+" where SID="+addQuotation(sid)+" and CID="
            +addQuotation(CId);
    return query.exec(QString::fromStdString(sql));
}

bool Course::updata2DB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="update Course set C_name="+addQuotation(CName)+",I_name="+addQuotation(IName)+",credits="
            +to_string(Credits)+",quota="+to_string(Quota)+" where CID="+addQuotation(CId);
     return query.exec(QString::fromStdString(sql));
}
bool Course::insert2DB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="insert into Course values("+addQuotation(CId)+","+addQuotation(CName)+","+addQuotation(IName)+","
            +to_string(Credits)+","+to_string(Quota)+")";
    return query.exec(QString::fromStdString(sql));
}
bool Course::deleteFromDB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql=string("delete from Course ")+"where CID="+addQuotation(CId);
    return query.exec(QString::fromStdString(sql));
}
int Course::getStuNumber()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql=string("select count(*) as number from takes ")+"where CID="+addQuotation(CId);
    query.exec(QString::fromStdString(sql));
    if(!query.next())
        return 0;
    return query.value("number").toInt();
}

int Course::getScore(string sid)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select Grade from takes where SID="+sid+" and CID="+CId;
    int res=-1;
    if(query.exec(QString::fromStdString(sql)))
    {
        if(query.next())
            res=query.value("Grade").toInt();
    }
    return res;
}

string Course::getCID()
{
    return CId;
}

string Course::getCName()
{
    return CName;
}

string Course::getIName()
{
    return IName;
}

float Course::getCredits()
{
    return Credits;
}

int Course::getQuota()
{
    return Quota;
}

void Course::setCName(string name)
{
    CName = name;
}

void Course::setCredits(float credits)
{
    Credits = credits;
}

void Course::setQuota(int quota)
{
    Quota = quota;
}
