007_PHP中的simplehtmldom学习.md

## 正文

PHP Simple HTML DOM Parser是PHP中较为常用的DOM解析工具。下载地址是[https://sourceforge.net/projects/simplehtmldom/files/](https://sourceforge.net/projects/simplehtmldom/files/)

### 获取网页

在项目中一般使用curl获取到内容之后，将内容传递给simplehtmldom进行解析；也可以使用simplehtmldom内置的函数直接获取网页：

```
require 'simple_html_dom.php';

$html = file_get_html("http://www.example.com");
echo $html;
```

`file_get_html($url)`的`$url`参数也可以是一个文件地址。本质上是调用了`file_get_contents()`函数。

也可以直接解析文本

```
require 'simple_html_dom.php';

$str = <<<EOF
<!doctype html>
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
        
    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 50px;
        background-color: #fff;
        border-radius: 1em;
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        body {
            background-color: #fff;
        }
        div {
            width: auto;
            margin: 0 auto;
            border-radius: 0;
            padding: 1em;
        }
    }
    </style>    
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is established to be used for illustrative examples in documents. You may use this
    domain in examples without prior coordination or asking for permission.</p>
    <p><a href="http://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>
EOF;

$html = str_get_html($str);
echo $html;
```

### 获取感兴趣的数据

```
require 'simple_html_dom.php';

$html = file_get_html('http://www.qq.com/');
if(method_exists($html, "find")){
    $items = $html->find('head link');
    foreach ($items as $item){
        echo "{$item->href}\n";
    }

    $items = $html->find('body a[target=_blank]');
    foreach ($items as $item){
        echo trim($item->plaintext)."\n";
    }
}
```

输出

```
//mat1.gtimg.com/www/icon/favicon2.ico
//mat1.gtimg.com/www/qq_index/css/qq_657073d0.css
//mat1.gtimg.com/www/css/qq2012/hot_word_sogou.css
腾讯网
...
```

## 参考

- [PHP Simple HTML DOM Parser官方文档](http://simplehtmldom.sourceforge.net/)