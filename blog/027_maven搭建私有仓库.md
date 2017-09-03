

```
mvn deploy:deploy-file -DgroupId=cn.qihoo -DartifactId=qbus2-client -Dversion=1.0.0-SNAPSHOT -Dpackaging=jar -Dfile=/X/storm/qbus2-demo/libs/qbus2-client-0.1.0.jar -Durl=http://172.23.13.12:8081/repository/zhangyoulun-host/ -DrepositoryId=zhangyoulun-host
```


## 参考

- [Nexus3.x.x上传第三方jar](http://blog.csdn.net/iopfan/article/details/71107686)
- [使用Nexus搭建maven私有仓库](http://www.jianshu.com/p/9740778b154f)