## 正文

编辑`etc/hadoop/core-site.xml`：

```
<configuration>
    <property>
        <name>fs.defaultFS</name>
        <value>hdfs://localhost:9000</value>
    </property>
    <property>
        <name>hadoop.tmp.dir</name>
        <value>/home/s/data/hadoop/tmp</value>
    </property>
</configuration>
```

>修改hadoop.tmp.dir之后，最好重新格式化一下namenode

编辑`etc/hadoop/hdfs-site.xml`：

```
<configuration>
    <property>
        <name>dfs.replication</name>
        <value>1</value>
    </property>
</configuration>
```

配置`ssh localhost`免密码登录：

```
ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
chmod 0600 ~/.ssh/authorized_keys
```

格式化文件系统

```
bin/hdfs namenode -format
```

启动NameNode守护进程和DataNode守护进程：

```
sbin/start-dfs.sh
```

创建文件夹

```
bin/hadoop fs -mkdir /hello
bin/hadoop fs -ls /
```

创建文件

```
bin/hadoop fs -touchz /hello/a.txt
bin/hadoop fs -ls /hello
```

复制本地文件到hdfs

```
bin/hadoop fs -put etc/hadoop/core-site.xml /hello/core-site.xml
bin/hadoop fs -ls /hello
```

`jps`命令可以查看`NameNode`，`SecondaryNameNode`，`DataNode`是否正常启动。如果不正常，可以参考文本的参考。

## 问题

### Error:JAVA_HOME is not set and could not be found

编辑`etc/hadoop/hadoop-env.sh`：

```
export JAVA_HOME=${JAVA_HOME}

修改为jdk的真实路径

export JAVA_HOME=/home/s/software/jdk
```

## 参考

- [Hadoop: Setting up a Single Node Cluster.](http://hadoop.apache.org/docs/r2.7.4/hadoop-project-dist/hadoop-common/SingleCluster.html)
- [Error:JAVA_HOME is not set and could not be found 解决般的法](http://blog.csdn.net/dianzishijian/article/details/52094569)
- [Hadoop namenode无法启动](http://blog.csdn.net/bychjzh/article/details/7830508)
- [启动hadoop 2.6遇到的datanode启动不了](http://blog.csdn.net/zhangt85/article/details/42078347)