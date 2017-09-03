## 正文

- BIT[(M)]

一个bit值类型。M代表bit值的长度，范围是1到64。M的缺省值为1。

- TINYINT[(M)] [UNSIGNED] [ZEROFILL]

一个非常小的整数。有符号的范围是[-128, 127]，无符号的范围是[0,255]

- BOOL, BOOLEAN

这个类型是`tinyint(1)`的同义词。0值代表false，非零值代表true：

```
mysql> SELECT IF(0, 'true', 'false');
+------------------------+
| IF(0, 'true', 'false') |
+------------------------+
| false                  |
+------------------------+

mysql> SELECT IF(1, 'true', 'false');
+------------------------+
| IF(1, 'true', 'false') |
+------------------------+
| true                   |
+------------------------+

mysql> SELECT IF(2, 'true', 'false');
+------------------------+
| IF(2, 'true', 'false') |
+------------------------+
| true                   |
+------------------------+
```

需要注意的是，`true`和`false`是`1`和`0`的别称，注意后边两个例子：

```
mysql> SELECT IF(0 = FALSE, 'true', 'false');
+--------------------------------+
| IF(0 = FALSE, 'true', 'false') |
+--------------------------------+
| true                           |
+--------------------------------+

mysql> SELECT IF(1 = TRUE, 'true', 'false');
+-------------------------------+
| IF(1 = TRUE, 'true', 'false') |
+-------------------------------+
| true                          |
+-------------------------------+

mysql> SELECT IF(2 = TRUE, 'true', 'false');
+-------------------------------+
| IF(2 = TRUE, 'true', 'false') |
+-------------------------------+
| false                         |
+-------------------------------+

mysql> SELECT IF(2 = FALSE, 'true', 'false');
+--------------------------------+
| IF(2 = FALSE, 'true', 'false') |
+--------------------------------+
| false                          |
+--------------------------------+
```

- SMALLINT[(M)] [UNSIGNED] [ZEROFILL]

有符号的范围是[-32768, 32767]，无符号的范围是[0, 65535]

- MEDIUMINT[(M)] [UNSIGNED] [ZEROFILL]

有符号的范围是[-8388608, 8388607]，无符号的范围是[0, 16777215]

- INT[(M)] [UNSIGNED] [ZEROFILL]

有符号的范围是[-2147483648, 2147483647]，无符号的范围是[0, 4294967295]

- INTEGER[(M)] [UNSIGNED] [ZEROFILL]

`int`的同义词

- BIGINT[(M)] [UNSIGNED] [ZEROFILL]

有符号的范围是[-9223372036854775808, 9223372036854775807]，无符号的范围是[0, 18446744073709551615]

`SERIAL`是`BIGINT UNSIGNED NOT NULL AUTO_INCREMENT UNIQUE`的别称。

- DECIMAL[(M[,D])] [UNSIGNED] [ZEROFILL]



- DEC[(M[,D])] [UNSIGNED] [ZEROFILL], NUMERIC[(M[,D])] [UNSIGNED] [ZEROFILL], FIXED[(M[,D])] [UNSIGNED] [ZEROFILL]
- FLOAT[(M,D)] [UNSIGNED] [ZEROFILL]
- DOUBLE[(M,D)] [UNSIGNED] [ZEROFILL]
- DOUBLE PRECISION[(M,D)] [UNSIGNED] [ZEROFILL], REAL[(M,D)] [UNSIGNED] [ZEROFILL]
- FLOAT(p) [UNSIGNED] [ZEROFILL]

## 参考

- [11.1.1 Numeric Type Overview](https://dev.mysql.com/doc/refman/8.0/en/numeric-type-overview.html)
