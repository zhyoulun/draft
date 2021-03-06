## 正文

给nginx安装echo插件方便调试，echo插件下载地址[https://github.com/openresty/echo-nginx-module](https://github.com/openresty/echo-nginx-module)

语法规则

`location [=|~|~*|^~] /uri/ {...}`

- = 表示精确匹配,这个优先级也是最高的
- ^~ 表示uri以某个常规字符串开头
- ~ 表示区分大小写的正则匹配 
- ~* 表示不区分大小写的正则匹配(和上面的唯一区别就是大小写) 
- !~和!~*分别为区分大小写不匹配及不区分大小写不匹配的正则
- / 通用匹配，任何请求都会匹配到，默认匹配. 下面讲讲这些语法的一些规则和优先级

### `=`，精确匹配

不支持正则表达式，必须以`/`开头

- 实验一

```
location = / {
    echo 'hello world';
}
```

实验结果

```
[root@localhost ~]# curl 'http://localhost:12345'
hello world
[root@localhost ~]# curl 'http://localhost:12345/'
hello world
[root@localhost ~]# curl 'http://localhost:12345/a'
404
```

- 实验二

```
location = /abc {
    echo 'hello world';
}
```

实验结果

```
[root@localhost ~]# curl 'http://localhost:12345/abc'
hello world
[root@localhost ~]# curl 'http://localhost:12345/ab'
404
[root@localhost ~]# curl 'http://localhost:12345/abcd'
404
```

- 实验三

```
location = /.* {
    echo 'hello world';
}
```

实验结果

```
[root@localhost ~]# curl 'http://localhost:12345/.*'
hello world
[root@localhost ~]# curl 'http://localhost:12345/abc'
404
[root@localhost ~]# curl 'http://localhost:12345/.'
301
[root@localhost ~]# curl 'http://localhost:12345/.*a'
404
```

### `^~` url以某个常规字符串开头

且开头必须是`/`，不支持正则匹配

- 实验一

```
location ^~ abc {
    echo 'hello world';
}
```

```
[root@localhost ~]# curl 'http://localhost:12345/abc'
404
```

- 实验二

```
location ^~ /abc {
    echo 'hello world';
}
```

```
[root@localhost ~]# curl 'http://localhost:12345/abc'
hello world
```

- 实验三

```
location ^~ /.* {
    echo 'hello world';
}
```

```
[root@localhost ~]# curl 'http://localhost:12345/.*'
hello world
[root@localhost ~]# curl 'http://localhost:12345/abc'
404
```

### `~` 区分大小写的正则匹配

- 实验一

```
location ~ ^/a/b/c$ {
    echo 'hello world';
}
```

```
[root@localhost ~]# curl 'http://localhost:12345/a/b/c'
hello world
[root@localhost ~]# curl 'http://localhost:12345/a/b/C'
404
[root@localhost ~]# curl 'http://localhost:12345/a/b/cd'
404
```

- 实验二

```
location ~ /a/b/c {
    echo 'hello world';
}
```

```
[root@localhost ~]# curl 'http://localhost:12345/a/b/c'
hello world
[root@localhost ~]# curl 'http://localhost:12345/a/b/C'
404
[root@localhost ~]# curl 'http://localhost:12345/d/a/b/c'
hello world
[root@localhost ~]# curl 'http://localhost:12345/a/b/c/d'
hello world
```

- 实验三

```
location ~ [a-z]+ {
    echo 'hello world';
}
```

```
[root@localhost ~]# curl 'http://localhost:12345/abc'
hello world
[root@localhost ~]# curl 'http://localhost:12345/123'
404
[root@localhost ~]# curl 'http://localhost:12345/ABC'
404
```

### `~*` 表示不区分大小写的正则匹配(和`~`唯一区别就是大小写)

```
location ~ [a-z]+ {
    echo 'hello world';
}
```

```
[root@localhost ~]# curl 'http://localhost:12345/abc'
hello world
[root@localhost ~]# curl 'http://localhost:12345/123'
404
[root@localhost ~]# curl 'http://localhost:12345/ABC'
hello world
```

### `/` 通用匹配，任何请求都会匹配到，默认匹配

```
location / {
    echo 'hello world';
}
```

```
[root@localhost ~]# curl 'http://localhost:12345'
hello world
[root@localhost ~]# curl 'http://localhost:12345/'
hello world
[root@localhost ~]# curl 'http://localhost:12345/123'
hello world
```

## 常用案例

### 忽略`/favicon.ico`的日志

```
location = /favicon.ico {
    access_log off;
}
```

### 设置静态文件

```
location ~* .*\.(gif|jpg|jpeg|png|bmp|swf)$ {
    expires 30d;
}
```

```
[root@localhost ~]# curl -I 'http://localhost:12345/test.jpg'
HTTP/1.1 200 OK
Server: nginx/1.10.3
Date: Thu, 06 Jul 2017 15:20:23 GMT
Content-Type: image/jpeg
Content-Length: 117843
Last-Modified: Sun, 07 May 2017 16:24:31 GMT
Connection: keep-alive
ETag: "590f4a3f-1cc53"
Expires: Sat, 05 Aug 2017 15:20:23 GMT
Cache-Control: max-age=2592000
Accept-Ranges: bytes
```

### 禁止访问`.git`或者`.svn`文件夹

```
location ~ \/\.(git|svn)\/ {
    deny all;
}
```

临时将`deny all;`换成`echo 'hello world';`

```
[root@localhost ~]# curl 'http://localhost:12345/.git/'
hello world
[root@localhost ~]# curl 'http://localhost:12345/.svn/'
hello world
[root@localhost ~]# curl 'http://localhost:12345/a/.git/'
hello world
[root@localhost ~]# curl 'http://localhost:12345/.git/a'
hello world
[root@localhost ~]# curl 'http://localhost:12345/a/.git/b'
hello world
```

### 转发请求

```
location ~ \.php {
    fastcgi_pass 127.0.0.1:9000;
    include fastcgi.conf;

    fastcgi_param env 'dev';//设置$_SERVER['env']变量
}
```

`test.php`文件

```
<?php
$arr = [1,2,3];
var_dump($arr);
var_dump($_SERVER['env']);
```

```
[root@localhost ~]# curl 'http://localhost:12345/test.php'
array(3) {
  [0]=>
  int(1)
  [1]=>
  int(2)
  [2]=>
  int(3)
}
string(3) "dev"
```

## 参考

- [nginx配置location总结及rewrite规则写法](http://seanlook.com/2015/05/17/nginx-location-rewrite/)
- [Nginx 的 Echo 模块 —— echo-nginx-module](http://www.oschina.net/question/12_45735)