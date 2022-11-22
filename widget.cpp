#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    setWindowTitle("Aura's tool-Excel2MySQL");
    ui->setupUi(this);


    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    titleRect.setRect(160,60,300,50);

    connect(ui->openBtn,SIGNAL(clicked()),this,SLOT(openExcel()));
    connect(ui->workBtn,SIGNAL(clicked()),this,SLOT(build()));


    update();



}

void Widget::addColum(QString name, QString type,int idx)
{
    qDebug()<<"daozhele";
    columBox * groupBox=new columBox();
    groupBox->setParent(ui->scrollAreaWidgetContents);
    groupBox->setVisible(true);
    groupBox->setGeometry(5,idx*170+10,500,150);
    groupBox->getNameText()->setText(name);
    groupBox->getTypeText()->setText(type);
    if(groupBox->getTypeText()->toPlainText()=="int") groupBox->getTypeBox()->setCurrentIndex(1);
    else groupBox->getTypeBox()->setCurrentIndex(0);
    groupBox->getColumCountLabel()->setText(QString::number(idx+1));
    columBoxList<<groupBox;

}

void Widget::setShowWidgetHeight(int h)
{
    ui->scrollAreaWidgetContents->setMinimumHeight(h);
    ui->scrollAreaWidgetContents->setGeometry(0,0, ui->scrollAreaWidgetContents->width(), h);
}

void Widget::createTabel()
{

    QString createStr="create table if not exists "+ui->databaseName->toPlainText()+".`"+ui->tableNameText->toPlainText()+"`(\n";

    for(int i=0;i<columBoxList.size();i++)
    {
        QString tmpStr;
        tmpStr="\t`"+columBoxList[i]->getNameText()->toPlainText()+"` "
                +columBoxList[i]->getTypeText()->toPlainText()+" ";
        if(columBoxList[i]->checkBoxList[1]->isChecked()) tmpStr+=" NOT NULL "; else tmpStr+=" NULL ";
        if(columBoxList[i]->checkBoxList[2]->isChecked()) tmpStr+=" unique ";
        if(columBoxList[i]->checkBoxList[3]->isChecked()) tmpStr+= " AUTO_INCREMENT ";
        if(columBoxList[i]->checkBoxList[4]->isChecked()) tmpStr+="  DEFAULT '"+columBoxList[i]->getDefaultText()->toPlainText()+"' ";
        if(columBoxList[i]->checkBoxList[0]->isChecked()) tmpStr+="PRIMARY KEY";

        if(i<columBoxList.size()-1) tmpStr +=",\n";
        else tmpStr+="\n";
        createStr+=tmpStr;

    }

    createStr+=");";


    ui->tableEdit->setText(createStr);


}

void Widget::insertData()
{
    QString mStr="";
    for(int k=1;k<excelInformation.size();k++)
    {
        QString insertStr="insert into "+ui->tableNameText->toPlainText()+" (";
        for(int i=0;i<columBoxList.size();i++)
        {
            QString tmpStr=" ";
            tmpStr+=columBoxList[i]->getNameText()->toPlainText();
            if(i<columBoxList.size()-1)
            tmpStr+=", ";
            insertStr+=tmpStr;

        }
        insertStr+=") values( ";
        for(int i=0;i<columBoxList.size();i++)
        {
            bool isNum;
            QString tmpStr=" ";
            if(excelInformation[k][i].isNull()) tmpStr+="NULL";
            else if(columBoxList[i]->getTypeBox()->currentText()==QString("数值型")) tmpStr+=excelInformation[k][i];
            else {
                tmpStr+=QString("'"+excelInformation[k][i]+"'");
            }
           if(i<columBoxList.size()-1)
           tmpStr+=", ";
           insertStr+=tmpStr;
        }
        insertStr+=");\n";
        mStr+=insertStr;

    }

    ui->dataEdit->setText(mStr);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(titleRect,QPixmap(":/title.png"));
    painter.end();




}

void Widget::openExcel()
{
    qDebug()<<"启动了";
    for(int i=0;i<columBoxList.size();i++)
    {
        columBoxList[i]->setVisible(false);
    }
    columBoxList.clear();
    QStringList tmpStList=ui->readEdit->toPlainText().split(QRegExp("[ .]"));
    //if(tmpStList[tmpStList.size()-1]!="xls"||tmpStList[tmpStList.size()-1]!="xlsx") return;

    readDataExcel=new readExcel();
    excelInformation=readDataExcel->readExcelData(ui->readEdit->toPlainText());
    qDebug()<<excelInformation[0].size();
     //先设置窗体大小再进行分配
    setShowWidgetHeight(excelInformation[0].size()*170+20);

    for(int i=0;i<excelInformation[0].size();i++)
    {
        QString tmpTy;
        bool isNum;
        if(excelInformation[1][i].toDouble(&isNum)||excelInformation[1][i].toInt(&isNum)) tmpTy="int"; else tmpTy="text";
        addColum(excelInformation[0][i],tmpTy,i);

    }
}

void Widget::build()
{
    createTabel();
    insertData();
}

