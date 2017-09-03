
```
create table student(
id int unsigned not null auto_increment comment 'ID',
name varchar(16) comment '姓名',
age tinyint unsigned comment '年龄',
gender bit(1) comment '性别',
create_time datetime comment '创建时间',
primary key(id)
)ENGINe=INNODB DEFAULT CHARSET=utf8 auto_increment=1;
```

### 插入一条记录

```
package main

import (
    _ "github.com/go-sql-driver/mysql"
    "fmt"
    "database/sql"
    "time"
)

func main() {
    db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/study")
    if err != nil {
        panic(err.Error())
    }
    defer db.Close()//关闭连接

    //验证是否可以成功连接
    err = db.Ping()
    if err != nil {
        panic(err.Error())
    }

    //插入一条记录
    stmt, err := db.Prepare("insert into student(name,age,gender,create_time) values(?,?,?,?);")
    result, err := stmt.Exec("zhao", 11, false, time.Now().Format("2006-01-02 15:04:05"))
    if err != nil {
        panic(err.Error())
    }
    defer stmt.Close()// Close the statement when we leave main() / the program terminates

    //获取上次插入的ID
    lastInsertId, err := result.LastInsertId()
    if err != nil {
        panic(err.Error())
    }
    fmt.Println(lastInsertId)
}
```

### 查询

```
package main

import (
    _ "github.com/go-sql-driver/mysql"
    "database/sql"
    "fmt"
)

func main() {
    db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/study")
    if err != nil {
        panic(err.Error())
    }
    defer db.Close()//关闭连接

    //验证是否可以成功连接
    err = db.Ping()
    if err != nil {
        panic(err.Error())
    }

    //查询
    rows, err := db.Query("select * from student;")
    if err != nil {
        panic(err.Error())
    }

    //获取列名称
    columns, err := rows.Columns()
    if err != nil {
        panic(err.Error())
    }
    fmt.Println(columns)

    //遍历输出
    for rows.Next() {
        var id int
        var name string
        var age int
        var gender string
        var createTime string

        err = rows.Scan(&id, &name, &age, &gender, &createTime)
        if err != nil {
            panic(err.Error())
        }

        fmt.Println(id, name, age, gender[0], createTime)
    }
}
```


```
package main

import (
    _ "github.com/go-sql-driver/mysql"
    "database/sql"
    "fmt"
)

func main() {
    db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/study")
    if err != nil {
        panic(err.Error())
    }
    defer db.Close()//关闭连接

    //验证是否可以成功连接
    err = db.Ping()
    if err != nil {
        panic(err.Error())
    }

    //查询
    rows, err := db.Query("select * from student;")
    if err != nil {
        panic(err.Error())
    }

    //获取列名称
    columns, err := rows.Columns()
    if err != nil {
        panic(err.Error())
    }
    fmt.Println(columns)

    //构造scanArgs、values两个数组，scanArgs的每个值指向values相应值的地址
    scanArgs := make([]interface{}, len(columns))
    values := make([]interface{}, len(columns))
    for i := range values {
        scanArgs[i] = &values[i]
    }

    //遍历输出
    for rows.Next() {
        err = rows.Scan(scanArgs...)
        if err != nil {
            panic(err.Error())
        }

        //将行数据保存到record字典
        record := make(map[string]string)
        for i, col := range values {
            if col != nil {
                record[columns[i]] = string(col.([]byte))
            }
        }

        fmt.Println(record)
    }
}
```


```
package main

import (
    _ "github.com/go-sql-driver/mysql"
    "database/sql"
    "fmt"
)

func main() {
    db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/study")
    if err != nil {
        panic(err.Error())
    }
    defer db.Close()//关闭连接

    //验证是否可以成功连接
    err = db.Ping()
    if err != nil {
        panic(err.Error())
    }

    //查询一条记录
    stmt, err := db.Prepare("select * from student where id=?;")
    if err != nil {
        panic(err.Error())
    }
    var id int
    var name string
    var age int
    var gender string
    var createTime string
    err = stmt.QueryRow(6).Scan(&id, &name, &age, &gender, &createTime)//where id=6
    if err!=nil{
        panic(err.Error())
    }
    fmt.Println(id, name, age, gender[0], createTime)
}
```

### 更新

```
package main

import (
    _ "github.com/go-sql-driver/mysql"
    "fmt"
    "database/sql"
    "time"
)

func main() {
    db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/study")
    if err != nil {
        panic(err.Error())
    }
    defer db.Close()//关闭连接

    //验证是否可以成功连接
    err = db.Ping()
    if err != nil {
        panic(err.Error())
    }

    //更新一条数据
    stmt, err := db.Prepare("update student set create_time=? where id=?;")
    result, err := stmt.Exec(time.Now().Format("2006-01-02 15:04:05"), 7)
    if err != nil {
        panic(err.Error())
    }
    defer stmt.Close()// Close the statement when we leave main() / the program terminates

    //获取更新的记录数量
    rowsAffect, err := result.RowsAffected()
    if err != nil {
        panic(err.Error())
    }
    fmt.Println(rowsAffect)
}
```

### 删除

```
package main

import (
    _ "github.com/go-sql-driver/mysql"
    "fmt"
    "database/sql"
)

func main() {
    db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/study")
    if err != nil {
        panic(err.Error())
    }
    defer db.Close()//关闭连接

    //验证是否可以成功连接
    err = db.Ping()
    if err != nil {
        panic(err.Error())
    }

    //删除一条数据
    stmt, err := db.Prepare("delete from student where id=?;")
    result, err := stmt.Exec(7)
    if err != nil {
        panic(err.Error())
    }
    defer stmt.Close()// Close the statement when we leave main() / the program terminates

    //获取删除的记录数量
    rowsAffect, err := result.RowsAffected()
    if err != nil {
        panic(err.Error())
    }
    fmt.Println(rowsAffect)
}
```

## 参考

- [go-sql-driver/mysql examples](https://github.com/go-sql-driver/mysql/wiki/Examples)
- [https://github.com/go-sql-driver/mysql](https://github.com/go-sql-driver/mysql)
- [Go操作mysql实现增删改查及连接池](http://blog.csdn.net/kenkao/article/details/47857795)