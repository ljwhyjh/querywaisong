#include "waisong.h"

#include <QTextCodec>
#include <QDir>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBk"));

    QString path=QDir::currentPath();
    QString text = path+"/config/logo.jpg";


    waisong w;
    w.setWindowTitle(u8"外送样本查询v1.51 20221115");//20221102修改时间为采血登记时间
    w.setWindowIcon(QIcon(text));

    w.show();
    return a.exec();
}
