## 创建一个只含有一个字段的表

```
create table table_name1
(
    id int
);
```

查看创建的表

```
mysql> show create table table_name1;
+-------------+-------------------------------------------------------------------------------------------------+
| Table       | Create Table                                                                                    |
+-------------+-------------------------------------------------------------------------------------------------+
| table_name1 | CREATE TABLE `table_name1` (
  `id` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 |
+-------------+-------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)
```

备注：MySQL默认使用InnoDB引擎，缺省的字符集是latin1。id字段的默认值是NULL。

## 创建带有auto_increment的表

```
create table table_name2
(
    id int auto_increment
);
```

执行这个会报如下错误

```
ERROR 1075 (42000): Incorrect table definition; there can be only one auto column and it must be defined as a key
```

指明在创建表的时候，只能有一个字段是自增的，并且必须被定义为一个key。所以使用下边的创建方式是可以的。

```
create table table_name2
(
    id int auto_increment,
    key(id)
);
```

```
mysql> show create table table_name2;
+-------------+-------------------------------------------------------------------------------------------------------------------------------+
| Table       | Create Table                                                                                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------------+
| table_name2 | CREATE TABLE `table_name2` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 |
+-------------+-------------------------------------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)
```

备注：id字段不能为空

插入一条记录

```
mysql> select * from table_name2;
Empty set (0.00 sec)

mysql> insert into table_name2 values();
Query OK, 1 row affected (0.00 sec)

mysql> select * from table_name2;
+----+
| id |
+----+
|  1 |
+----+
1 row in set (0.00 sec)
```

此时table_name2的属性会发生变化，会多一个AUTO_INCREMENT=2，用以标识下次id字段的自增值。

```
mysql> show create table table_name2;
+-------------+------------------------------------------------------------------------------------------------------------------------------------------------+
| Table       | Create Table                                                                                                                                   |
+-------------+------------------------------------------------------------------------------------------------------------------------------------------------+
| table_name2 | CREATE TABLE `table_name2` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1 |
+-------------+------------------------------------------------------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)
```

## 参考

- [MySQL中给表添加一个自动增长字段（auto_increment）](http://www.splaybow.com/post/mysql-table-add-column-auto-increment.html)
- [mysql的auto_increment详解](http://blog.csdn.net/fwkjdaghappy1/article/details/7663331)