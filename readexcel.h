#ifndef READEXCEL_H
#define READEXCEL_H

#include <QLabel>
#include <QObject>
#include <QVariant>
#include <objbase.h>
#include <ActiveQt/QAxObject>
#include <QString>
#include <QList>
#include<QFile>
#include<QFileInfo>
#include<QFileDialog>
#include<QCoreApplication>
#include<QTemporaryDir>

#include<QDebug>
#pragma execution_character_set("utf-8")

//需要wps才能打开噢
class readExcel:public QObject
{
    Q_OBJECT
public:
    readExcel(QObject *parent=0);
    QList<QList<QString> > readExcelData( QString url);
private:

    //建立excel相关参数
    QAxObject *excel;
    QAxObject *workBooks;
    QAxObject *workBook;
    QAxObject *workSheets;
    QAxObject *workSheet;
    QAxObject *usedRange;
    QList<QList<QString> > tempData;
    QLabel *qlabel2;
};

#endif // READEXCEL_H
