函数原型

```
//编码
func Marshal(v interface{}) ([]byte, error)

//解码
func Unmarshal(data []byte, v interface{}) error
```

### 编码

```
package main

import (
    "encoding/json"
    "fmt"
)

type Student struct {
    Id     int
    Name   string
    Gender bool
    Age    int
}

func main() {
    student := Student{
        Id:     1,
        Name:   "zhao",
        Gender: true,
        Age:    11,
    }

    fmt.Println(student)
    out, err := json.Marshal(student)
    if err != nil {
        fmt.Println("json marsha1 error")
    }
    fmt.Printf("%s\n", out)
}
```

输出

```
{1 zhao true 11}
{"Id":1,"Name":"zhao","Gender":true,"Age":11}
```

### 解码

```
package main

import (
    "encoding/json"
    "fmt"
)

type Student struct {
    Id     int
    Name   string
    Gender bool
    Age    int
}

func main() {
    var jsonStr string = `{"Id":1,"Name":"zhao","Gender":true,"Age":11}`
    fmt.Println(jsonStr)
    var s Student
    err := json.Unmarshal([]byte(jsonStr), &s)
    if err != nil {
        fmt.Println("json unmarshal error: ", err)
    }
    fmt.Println(s)
}
```

输出

```
{"Id":1,"Name":"zhao","Gender":true,"Age":11}
{1 zhao false 11}
```

