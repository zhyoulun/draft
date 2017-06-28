# MySQL查询时当offset较大时查询效率低

## 正文

数据库有中1千万条数据，如下所示：

```
mysql> select count(*) from score;
+----------+
| count(*) |
+----------+
| 10000000 |
+----------+
1 row in set (1.89 sec)

mysql> select * from score limit 0,5;
+----+------+
| id | num  |
+----+------+
|  1 |  695 |
|  2 | 3635 |
|  3 | 7766 |
|  4 | 4574 |
|  5 |  134 |
+----+------+
5 rows in set (0.00 sec)

mysql> select * from score order by id desc limit 0,5;
+----------+------+
| id       | num  |
+----------+------+
| 10000000 | 1230 |
|  9999999 | 4717 |
|  9999998 | 4719 |
|  9999997 | 3636 |
|  9999996 | 9254 |
+----------+------+
5 rows in set (0.00 sec)
```

做分页查询时，当offset较小时，查询效率很高；但是当offset较大时，查询效率很容易达到秒级。如下所示：

```
mysql> select * from score limit 0,5;
+----+------+
| id | num  |
+----+------+
|  1 |  695 |
|  2 | 3635 |
|  3 | 7766 |
|  4 | 4574 |
|  5 |  134 |
+----+------+
5 rows in set (0.00 sec)

mysql> select * from score limit 9000000,5;
+---------+------+
| id      | num  |
+---------+------+
| 9000001 |  507 |
| 9000002 | 5379 |
| 9000003 | 3095 |
| 9000004 | 1925 |
| 9000005 | 1308 |
+---------+------+
5 rows in set (2.68 sec)
```

网上能找到的优化方法主要有两种：

一种是，将`select * from score limit 9000000,5`改写为`select * from score as a inner join (select id from score limit 9000000,5) as b on a.id=b.id;`，先查询出偏移后的id，然后再取出对应的数据，个人感觉这种优化程度还是不够好。不过当表中的字段较多时，应该会有较大的提升。

第二种是，将`select * from score limit 9000000,5`改写为`select * from score where id>=9000000 limit 0,5;`，这样能做到和查询前5条数据基本一样的效果。但是不足是需要记录上一页最后一个id的值。

以上两种情况可以根据实际场景选择。

## 参考

- [在mysql中翻页是不是有比LIMIT OFFSET更好的选择](https://segmentfault.com/q/1010000000114645)
- [mysql分页offset过大，Sql优化经验](https://segmentfault.com/a/1190000005007706)
- [mysql查询时，offset过大影响性能的原因与优化方法](http://blog.csdn.net/fdipzone/article/details/72793837)
- [Why does MYSQL higher LIMIT offset slow the query down?](https://stackoverflow.com/questions/4481388/why-does-mysql-higher-limit-offset-slow-the-query-down)