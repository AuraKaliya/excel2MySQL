#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QCheckBox>
#include <QList>
#include <QStringList>

#include <QDebug>
#include <QPainter>
#include <QPixmap>

#include "columbox.h"
#include "readexcel.h"


#pragma execution_character_set("utf-8")
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT


public:
    Widget(QWidget *parent = nullptr);

    void addColum(QString,QString,int idx);
    void setShowWidgetHeight(int h);
    void createTabel();
    void insertData();


    ~Widget();

private:
    readExcel *readDataExcel;

    QList<QList <QString> > excelInformation;

    //
    columBox* groupBox;

    QLabel* nameLabel;
    QLabel* typeLabel;

    QTextEdit* nameText;
    QTextEdit* typeText;

    QLabel* columCountLabel;

    QCheckBox*  cbDefault;
    QCheckBox*  cbPrime;
    QCheckBox*  cbOnly;
    QCheckBox*  cbNull;
    QCheckBox*  cbExtra;

    QList <QCheckBox *> checkBoxList;
    QTextEdit* defaultText;

    //



    QList<columBox*> columBoxList;

    QRect titleRect;

    Ui::Widget *ui;

private:
    void paintEvent(QPaintEvent *event);
private slots:
    void openExcel();
    void build();


};
#endif // WIDGET_H
