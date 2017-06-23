## Hello World

```
package main

import (
    "fmt"
    "net/http"
)

func hello(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, "hello world")//返回给客户端
    fmt.Println("this is a log")//打印到控制台
}

func main() {
    http.HandleFunc("/abc", hello)
    http.ListenAndServe(":12345", nil)
}
```

`curl -XGET -i "http://localhost:12345/abc"`的结果是：

```
HTTP/1.1 200 OK
Date: Fri, 23 Jun 2017 09:54:21 GMT
Content-Length: 11
Content-Type: text/plain; charset=utf-8

hello world
```



## 参考

- Go Web编程，鞋孟军