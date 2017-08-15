```
package main

import (
	"net/http"
	"io"
	"log"
)

func main(){
	//设置路由
	http.HandleFunc("/", sayHello)
	err:=http.ListenAndServe(":8080", nil)
	if(err!=nil){
		log.Fatal("listen and serve error")
	}
}

func sayHello(w http.ResponseWriter, r *http.Request){
	io.WriteString(w, "hello world")
}
```




```
package main

import (
	"net/http"
	"io"
	"log"
)

func main(){
	mux := http.NewServeMux()
	mux.Handle("/", &myHandler{})
	err:=http.ListenAndServe(":8080", mux)
	if err!=nil{
		log.Fatal("listen and serve error")
	}
}

type myHandler struct {
}

func (*myHandler) ServeHTTP(w http.ResponseWriter, r *http.Request){
	io.WriteString(w, r.URL.String())
}
```




```
package main

import (
	"net/http"
	"io"
	"log"
)

func main(){
	mux := http.NewServeMux()
	mux.Handle("/", &myHandler{})
	mux.HandleFunc("/hello", sayHello)
	err:=http.ListenAndServe(":8080", mux)
	if err!=nil{
		log.Fatal("listen and serve error")
	}
}

type myHandler struct {
}

func (*myHandler) ServeHTTP(w http.ResponseWriter, r *http.Request){
	io.WriteString(w, r.URL.String())
}

func sayHello(w http.ResponseWriter, r *http.Request){
	io.WriteString(w, "hello world")
}
```


```
package main

import (
	"net/http"
	"time"
	"io"
	"log"
)

func main() {
	server := http.Server{
		Addr: ":8080",
		Handler: &myHandler{},
		ReadTimeout: 5 * time.Second,
	}

	err:=server.ListenAndServe()
	if err!=nil{
		log.Fatal("listen and serve error")
	}

}

type myHandler struct {
}

func (*myHandler) ServeHTTP(w http.ResponseWriter, r *http.Request){
	io.WriteString(w, r.URL.String())
}
```


```
package main

import (
	"net/http"
	"time"
	"io"
	"log"
)

var mux map[string]func(http.ResponseWriter, *http.Request)

func main() {
	server := http.Server{
		Addr: ":8080",
		Handler: &myHandler{},
		ReadTimeout: 5 * time.Second,
	}

	//通过map保存handler
	mux = make(map[string]func(http.ResponseWriter, *http.Request))
	mux["/hello"] = sayHello
	mux["/bye"] = sayBye

	err := server.ListenAndServe()
	if err != nil {
		log.Fatal("listen and serve error")
	}

}

type myHandler struct {
}

func (*myHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	if h, ok := mux[r.URL.String()]; ok {
		h(w, r)
		return
	}

	io.WriteString(w, r.URL.String())
}

func sayHello(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "hello world")
}

func sayBye(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "byebye")
}
```


静态文件

```
package main

import (
	"net/http"
	"log"
	"os"
)

func main(){
	mux := http.NewServeMux()

	wd, err := os.Getwd()
	if err!=nil{
		log.Fatal(err)
	}

	mux.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir(wd))))

	err=http.ListenAndServe(":8080", mux)
	if err!=nil{
		log.Fatal(err)
	}
}
```