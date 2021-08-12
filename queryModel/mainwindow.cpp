#include "mainwindow.h"
#include "mysqlquerymodel.h"
#include "ui_mainwindow.h"

#include <QtSql/QSqlQueryModel>
#include <QTableView>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QModelIndex>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setHeaderData(0, Qt::Horizontal, tr("id"));
    model->setHeaderData(1, Qt::Horizontal, tr("name"));
    QTableView *view = new QTableView;
    view->setModel(model);


    int column= model->columnCount(); //获得列数
    int row = model->rowCount();    // 获得行数
    QSqlRecord record = model->record(1); //获得一条记录
    QModelIndex index = model->index(1,1);   //获得一条记录的一个属性的值
    qDebug() << "column numis:" << column << endl
            << "row num is:" << row << endl
            <<"the second record is:" << record << endl
            << "the data of index(1,1) is:"<< index.data();

    QSqlQuery query = model->query();
    query.exec("insert into student values (13,'yafei13')");
    model->setQuery("select * from student");
    view->show();


    MySqlQueryModel *myModel = new MySqlQueryModel();
    myModel->setQuery("select * from student");
    myModel->setHeaderData(0, Qt::Horizontal, tr("id"));
    myModel->setHeaderData(1, Qt::Horizontal, tr("name"));
    QTableView *view1 = new QTableView;
    view1->setWindowTitle("mySqlQueryModel"); //修改窗口标题
    view1->setModel(myModel);
    view1->show();
}
