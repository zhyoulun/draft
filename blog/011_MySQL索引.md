## 基本操作

### 创建

- 添加普通索引

```
alter table table_name add {index|key} index_name(column_name,...);
```

index和key二选一

- 添加唯一索引

```
alter table table_name unique [index|key] index_name(column_name,...);
```

index和key二选一，且可省略

- 添加主键

```
alter table table_name primary key(column_name);
```

在创建索引时，可以规定索引能否包含重复值。如果不包含，则索引应该创建为PRIMARY KEY或UNIQUE索引。对于单列惟一性索引，这保证单列不包含重复的值。对于多列惟一性索引，保证多个值的组合不重复。

PRIMARY KEY索引和UNIQUE索引非常类似。事实上，PRIMARY KEY索引仅是一个具有名称PRIMARY的UNIQUE索引。这表示一个表只能包含一个PRIMARY KEY，因为一个表中不可能具有两个同名的索引。

### 删除

- 删除一个索引

```
alter table table_name drop {index|key} index_name;
drop index index_name on table_name;
```

这两个语句是等价的，index和key二选一。

- 删除主键

```
alter table table_name drop primary key;
```

只在删除PRIMARY KEY索引时使用，因为一个表只可能有一个PRIMARY KEY索引，因此不需要指定索引名。如果没有创建PRIMARY KEY索引，但表具有一个或多个UNIQUE索引，则MySQL将删除第一个UNIQUE索引。

如果从表中删除了某列，则索引会受到影响。对于多列组合的索引，如果删除其中的某列，则该列也会从索引中删除。如果删除组成索引的所有列，则整个索引将被删除。

### 更新

在MySQL中并没有提供修改索引的直接指令，一般情况下，我们需要先删除掉原索引，再根据需要创建一个同名的索引，从而变相地实现修改索引操作。

### 查看

```
SHOW {INDEX | INDEXES | KEYS}
    {FROM | IN} table_name
    [{FROM | IN} db_name]
    [WHERE expr]
```

也可以使用`db_name.table_name`替代`table_name from db_name`

```
mysql> show create table score;
CREATE TABLE `score` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `num` int(11) DEFAULT NULL,
  `rank` int(10) unsigned DEFAULT NULL,
  KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10000001 DEFAULT CHARSET=utf8

mysql> show index from score \G;
*************************** 1. row ***************************
        Table: score
   Non_unique: 1
     Key_name: id
 Seq_in_index: 1
  Column_name: id
    Collation: A
  Cardinality: 9725945
     Sub_part: NULL
       Packed: NULL
         Null: 
   Index_type: BTREE
      Comment: 
Index_comment: 
1 row in set (0.00 sec)
```

| 名称 | 解释 |
|---|---|
| Table |  表的名称 |
|  Non_unique | 如果索引不能包括重复词，则为0。如果可以，则为1  |
| Key_name | 索引的名称 |
| Seq_in_index | 索引中的列序列号，从1开始 |
| Column_name | 列名称 |
| Collation | 列以什么方式存储在索引中。在MySQL中，有值‘A’（升序）或NULL（无分类） |
| Cardinality | 索引中唯一值的数目的估计值。通过运行ANALYZE TABLE或myisamchk -a可以更新。基数根据被存储为整数的统计数据来计数，所以即使对于小型表，该值也没有必要是精确的。基数越大，当进行联合时，MySQL使用该索引的机会就越大。 |
| Sub_part | 如果列只是被部分地编入索引，则为被编入索引的字符的数目。如果整列被编入索引，则为NULL。 |
| Packed | 指示关键字如何被压缩。如果没有被压缩，则为NULL。 |
| Null | 如果列含有NULL，则含有YES。如果没有，则该列含有NO。 |
| Index_type | 用过的索引方法（BTREE, FULLTEXT, HASH, RTREE） |
| Comment | Information about the index not described in its own column, such as disabled if the index is disabled. |
| Index_comment | Any comment provided for the index with a COMMENT attribute when the index was created. |


## 参考

- [MySQL索引的创建、删除和查看](http://www.cnblogs.com/tianhuilove/archive/2011/09/05/2167795.html)
- [MySQL中给表添加一个自动增长字段（auto_increment）](http://www.splaybow.com/post/mysql-table-add-column-auto-increment.html)
- [mysql中key 、primary key 、unique key 与index区别](http://zccst.iteye.com/blog/1697043)
- [Mysql中索引的 创建，查看，删除，修改](http://www.cnblogs.com/yeyublog/p/5898588.html)