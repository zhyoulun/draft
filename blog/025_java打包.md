## 正文

安装java和maven

设置JAVA_HOME和M2_HOME

查看是否成功安装

```
$ java -version
java version "1.8.0_144"
Java(TM) SE Runtime Environment (build 1.8.0_144-b01)
Java HotSpot(TM) 64-Bit Server VM (build 25.144-b01, mixed mode)
```

```
$ mvn -v
Apache Maven 3.3.9 (bb52d8502b132ec0a5a3f4c09453c07478323dc5; 2015-11-11T00:41:47+08:00)
Maven home: D:\software\develop\apache-maven-3.3.9
Java version: 1.8.0_144, vendor: Oracle Corporation
Java home: D:\software\develop\Java\jdk1.8.0_144\jre
Default locale: zh_CN, platform encoding: GBK
OS name: "windows 7", version: "6.1", arch: "amd64", family: "dos"
```

在`pom.xml`中添加`maven-assembly-plugin`插件，用于打包，作为`<project></project>的子节点`

```
<build>
    <plugins>
        <plugin>
            <artifactId>maven-assembly-plugin</artifactId>
            <configuration>
                <archive>
                    <manifest>
                        <mainClass>com.study.Main</mainClass>
                    </manifest>
                </archive>
                <descriptorRefs>
                    <descriptorRef>jar-with-dependencies</descriptorRef>
                </descriptorRefs>
            </configuration>
        </plugin>
    </plugins>
</build>
```

运行

```
mvn package assembly:single
```

可以在target文件夹中找到结果文件`xxx-jar-with-dependencies.jar`

然后就可以运行了

```
$ java -jar study4-1.0-SNAPSHOT-jar-with-dependencies.jar 
hello world
```

## 参考

- [maven-assembly-plugin把java工程打包成为一个可执行的jar包](http://blog.csdn.net/qiyueqinglian/article/details/46229157)
- [Maven生成可以直接运行的jar包的多种方式](http://blog.csdn.net/xiao__gui/article/details/47341385)