#include "Institute.h"
#include<QSqlQuery>
#include<functional>
#include<QMessageBox>
#include <QVariant>
tuple<bool,string,Institute> Institute::LoadFromDB(string name)
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select building,budget from Institute where I_name="+addQuotation(name);
    Institute res(name,"null",0.0);
    string info="操作成功";
    if(!query.exec(QString::fromStdString(sql)))
    {
        info="数据库操作失败";
        return make_tuple(false,info,res);
    }
    if(!query.next())
    {
        info="不存在名称为"+name+"的学院";
        return make_tuple(false,info,res);
    }
    res.setBuilding(query.value("building").toString().toStdString());
    res.setBudget(query.value("budget").toString().toFloat());
    return make_tuple(true,info,res);
}
vector<Institute> Institute::getAllInstitute()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="select I_name from Institute";
    query.exec(QString::fromStdString(sql));
    vector<Institute> res;
    while(query.next())
    {
        string iname=query.value("I_name").toString().toStdString();
        bool isSuccess;
        string info;
        Institute ins("null","null",0);
        tie(isSuccess,info,ins)=Institute::LoadFromDB(iname);
        if(isSuccess)
            res.push_back(ins);
    }
    return res;
}
bool Institute::insert2DB()
{
    function<string(string)>addQuotation=[](string str){return "\""+str+"\"";};
    QSqlQuery query;
    string sql="insert into Institute values("+addQuotation(IName)+","+addQuotation(Building)+","+to_string(Budget)+")";
    return query.exec(QString::fromStdString(sql));
}
string Institute::getIname()
{
    return IName;
}
string Institute::getBuilding()
{
    return Building;
}

void Institute::setBuilding(string building)
{
    Building = building;
}

float Institute::getBudget()
{
    return Budget;
}

void Institute::setBudget(float budget)
{
    Budget = budget;
}
