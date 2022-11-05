/********************************************************************************
** Form generated from reading UI file 'waisong.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAISONG_H
#define UI_WAISONG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_waisong
{
public:
    QLabel *label;
    QDateEdit *startDate;
    QLabel *label_2;
    QDateEdit *endDate;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QPushButton *dateBtn;
    QPushButton *sglBtn;
    QTableView *tableView;
    QLabel *label_4;
    QLineEdit *sglEdit;
    QLabel *label_5;
    QLabel *numlabel;
    QLabel *label_7;
    QLabel *label_6;
    QLineEdit *nameEdit;

    void setupUi(QDialog *waisong)
    {
        if (waisong->objectName().isEmpty())
            waisong->setObjectName(QString::fromUtf8("waisong"));
        waisong->resize(1000, 800);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        waisong->setWindowIcon(icon);
        label = new QLabel(waisong);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 30, 41, 21));
        startDate = new QDateEdit(waisong);
        startDate->setObjectName(QString::fromUtf8("startDate"));
        startDate->setGeometry(QRect(100, 30, 110, 22));
        label_2 = new QLabel(waisong);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 30, 31, 16));
        endDate = new QDateEdit(waisong);
        endDate->setObjectName(QString::fromUtf8("endDate"));
        endDate->setGeometry(QRect(240, 30, 110, 22));
        label_3 = new QLabel(waisong);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 70, 31, 16));
        lineEdit = new QLineEdit(waisong);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 70, 181, 20));
        dateBtn = new QPushButton(waisong);
        dateBtn->setObjectName(QString::fromUtf8("dateBtn"));
        dateBtn->setGeometry(QRect(660, 30, 75, 23));
        dateBtn->setAutoDefault(false);
        sglBtn = new QPushButton(waisong);
        sglBtn->setObjectName(QString::fromUtf8("sglBtn"));
        sglBtn->setGeometry(QRect(660, 70, 75, 23));
        sglBtn->setAutoDefault(false);
        tableView = new QTableView(waisong);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(50, 150, 900, 600));
        label_4 = new QLabel(waisong);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(360, 30, 54, 12));
        sglEdit = new QLineEdit(waisong);
        sglEdit->setObjectName(QString::fromUtf8("sglEdit"));
        sglEdit->setGeometry(QRect(390, 30, 113, 20));
        label_5 = new QLabel(waisong);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(300, 70, 81, 16));
        numlabel = new QLabel(waisong);
        numlabel->setObjectName(QString::fromUtf8("numlabel"));
        numlabel->setGeometry(QRect(380, 70, 31, 16));
        label_7 = new QLabel(waisong);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(400, 70, 54, 12));
        label_6 = new QLabel(waisong);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(510, 30, 41, 16));
        nameEdit = new QLineEdit(waisong);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setGeometry(QRect(540, 30, 91, 20));

        retranslateUi(waisong);

        QMetaObject::connectSlotsByName(waisong);
    } // setupUi

    void retranslateUi(QDialog *waisong)
    {
        waisong->setWindowTitle(QCoreApplication::translate("waisong", "waisong", nullptr));
        label->setText(QCoreApplication::translate("waisong", "\346\227\245\346\234\237", nullptr));
        label_2->setText(QCoreApplication::translate("waisong", " --", nullptr));
        label_3->setText(QCoreApplication::translate("waisong", "\346\235\241\347\240\201", nullptr));
        dateBtn->setText(QCoreApplication::translate("waisong", "\346\237\245\350\257\242", nullptr));
        sglBtn->setText(QCoreApplication::translate("waisong", "\346\240\207\350\256\260", nullptr));
        label_4->setText(QCoreApplication::translate("waisong", "\346\235\241\347\240\201", nullptr));
        label_5->setText(QCoreApplication::translate("waisong", "\345\267\262\346\240\270\345\257\271\346\240\267\346\234\254\346\225\260", nullptr));
        numlabel->setText(QString());
        label_7->setText(QCoreApplication::translate("waisong", "\344\270\252", nullptr));
        label_6->setText(QCoreApplication::translate("waisong", "\345\247\223\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class waisong: public Ui_waisong {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAISONG_H
