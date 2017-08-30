## 命令列表

- put

将一个或多个文件从本地文件系统中拷贝到目标文件系统。也支持从标准输入中读取输入写入目标文件系统。

```
hadoop fs -put localfile /user/hadoop/hadoopfile
hadoop fs -put -f localfile1 localfile2 /user/hadoop/hadoopdir
hadoop fs -put -d localfile hdfs://nn.example.com/hadoop/hadoopfile
hadoop fs -put - hdfs://nn.example.com/hadoop/hadoopfile 从标准输入中读取输入。
```

成功返回0，失败返回-1

- copyFromLocal

除了限定源路径是一个本地文件外，和put命令相似。

```
hadoop fs -copyFromLocal <localsrc> URI
```

- cat

将路径指定文件的内容输出到stdout。

```
hadoop fs -cat hdfs://nn1.example.com/file1 hdfs://nn2.example.com/file2
hadoop fs -cat file:///file3 /user/hadoop/file4
```

成功返回0，失败返回-1

- ls

```
fs -ls [-d] [-h] [-R] <args>
```

`-d`参数：文件夹作为纯文件列出

示例

```
[root@localhost ~]# hadoop fs -ls -d /hello/*
-rw-r--r--   1 root supergroup          0 2017-08-30 11:39 /hello/a.txt
-rw-r--r--   1 root supergroup        998 2017-08-30 11:40 /hello/core-site.xml
drwxr-xr-x   - root supergroup          0 2017-08-30 14:00 /hello/folder1
-rw-r--r--   1 root supergroup         33 2017-08-30 13:54 /hello/stdin.txt._COPYING_
[root@localhost ~]# hadoop fs -ls /hello/*
-rw-r--r--   1 root supergroup          0 2017-08-30 11:39 /hello/a.txt
-rw-r--r--   1 root supergroup        998 2017-08-30 11:40 /hello/core-site.xml
-rw-r--r--   1 root supergroup         33 2017-08-30 13:54 /hello/stdin.txt._COPYING_
```

`-h`：格式化文件大小

`-R`：递归列出子文件夹

```
[root@localhost ~]# hadoop fs -ls /
Found 1 items
drwxr-xr-x   - root supergroup          0 2017-08-30 14:00 /hello
[root@localhost ~]# hadoop fs -ls -R /
drwxr-xr-x   - root supergroup          0 2017-08-30 14:00 /hello
-rw-r--r--   1 root supergroup          0 2017-08-30 11:39 /hello/a.txt
-rw-r--r--   1 root supergroup        998 2017-08-30 11:40 /hello/core-site.xml
drwxr-xr-x   - root supergroup          0 2017-08-30 14:02 /hello/folder1
-rw-r--r--   1 root supergroup          0 2017-08-30 14:02 /hello/folder1/test.txt
-rw-r--r--   1 root supergroup         33 2017-08-30 13:54 /hello/stdin.txt._COPYING_
```

- touchz

创建一个空文件，如果文件已存在且大小不为0，则报错

- du

显示目录中所有文件的大小，或者当只指定一个文件时，显示此文件的大小。

```
hadoop fs -du [-s] [-h] URI [URI ...]
```

`-s`参数：聚合输出结果

```
[root@localhost ~]# hadoop fs -du /hello
0    /hello/a.txt
998  /hello/core-site.xml
0    /hello/folder1
33   /hello/stdin.txt._COPYING_
[root@localhost ~]# hadoop fs -du -s /hello
1031  /hello
```

`-h`参数：格式化文件大小

成功返回0，失败返回-1

- df

显示剩余空间

```
[root@localhost ~]# hadoop fs -df
Filesystem                     Size   Used     Available  Use%
hdfs://localhost:9000  422617952256  53248  383257497600    0%
[root@localhost ~]# hadoop fs -df -h
Filesystem                Size  Used  Available  Use%
hdfs://localhost:9000  393.6 G  52 K    356.9 G    0%
```

- mv

```
hadoop fs -mv URI [URI ...] <dest>
```

移动文件，当需要移动多个文件时目标需要是一个文件夹

```
hadoop fs -mv /user/hadoop/file1 /user/hadoop/file2
hadoop fs -mv hdfs://nn.example.com/file1 hdfs://nn.example.com/file2 hdfs://nn.example.com/file3 hdfs://nn.example.com/dir1
```

成功返回0，失败返回-1

- rm

```
hadoop fs -rm [-f] [-r |-R] [-skipTrash] URI [URI ...]
```

删除文件或文件夹

```
hadoop fs -rm hdfs://nn.example.com/file /user/hadoop/emptydir
```

`-r`或者`-R`参数：删除文件夹以及文件中的内容

`-f`参数：强制删除

`-skipTrash`参数：绕开垃圾回收站直接删除。当使用空间超额是非常有用。

- mkdir

创建文件夹

```
hadoop fs -mkdir [-p] <paths>
```

`-p`参数：创建路径中的父文件夹

```
hadoop fs -mkdir /user/hadoop/dir1 /user/hadoop/dir2
hadoop fs -mkdir hdfs://nn1.example.com/user/hadoop/dir hdfs://nn2.example.com/user/hadoop/dir
```

成功返回0，失败返回-1

- appendToFile
- checksum
- chgrp
- chmod
- chown
- copyToLocal
- count
- cp
- createSnapshot
- deleteSnapshot
- dus
- expunge
- find
- get
- getfacl
- getfattr
- getmerge
- help
- lsr
- moveFromLocal
- moveToLocal
- renameSnapshot
- rmdir
- rmr
- setfacl
- setfattr
- setrep
- stat
- tail
- test
- text
- truncate
- usage

## 参考

- [http://hadoop.apache.org/docs/r2.7.4/hadoop-project-dist/hadoop-common/FileSystemShell.html](http://hadoop.apache.org/docs/r2.7.4/hadoop-project-dist/hadoop-common/FileSystemShell.html)
- [Hadoop Shell命令](http://hadoop.apache.org/docs/r1.0.4/cn/hdfs_shell.html)
