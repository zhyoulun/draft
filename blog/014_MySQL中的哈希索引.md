## 正文

哈希索引（hash index）基于哈希表实现，只有精确匹配索引所有列的查询才能有效。对于每一行数据，存储引擎都会对所有的索引列计算一个哈希码，哈希码是一个较小的值，并且不同的键值的行计算出来的哈希码也不一样。哈希索引将所有的哈希码存储在索引中，同时再哈希表中保存指向每个数据行的指针。

在MySQL中，只有Memory引擎显式支持哈希索引。这也是Memory引擎表的默认索引类型。Memory引擎同时也支持B-Tree索引。值得一提的是，Memory引擎是支持非唯一哈希索引的，这在数据库世界里面是比较与众不同的。如果多个列的哈希值相同，索引会以链表的方式存放多个记录指针到同一个哈希条目中。

下面来看一个例子：

```
create table testhash(
    fname varchar(50) not null,
    lname varchar(50) not null,
    key using hash(fname)
)engine=memory;
```

表中包含如下数据：

![](http://mdimg.fabuler.cn/1707/p103.png)

假设索引使用假象的哈希函数f()，它返回下面的值：

![](http://mdimg.fabuler.cn/1707/p104.png)

则哈希索引的数据结构如下：

![](http://mdimg.fabuler.cn/1707/p105.png)

注意每个槽的编号是顺序的，但是数据行不是。现在来看如下查询：

```
select lname from testhash where fname='Peter';
```

MySQL先计算'Peter'的哈希值，并使用该值寻找对应的记录指针。因为f('Peter')=8784，所以MySQL在索引中查找8784，可以找到指向第3行的指针，最后一步是比较第三行的值是否为'Peter'，以确保就是要找的行。

因为索引自身只需要存储对应的哈希值，所以索引的结构十分紧凑，这也让哈希索引查找的速度非常快。

## 哈希索引的限制

- 哈希索引只包含哈希值和行指针，而不存储字段值，所以不能使用索引中的值来避免读取行。不过，访问内存中的行的速度很快，所以大部分情况下这一点对性能的影响并不明显。
- 哈希索引并不是按照索引值顺序存储的，所以也就无法用于排序。
- 哈希索引也不支持部分索引列匹配查找，因为哈希索引始终是使用索引列的全部内容来计算哈希值的。例如，在数据列（A，B）上建立哈希索引，如果查询只有数据列A，则无法使用该索引。
- 哈希索引只支持等值比较查询，包括=、in、<=>（注意<>和<=>是不同的操作）。也不支持任何范围查询，例如where Price>100。
- 访问哈希索引的数据非常快，除非有很多哈希冲突（不同的索引列值却有相同的哈希值）。当出现哈希冲突的时候，存储引擎必须遍历链表中所有的行指针，逐行进行比较，直到找到所有符合条件的行。
- 如果哈希冲突很多的话，一些索引维护操作的代价也会很高。例如，如果在某个选择性很低（哈希冲突很多）的列上建立哈希索引，那么当从表中删除一行时，存储引擎需要遍历对应哈希值的链表中的每一行，找到并删除对应行的引用，冲突越多，代价越大。

## 创建自定义哈希索引

如果存储引擎不支持哈希索引，则可以模拟像InnoDB一样创建哈希索引，这可以享受一些哈希索引的便利，例如只需要很小的索引就可以为超长的键创建索引。

思路很简单：在B-Tree的基础上创建一个伪哈希索引。这和真正的哈希索引不是一回事，因为还是使用B-Tree进行查找，但是它使用哈希值而不是键本身进行索引查找。你需要做的就是在查询where字句中手动指定使用哈希函数。

下面是一个例子，例如需要存储大量的URL，并需要根据URL进行搜索查找。如果使用B-Tree来存储URL，存储的内容就会非常大，因为URL本身就很长。正常情况下，会儿有如下查询：

```
select id from url where url='http://www.mysql.com';
```

若删除原来URL列上的索引，而新增一个被索引的url_crc列，使用CRC32做哈希，就可以使用下面的方式查询：

```
select id from url where url='http://www.mysql.com' and url_crc=crc32('http://www.mysql.com');
```

这样做的性能会非常高，因为MySQL优化器会使用这个选择性很高而体积很小的基于url_crc列的索引来完成查找（在上边的例子中，索引值是1560514994）。即使有多个记录有相同的索引值，查找仍然很快，只需要根据哈希值做快速的整数比较就能找到索引条目，然后一一比较返回对应的行。另外一种方式就是对完整的URL字符串做索引，那样会非常慢。

这样实现的缺陷是需要维护哈希值。可以手动维护，也可以使用触发器实现。下面的案例演示了触发器如何在插入和更新时维护url_crc列。首先创建如下表：

```
create table pseudohash(
    id int unsigned not null auto_increment,
    url varchar(255) not null,
    url_crc int unsigned not null default 0,
    primary key(id)
);
```

然后创建触发器。先临时修改一下语句分隔符，这样就可以在触发器定义中使用分好：

```
delimiter //
create trigger pseudohash_crc_ins before insert on pseudohash for each row begin set new.url_crc=crc32(new.url);
end;
//

create trigger pseudohash_crc_ins before update on pseudohash for each row begin set new.url_crc=crc32(new.url);
end;
//

delimiter;
```

剩下的工作就是验证一下触发器如何维护哈希索引：

![](http://mdimg.fabuler.cn/1707/p106.png)

如果采用这种方式，记住不要使用sha1()和md5()作为哈希函数。因为这两个函数计算出来的哈希值是非常长的字符串，会浪费大量控件，比较时也比较慢。sha1()和md5()是强加密函数，设计目标是最大限度消除冲突，但这里并不需要这样高的要求。简单哈希函数的冲突在一个可以接受的范围，同时又能够提供更好的性能。

如果数据表非常大，crc32()会出现大量的冲突，则可以考虑自己去实现一个简单的64位哈希函数。这个自定义函数要返回整数，而不是字符串。一个简单的办法可以使用md5()函数返回值的一部分来作为自定义哈希函数。这可能比自己写一个哈希算法的性能要查（参考第7章），不过这样实现最简单：

```
select conv(right(md5('http://www.mysql/'),16),16,10) as hash64;
```

![](http://mdimg.fabuler.cn/1707/p107.png)

## 处理哈希冲突。当使用哈希索引进行查询的时候，必须在where子句中包含常量值：

```
select id from url where url_crc=crc32('http://www.mysql.com') and url='http://www.mysql.com';
```

一旦出现哈希冲突，另一个字符串的哈希值也恰好是1560514994，则下面的查询时无法正确工作的。

```
select id from url where url_crc=crc32('http://www.mysql.com');
```

因为所谓的“生日北仑”，出现哈希冲突的概率的增长速度可能比想象的要快得多。crc32()返回的是32位的整数，当索引有93000条记录时，出现冲突的概率是1%。

```
select word,crc from words where crc=crc32('gnu');
```

![](http://mdimg.fabuler.cn/1707/p108.png)

正确的写法是：

```
select word,crc from words where crc=crc32('gnu') and word='gnu';
```

![](http://mdimg.fabuler.cn/1707/p109.png)

要避免冲突问题，必须在where条件中待入哈希值和对应列值。如果不是想查询具体的值，例如只是统计记录数（不精确的），则可以不带入列值，直接用crc32()的哈希值查询即可。还可以使用如fnv64()函数作为哈希函数，这是移植自percona server的函数。可以以插件的方式在任何mysql版本中使用，哈希值是64位，速度快，且冲突比crc32少很多。

## 参考

- 来自《高性能MySQL》