#include "readexcel.h"

readExcel::readExcel(QObject *parent):QObject(parent)
{
}

 QList<QList<QString>> readExcel::readExcelData( QString  url)
{

    excel=new QAxObject();
    if (excel->setControl("Excel.Application"))         //微软
    {}
    else
    {
        excel->setControl("ket.Application");           //wps
    }
    excel->dynamicCall("SetVisible(bool)",false);
    excel->setProperty("DisplayAlerts",false);
    workBooks=excel->querySubObject("WorkBooks");
    //转化为绝对路径--方便了exe转移pc 但excel要跟随一起
    QString stpth;
    if(url.contains("\\",Qt::CaseSensitive)){
         stpth=url;
    }else
     stpth=QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + url);

    workBook=workBooks->querySubObject("Open(const QString&)",stpth);
    workSheets=workBook->querySubObject("WorkSheets");
    workSheet=workSheets->querySubObject("Item(int)",1);
    usedRange=workSheet->querySubObject("UsedRange");
    int iRow= usedRange->property("Row").toInt();
    int iCol=usedRange->property("Column").toInt();
    int intRow=usedRange->querySubObject("Rows")->property("Count").toInt();

   QVariant var = usedRange->dynamicCall("Value");
   QList<QList<QVariant> > excelList;
   QVariantList varRows=var.toList();
   const int rowCount=varRows.size();
   QVariantList rowData;
   for(int i=0;i<rowCount;i++)
   {
       rowData=varRows[i].toList();
       excelList.push_back(rowData);
   }

   for (int i=0;i<excelList.size();i++)
   {
       QList<QString> temp;
       for (int j=0;j<excelList[0].size();j++)
       {
          temp.append(excelList[i][j].toString());
       }

       tempData.append(temp);
        qDebug()<<temp;
   }

   workBook->dynamicCall("Close(Boolean)",false);
   excel->dynamicCall("Quit(void)");

   delete excel;
   return tempData;
}
