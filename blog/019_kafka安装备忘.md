## 正文

### 版本

当前kafka最新版本是0.11.0.0，2017年6月28日发布。下载页面是[http://kafka.apache.org/downloads](http://kafka.apache.org/downloads)。有两个可用的binary包，分别对应了Scala 2.11和Scala 2.12，推荐使用2.11。

### 安装

```
wget http://mirror.bit.edu.cn/apache/kafka/0.11.0.0/kafka_2.11-0.11.0.0.tgz

tar -zxvf kafka_2.11-0.11.0.0.tgz
cd kafka_2.11-0.11.0.0
```

首先启动ZooKeeper

```
bin/zookeeper-server-start.sh config/zookeeper.properties
```

然后启动kafka服务器

```
bin/kafka-server-start.sh config/server.properties
```

创建名为test1的topic

```
bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test1
```

列出topic列表

```
bin/kafka-topics.sh --list --zookeeper localhost:2181
```

发送消息到test1

```
bin/kafka-console-producer.sh --broker-list localhost:9092 --topic test1
```

从test1接收消息

```
bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test1 --from-beginning
```

