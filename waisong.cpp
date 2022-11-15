#include "waisong.h"
#include "ui_waisong.h"

#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include<QSqlError>
#include <QFile>
#include <QFileDevice>
#include <QDir>
#include <QXmlStreamWriter>

waisong::waisong(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::waisong)
{
   // ui->setupUi(this);
   // this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);  //禁用最大化窗口
   //this->setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小
   //this->setWindowTitle(u8"外送样本查询 v1.0");

    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    current_date_time =QDate::currentDate();
    current_date =current_date_time.toString("yyyy-MM-dd");

    model = new QStandardItemModel();


    QString path3=QDir::currentPath();
    text1 = path3+"/config/db.ini";




   bool sqlflag= sqlConnection();
   qDebug()<<sqlflag;

   if(sqlflag)
   {
        ui->setupUi(this);
        ui->startDate->setDate(current_date_time);
        ui->startDate->setCalendarPopup(true);

        ui->endDate->setDate(current_date_time);
        ui->endDate->setCalendarPopup(true);
        ui->numlabel->setText(QString::number(num));

    }

    //db.close();
}

waisong::~waisong()
{
    db.close();
    delete ui;
}

bool waisong::sqlConnection()
{

    configIniRead = new QSettings(text1, QSettings::IniFormat);
       //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
    QString HostName = configIniRead->value("ip").toString();
    QString DatabaseName= configIniRead->value("database").toString();
    QString UserName = configIniRead->value("username").toString();
    QString Password = configIniRead->value("password").toString();
            deptID1  = configIniRead->value("deptID1").toString();
            deptID2  = configIniRead->value("deptID2").toString();

    if(HostName=="" || UserName=="" || Password==""){
        QMessageBox::warning(this,"警告!","数据库信息错误，请检查!", QMessageBox::Yes);
        this->show();
        return false;
    }else {

        qDebug()<<HostName<<DatabaseName<<UserName<<Password;

        if(QSqlDatabase::contains("qt_sql_default_connection"))
        {
             db = QSqlDatabase::database("qt_sql_default_connection");
        }
        else
        {
              db = QSqlDatabase::addDatabase("QODBC");

              //qDebug()<<db.isValid();//检测驱动是否可用
        }


        db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                                 "SERVER=%1;"
                                 "DATABASE=%2;"
                                 "UID=%3;"
                                 "PWD=%4;")
                       .arg(HostName)
                       .arg(DatabaseName)
                       .arg(UserName)
                       .arg(Password));
        if(!db.open())
        {
            QMessageBox::critical(0, QObject::tr("Error"),
                                                 QObject::tr("The database reported an error: %1").arg(db.lastError().text()));
            return false;
        }
        //在Qt数据库连接后，运行"SET NAMES 'UTF8'"语句或"SET NAMES 'GBK'"。
        else{
            db.open();
        }
    }

    db.exec("SET NAMES 'utf8'");

    return true;
}

void waisong::selectView()
{
    model->clear();

    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,u8"条码");
    model->setHeaderData(1,Qt::Horizontal,u8"姓名");
    model->setHeaderData(2,Qt::Horizontal,u8"性别");
    model->setHeaderData(3,Qt::Horizontal,u8"年龄");
    model->setHeaderData(4,Qt::Horizontal,u8"体检时间");
    model->setHeaderData(5,Qt::Horizontal,u8"外送项目");

    ui->tableView->setSortingEnabled(true);

    ui->tableView->setModel(model);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    //设置列宽不可变
  /*  ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(5,QHeaderView::Fixed);*/
    ui->tableView->setColumnWidth(0,120);
    ui->tableView->setColumnWidth(1,70);
    ui->tableView->setColumnWidth(2,40);
    ui->tableView->setColumnWidth(3,40);
    ui->tableView->setColumnWidth(4,180);
    ui->tableView->setColumnWidth(5,400);

//    for(int i = 0; i < total; i++)
//     {
//        model->setItem(i,0,new QStandardItem(Data[i][0]));
//        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
//        model->setItem(i,1,new QStandardItem(Data[i][1]));
//        model->item(i,1)->setTextAlignment(Qt::AlignCenter);
//        model->setItem(i,2,new QStandardItem(Data[i][2]));
//        model->item(i,2)->setTextAlignment(Qt::AlignCenter);
//        model->setItem(i,3,new QStandardItem(Data[i][3]));
//        model->item(i,3)->setTextAlignment(Qt::AlignCenter);
//        model->setItem(i,4,new QStandardItem(Data[i][4]));
//        model->item(i,4)->setTextAlignment(Qt::AlignCenter);
//        model->setItem(i,5,new QStandardItem(Data[i][5]));
//        model->item(i,5)->setTextAlignment(Qt::AlignCenter);
//    }

    for(int i=0;i<jsonsz.size();i++){
        QJsonValue val=jsonsz[i];
       /* qDebug()<<val.toObject().value("barcode").toString()
        * <<val.toObject().value("name").toString()
        * <<val.toObject().value("sex").toString()
         <<val.toObject().value("age").toString()
          <<val.toObject().value("sampletime").toString()
         <<val.toObject().value("descr").toString();*/

        model->setItem(i,0,new QStandardItem(val.toObject().value("barcode").toString()));
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,1,new QStandardItem(val.toObject().value("name").toString()));
        model->item(i,1)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,2,new QStandardItem(val.toObject().value("sex").toString()));
        model->item(i,2)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,3,new QStandardItem(val.toObject().value("age").toString()));
        model->item(i,3)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,4,new QStandardItem(val.toObject().value("sampletime").toString()));
        model->item(i,4)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,5,new QStandardItem(val.toObject().value("descr").toString()));
        model->item(i,5)->setTextAlignment(Qt::AlignCenter);
    }


}


void waisong::on_dateBtn_clicked()
{
    num =0;
    ui->numlabel->setText("0");

    QString sglid="";
    sglid=ui->sglEdit->text();
    ui->sglEdit->clear();

    QString sglname="";
    sglname=ui->nameEdit->text();
    ui->nameEdit->clear();

    start_date_time=ui->startDate->date();
    end_date_time =ui->endDate->date();

    startDate =start_date_time.toString("yyyy-MM-dd");
    endDate =end_date_time.addDays(1).toString("yyyy-MM-dd");


    int size =jsonsz.size();
    for(int i=0;i<size;i++)
    {
        jsonsz.removeFirst();
    }

   QString sql;

   //聊城
   sql="SELECT distinct(BARCODE),PNAME, PSEX ,PAGE , CONVERT(VARCHAR(23),SAMPLETIME,120) SAMPLETIME,   descr";
   //sql+="  = stuff((SELECT ',' + DESCR FROM v_adicon_sample t WHERE t.BARCODE = v_adicon_sample.BARCODE FOR xml path('')) , 1 , 1 , '') ";
   sql+="  FROM (SELECT DISTINCT a.SGLCHECKID AS BARCODE,  a.NAME AS PNAME, a.SEX AS PSEX, a.AGE AS PAGE, '岁' AS PAGETYPE, a.BIRTHDATE AS BIRTHDAY, f.BRIEFNAME AS DESCR,d.CHECKDATE AS SAMPLETIME";
   sql+=" FROM dbo.T_SINGLE_CHECKINFO AS a INNER JOIN dbo.T_SINGLE_CHECKMODULE AS d ON a.SGLCHECKID = d.SGLCHECKID INNER JOIN";
   sql+=" dbo.T_CHECKMODULE_OUTCHECK AS b ON d.CHECKMODULEID = b.CHECKMODULEID INNER JOIN dbo.T_CHECKMODULE_CHECKITEM AS c ON b.CHECKMODULEID = c.CHECKMODULEID INNER JOIN";
   sql+=" dbo.T_CHECKITEM AS e ON c.CHECKITEMID = e.CHECKITEMID INNER JOIN  dbo.T_CHECKMODULE AS f ON d.CHECKMODULEID = f.CHECKMODULEID";   
   //sql+="  WHERE (d.ISCHECKED = '1') AND (b.APPLYHOSPITAL IN ('2520001', '2520003')) AND (a.REGISTDEPT IN ('2520001', '2520003'))) adicon_sample";
   sql+="  WHERE (d.ISCHECKED = '1') AND (b.APPLYHOSPITAL IN (\'"+deptID1+"\', \'"+deptID2+"\')) AND (a.REGISTDEPT IN (\'"+deptID1+"\', \'"+deptID2+"\'))) adicon_sample";


   //东营
//   sql="SELECT distinct(BARCODE),PNAME, PSEX ,PAGE , CONVERT(VARCHAR(23),SAMPLETIME,120) SAMPLETIME,   descr  ";
//   //sql+="= stuff((SELECT ',' + DESCR FROM v_adicon_sample t WHERE t.BARCODE = v_adicon_sample.BARCODE FOR xml path('')) , 1 , 1 , '')";
//   sql+="  FROM  (SELECT DISTINCT a.SGLCHECKID AS BARCODE,  a.NAME AS PNAME, a.SEX AS PSEX, a.AGE AS PAGE, '岁' AS PAGETYPE, a.BIRTHDATE AS BIRTHDAY, f.BRIEFNAME AS DESCR,d.CHECKDATE AS SAMPLETIME";
//   sql+=" FROM dbo.T_SINGLE_CHECKINFO AS a INNER JOIN dbo.T_SINGLE_CHECKMODULE AS d ON a.SGLCHECKID = d.SGLCHECKID INNER JOIN";
//   sql+=" dbo.T_CHECKMODULE_OUTCHECK AS b ON d.CHECKMODULEID = b.CHECKMODULEID INNER JOIN";
//   sql+="  dbo.T_CHECKMODULE AS f ON d.CHECKMODULEID = f.CHECKMODULEID";
//   sql+="  WHERE (d.ISCHECKED = '1') AND (b.APPLYHOSPITAL IN ('2570001', '2570003')) AND (a.REGISTDEPT IN ('2570001', '2570003'))) adicon_sample";


   //广饶
//   sql="SELECT distinct(BARCODE),PNAME, PSEX ,PAGE , CONVERT(VARCHAR(23),SAMPLETIME,120) SAMPLETIME,   descr";
//   //sql+="  = stuff((SELECT ',' + DESCR FROM v_adicon_sample t WHERE t.BARCODE = v_adicon_sample.BARCODE FOR xml path('')) , 1 , 1 , '') ";
//   sql+="  FROM (SELECT DISTINCT a.SGLCHECKID AS BARCODE,  a.NAME AS PNAME, a.SEX AS PSEX, a.AGE AS PAGE, '岁' AS PAGETYPE, a.BIRTHDATE AS BIRTHDAY, f.BRIEFNAME AS DESCR,d.CHECKDATE AS SAMPLETIME";
//   sql+=" FROM dbo.T_SINGLE_CHECKINFO AS a INNER JOIN dbo.T_SINGLE_CHECKMODULE AS d ON a.SGLCHECKID = d.SGLCHECKID INNER JOIN";
//   sql+=" dbo.T_CHECKMODULE_OUTCHECK AS b ON d.CHECKMODULEID = b.CHECKMODULEID INNER JOIN dbo.T_CHECKMODULE_CHECKITEM AS c ON b.CHECKMODULEID = c.CHECKMODULEID INNER JOIN";
//   sql+=" dbo.T_CHECKITEM AS e ON c.CHECKITEMID = e.CHECKITEMID INNER JOIN  dbo.T_CHECKMODULE AS f ON d.CHECKMODULEID = f.CHECKMODULEID";
//   sql+="  WHERE (d.ISCHECKED = '1') AND (b.APPLYHOSPITAL IN ('0546001', '0546003')) AND (a.REGISTDEPT IN ('0546001', '0546003'))) adicon_sample";




   if(sglid.length()!=0&&sglname.length()==0)
      sql+=" where BARCODE =\'"+sglid+"\' and descr!='TCT' and descr!='HPV,TCT' and descr!='HPV'";
   else if(sglid.length()==0&&sglname.length()!=0)
       sql+=" where PNAME =\'"+sglname+"\' and descr!='TCT' and descr!='HPV,TCT' and descr!='HPV'";
   else
       sql+=" where SAMPLETIME>=\'"+startDate+"\' and SAMPLETIME<=\'"+endDate+"\' and descr!='TCT' and descr!='HPV,TCT' and descr!='HPV'";


    qDebug()<<sql;


   QSqlQuery query(db);
   query.exec(sql);

   total=query.numRowsAffected();

   //qDebug()<<total;

   for(int i=0;i<total;i++)
   {
         if(query.next())
           {
//             for(int j=0;j<MAXCOL;j++){
//              if(j==2){
//                  if(query.value(j)==1){
//                      Data[i][j]=u8"男";
//                  }else{
//                      Data[i][j]=u8"女";
//                  }

//              }else{
//                  Data[i][j]=query.value(j).toString();
//              }


//              //qDebug()<<Data[i][j];
//             }

//             int j=0;
//             while(j<jsonsz.size()){

//                 if(val.toObject().value("barcode").toString()!=query.value(0).toString())
//                     j++;
//                 else
//                     continue;
//             }

              QJsonValue val=jsonsz[jsonsz.size()-1];
              QJsonObject obj=jsonsz[jsonsz.size()-1].toObject();
             if(val.toObject().value("barcode").toString()!=query.value(0).toString()){
                 json.insert("barcode",query.value(0).toString());
                 json.insert("name",query.value(1).toString());
                 if(query.value(2)==1){
                     json.insert("sex",u8"男");
                 }else{
                     json.insert("sex",u8"女");
                 }
                 json.insert("age",query.value(3).toString());
                 json.insert("sampletime",query.value(4).toString());
                 json.insert("descr",query.value(5).toString());
                 json.insert("status","0");

                 jsonsz.append(json);//将json对象存入json数组中
             }else if(val.toObject().value("barcode").toString()==query.value(0).toString()){
                 QString strDescr=val.toObject().value("descr").toString();
                 strDescr +=","+query.value(5).toString();
                 //qDebug()<<strDescr;
                 obj["descr"]=strDescr;
                 jsonsz[jsonsz.size()-1]=obj;
             }

         }
   }
   selectView();
}

void waisong::on_sglBtn_clicked()
{
    QString sglid;

    sglid=ui->lineEdit->text();

    for(int i=0;i<total;i++)
    {
        if(sglid==model->item(i,0)->text()){
            for(int j=0;j<MAXCOL;j++)
               model->item(i,j)->setBackground(QBrush(QColor(255,0,0)));
        }
    }

    ui->lineEdit->clear();
}


void waisong::on_lineEdit_editingFinished()
{
    QString sglid;

    sglid=ui->lineEdit->text();

    if(ui->lineEdit->hasFocus())
    {
        for(int i=0;i<total;i++)
        {
            if(sglid==model->item(i,0)->text() ){
                 if(jsonsz[i].toObject().value("status").toString()=="0"){
                    num++;
                    ui->numlabel->setText(QString::number(num));

                    QJsonObject obj=jsonsz[i].toObject();
                    obj["status"]="1";
                    jsonsz[i]=obj;

                    qDebug()<<jsonsz[i].toObject().value("status").toString();

                    for(int j=0;j<MAXCOL;j++)
                    {
                       model->item(i,j)->setBackground(QBrush(QColor(255,0,0)));
                    }
                  }else if(jsonsz[i].toObject().value("status").toString()=="1"){
                     QMessageBox::critical(0, QObject::tr("提示"),
                                                          QObject::tr("该人已核对，请扫下一条码！"));
                 }

                 ui->lineEdit->clear();

                 return;

            }else if(i==total-1&&sglid!=model->item(i,0)->text()){
               // QMessageBox::critical(0, QObject::tr("Error"), QObject::tr("登记日期不在本日，请扫码查询"));
               QMessageBox::critical(0, QObject::tr("提示"),QObject::tr("登记日期不在本日，请扫码查询"));
            }
        }
    }


    ui->lineEdit->clear();
}
