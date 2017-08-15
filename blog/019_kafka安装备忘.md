## 正文

### 版本

当前kafka最新版本是0.11.0.0，2017年6月28日发布。下载页面是[http://kafka.apache.org/downloads](http://kafka.apache.org/downloads)。有两个可用的binary包，分别对应了Scala 2.11和Scala 2.12，推荐使用2.11。

### 安装

```
wget http://mirror.bit.edu.cn/apache/kafka/0.11.0.0/kafka_2.11-0.11.0.0.tgz

tar -zxvf kafka_2.11-0.11.0.0.tgz
cd kafka_2.11-0.11.0.0
```

首先启动ZooKeeper，如下命令会启动一个快捷的单节点ZooKeeper实例

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

> 除了通过手动创建topic，你也可以把你的broker配置成自动创建topic。

列出topic列表

```
bin/kafka-topics.sh --list --zookeeper localhost:2181
```

运行producer，发送消息到test1

```
bin/kafka-console-producer.sh --broker-list localhost:9092 --topic test1
```

运行consumer，从test1接收消息

```
bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test1 --from-beginning
```

> 在windows平台中执行bin/windows文件夹下对应的命令

### 启动一个多broker的集群

复制配置文件

```
cp config/server.properties config/server-1.properties
cp config/server.properties config/server-2.properties
```

修改配置文件内容

```
config/server-1.properties:
	broker.id=1
	listeners=PLAINTEXT://:9093
	log.dir=/tmp/kafka-logs-1
 
config/server-2.properties:
	broker.id=2
	listeners=PLAINTEXT://:9094
	log.dir=/tmp/kafka-logs-2
```

`broker.id`属性是集群中每一个节点的唯一和固定的名称。我们必须修改端口和log文件夹，因为我们是在同一台机器上运行。

在先前的基础上，再次运行这两个新的节点

```
bin/kafka-server-start.sh config/server-1.properties
bin/kafka-server-start.sh config/server-2.properties
```

创建一个新的topic，replication-factor=3

```
[root@localhost kafka]# bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 3 --partitions 1 --topic my-replicated-topic
Created topic "my-replicated-topic".

[root@localhost kafka]# bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 4 --partitions 1 --topic test4
Error while executing topic command : replication factor: 4 larger than available brokers: 3
[2017-08-11 11:17:17,388] ERROR org.apache.kafka.common.errors.InvalidReplicationFactorException: replication factor: 4 larger than available brokers: 3
 (kafka.admin.TopicCommand$)
```

如何知道哪个broker在做什么？为了看到这个，运行"describe topics"命令

```
[root@localhost kafka]# bin/kafka-topics.sh --describe --zookeeper localhost:2181 --topic my-replicated-topic
Topic:my-replicated-topic	PartitionCount:1	ReplicationFactor:3	Configs:
	Topic: my-replicated-topic	Partition: 0	Leader: 0	Replicas: 0,2,1	Isr: 0,2,1

[root@localhost kafka]# bin/kafka-topics.sh --describe --zookeeper localhost:2181 --topic test2
Topic:test2	PartitionCount:1	ReplicationFactor:1	Configs:
	Topic: test2	Partition: 0	Leader: 0	Replicas: 0	Isr: 0
```

第一行是所有partition的总结，每一行给出了一个partition的信息。因为我们只是一个partition，所有值显示了一行。

- leader: 这个节点负责对指定的partition所有的读写。每一个节点将会被随机选为leader
- replicas: is the list of nodes that replicate the log for this partition regardless of whether they are the leader or even if they are currently alive
- isr: "in-sync" replicas的集合. 它是replicas的子集，表示当前alive并连上leader的列表