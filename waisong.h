#ifndef WAISONG_H
#define WAISONG_H

#pragma execution_character_set("utf-8")

#include <QDialog>

#include <QWidget>
#include <QDateTime>
#include <QString>
#include <QSettings>

#include <QSqlDatabase>
#include <QDate>
#include <QSqlQuery>

#include <QJsonArray>
#include <QJsonObject>

//#include <QDebug>
//#include <QMessageBox>
//#include<QSqlError>
//#include <QTime>

#include <QStandardItemModel>
#include <QHeaderView>


QT_BEGIN_NAMESPACE
namespace Ui { class waisong; }
QT_END_NAMESPACE

#define MAXROW 1000
#define MAXCOL 6

class waisong : public QDialog
{
    Q_OBJECT

public:
    waisong(QWidget *parent = nullptr);
    ~waisong();

    QSqlDatabase db;

    QSettings *configIniRead;
    QString text1;

private:

     bool sqlConnection();

     void selectView();

private slots:
    void on_dateBtn_clicked();

    void on_sglBtn_clicked();

   // void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

private:
    QDate current_date_time;
    QDate start_date_time;
    QDate end_date_time;


    QString current_date;
    QString startDate;
    QString endDate;
    QString deptID1,deptID2;
    int total;
    int num=0;

    QStandardItemModel  *model;
    //QString Data[MAXROW][MAXCOL];
    QJsonArray jsonsz;//定义一个json数组
    QJsonObject json;//定义一个json对



private:
    Ui::waisong *ui;
};
#endif // WAISONG_H
