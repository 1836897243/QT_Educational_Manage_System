#include"Global.h"
#include"Education/institute.h"
void addSex2ComboBox(QComboBox*ComboBox)
{
    ComboBox->addItem("男");
    ComboBox->addItem("女");
}

void addInstitude2ComboBox(QComboBox*ComboBox)
{
    vector<Institute> institutes=Institute::getAllInstitute();
    for(unsigned i=0;i<institutes.size();i++)
    {
        ComboBox->addItem(QString::fromStdString(institutes[i].getIname()));
    }
}
