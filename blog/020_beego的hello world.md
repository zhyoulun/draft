## 正文

设置GOPATH环境变量，因为`go get`需要，否则会报错。

引入beego框架

```
go get github.com/astaxie/beego
```

编写代码

```
package main

import "github.com/astaxie/beego"

type HomeController struct {
	beego.Controller
}

//接受者
func (homeController *HomeController) Get(){
	homeController.Ctx.WriteString("hello world")
}

func main() {
	beego.Router("/", &HomeController{})//注册路由
	beego.Run()
}
```

运行

```
go run main.go
```

访问

```
> curl http://localhost:8080/
hello world
```

## 参考

- [https://github.com/astaxie/beego](https://github.com/astaxie/beego)
- [Go语言的GOPATH与工作目录详解](http://www.jb51.net/article/56779.htm)
