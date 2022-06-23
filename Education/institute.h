#ifndef INSTITUTE_H
#define INSTITUTE_H
#include<string>
#include<vector>
using namespace std;


class Institute
{
public:
    static tuple<bool,string,Institute> LoadFromDB(string Iname);//从数据库中加载名称为Iname的学院信息，若是成功返回{ture,学院信息}，失败返回{false,xxx};
    static vector<Institute> getAllInstitute();//从数据库得到所有学院名称
    bool insert2DB();//将学院信息插入数据库中
public:
    Institute(string iname,string building,float budget)
        :IName(iname),Building(building),Budget(budget)
    {}
    string getIname();
    string getBuilding();
    float getBudget();
    void setBuilding(string building);
    void setBudget(float budget);
private:
    string IName;
    string Building;
    float Budget;

};

#endif // INSTITUTE_H
