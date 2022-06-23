#ifndef GLOBAL_H
#define GLOBAL_H
#include<QWidget>
#include<QItemDelegate>
#include<QStandardItemModel>
#include<QTableWidgetItem>
#include<Education/student.h>
#include<QInputDialog>
#include<QMessageBox>
#include<vector>
#include<QSpinBox>
#include<QComboBox>
#include<QDialogButtonBox>
#include<QFormLayout>
#include<QDateEdit>
#include"Education/institute.h"
using namespace std;
class ReadOnlyDelegate: public QItemDelegate
{
public:
    ReadOnlyDelegate(QWidget *parent = NULL):QItemDelegate(parent)
    {}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
const QModelIndex &index) const override //final
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return NULL;
    }
};
class  IntDelegate :  public  QItemDelegate
{
    Q_OBJECT
public :
    IntDelegate(QObject *parent =NULL): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent,  const QStyleOptionViewItem &option,
         const  QModelIndex &index)  const
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        QSpinBox *editor =  new  QSpinBox(parent);
 //       editor->setMinimum(1);
        editor->setMaximum(10000000);
         return  editor;
    }
     void  setEditorData(QWidget *editor,  const  QModelIndex &index)  const
    {
         int  value = index.model()->data(index, Qt::EditRole).toInt();
        QSpinBox *spinBox =  static_cast <QSpinBox*>(editor);
        spinBox->setValue(value);
    }
     void  setModelData(QWidget *editor, QAbstractItemModel *model,
         const  QModelIndex &index)  const
    {
        QSpinBox *spinBox =  static_cast <QSpinBox*>(editor);
        spinBox->interpretText();
         int  value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
     void  updateEditorGeometry(QWidget *editor,
         const  QStyleOptionViewItem &option,  const  QModelIndex &index) const
    {
         Q_UNUSED(index)
        editor->setGeometry(option.rect);
    }
};

class  DateDelegate :  public  QItemDelegate
{
    Q_OBJECT
public :
    DateDelegate(QObject *parent =NULL): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent,  const QStyleOptionViewItem &option,
         const  QModelIndex &index)  const
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        QDateEdit *editor =  new  QDateEdit(parent);
 //       editor->setMinimum(1);
   //     editor->setMaximum(100);
         return  editor;
    }
     void  setEditorData(QWidget *editor,  const  QModelIndex &index)  const
    {
         QString  value = index.model()->data(index, Qt::EditRole).toString();
        QDateEdit *spinBox =  static_cast <QDateEdit*>(editor);
        spinBox->setDate(QDate::fromString(value));
    }
     void  setModelData(QWidget *editor, QAbstractItemModel *model,
         const  QModelIndex &index)  const
    {
        QDateEdit *spinBox =  static_cast <QDateEdit*>(editor);
        QString  value = spinBox->date().toString();
        model->setData(index, value, Qt::EditRole);
    }
     void  updateEditorGeometry(QWidget *editor,
         const  QStyleOptionViewItem &option,  const  QModelIndex &index) const
    {
         Q_UNUSED(index)
        editor->setGeometry(option.rect);
    }
};

class  SexDelegate :  public  QItemDelegate
{
    Q_OBJECT
public :
    SexDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent,  const QStyleOptionViewItem &option,
         const  QModelIndex &index)  const
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        QComboBox *editor =  new  QComboBox(parent);
        editor->addItem( "男" );
        editor->addItem( "女" );
         return  editor;
    }
     void  setEditorData(QWidget *editor,  const  QModelIndex &index)  const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox =  static_cast <QComboBox*>(editor);
         int  tindex = comboBox->findText(text);
        comboBox->setCurrentIndex(tindex);
    }
     void  setModelData(QWidget *editor, QAbstractItemModel *model,
         const  QModelIndex &index)  const
    {
        QComboBox *comboBox =  static_cast <QComboBox*>(editor);
        QString text = comboBox->currentText();
        model->setData(index, text, Qt::EditRole);
    }
     void  updateEditorGeometry(QWidget *editor,
         const  QStyleOptionViewItem &option,  const  QModelIndex &index) const
    {
         Q_UNUSED(index)
        editor->setGeometry(option.rect);
    }
};

class  CreditsDelegate:  public  QItemDelegate
{
    Q_OBJECT
public :
    CreditsDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent,  const QStyleOptionViewItem &option,
         const  QModelIndex &index)  const
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        QLineEdit *editor =  new  QLineEdit(parent);
        QRegExp regExp( "^(5|[0-4]?(\\.\\d{1,1})?)$" );//https://blog.csdn.net/gossiplee/article/details/73935771
        editor->setValidator( new  QRegExpValidator(regExp, parent));
         return  editor;
    }
     void  setEditorData(QWidget *editor,  const  QModelIndex &index)  const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
        lineEdit->setText(text);
    }
     void  setModelData(QWidget *editor, QAbstractItemModel *model,
         const  QModelIndex &index)  const
    {
        QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
        QString text = lineEdit->text();
        model->setData(index, text, Qt::EditRole);
    }
     void  updateEditorGeometry(QWidget *editor,
         const  QStyleOptionViewItem &option,  const  QModelIndex &index) const
    {
        Q_UNUSED(index)
        editor->setGeometry(option.rect);
    }
};

extern void addSex2ComboBox(QComboBox*ComboBox);

extern void addInstitude2ComboBox(QComboBox*ComboBox);
#endif // GLOBAL_H
