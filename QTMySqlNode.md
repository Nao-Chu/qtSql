### MySql



* 打开数据库

  ```c++
  // 创建了一个SQLite数据库的默认连接
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  // ":memory:"建立在内存中的数据库,database.db表示创建/打开database.db文件
  db.setDatabaseName("database.db");
  if(!db.open())
  	return false;
  ```

  

* 写入数据库

  ```c++
  QSqlQuery query;
  //“primary key”表明该属性是主键，它不能为空，而且不能有重复的值；
  // name属性是varchar类型的，并且不大于20个字符
  query.exec("create table student (id int primary key, name vchar)");
  query.exec("insert into student values (0,'yafei0')");
  query.exec("insert into student values (1,'yafei1')");
  query.exec("insert into student values (2,'yafei2')");
  ```

  

* 查询数据库

  ```c++
  QSqlQuery query;
  // 查询出表中所有的内容
  query.exec("select * from student");
  while(query.next())
  {
      qDebug() << query.value(0).toInt()
      << query.value(1).toString();
  }
  /*
  seek(int n) ：query指向结果集的第n条记录；
  first() ：query指向结果集的第一条记录；
  last() ：query指向结果集的最后一条记录；
  next() ：query指向下一条记录，每执行一次该函数，便指向相邻的下一条记录；
  previous() ：query指向上一条记录，每执行一次该函数，便指向相邻的上一条记录；
  record() ：获得现在指向的记录；
  value(int n) ：获得属性的值。其中n表示你查询的第n个属性，比方上面我们使用“select * from student”就相当于“select id, name from student”，那么value(0)返回id属性的值，value(1)返回name属性的值。该函数返回QVariant类型的数据，关于该类型与其他类型的对应关系，可以在帮助中查看QVariant。
  at() ：获得现在query指向的记录在结果集中的编号。
  */
  
  // 查询表中的某一条内容
  query.exec(QString("select name from student where id =%1").arg(id));
  query.next();
  QString name = query.value(0).toString();
  // 查询表中的某一条内容 写法2：
  QSqlQuery query;
  // 使用:id,:name 或则 ？,？ 
  query.prepare("insert into student (id, name) ""values (:id, :name)");
  // bindValue 指定添加
  // addBindValue 按prepare顺序添加
  query.bindValue(0, 5);
  query.bindValue(1, "sixth");
  //query.addBindValue(5);
  //query.addBindValue("sixth");
  query.exec();
  query.exec("select * from student");
  query.last();
  int id = query.value(0).toInt();
  QString name = query.value(1).toString();
  ```

  

* 查询模型

  ```c++
  QSqlQueryModel *model = new QSqlQueryModel;
  // 函数执行了SQL语句“("select * fromstudent");”
  model->setQuery("select * from student");
  model->setHeaderData(0, Qt::Horizontal, tr("id"));
  model->setHeaderData(1, Qt::Horizontal, tr("name"));
  
  QTableView *view = new QTableView;
  view->setModel(model);
  view->show();
  
  // 常用操作
  //获得列数
  int column= model->columnCount(); 
  // 获得行数
  int row = model->rowCount();    
  //获得一条记录
  QSqlRecord record = model->record(1);
  //获得一条记录的一个属性的值
  QModelIndex index = model->index(1,1);
  qDebug() << "column numis:" << column << endl
          << "row num is:" << row << endl
          <<"the second record is:" << record << endl
          << "the data of index(1,1) is:"<< index.data();
  
  // 写入数据
  QSqlQuery query = model->query();
  query.exec("insert into student values (13,'yafei13')");
  ```

  