## 正文

### gif

```
yum install giflib giflib-devel -y
```

### jpeg

下载地址[http://www.ijg.org/](http://www.ijg.org/)

```
wget http://www.ijg.org/files/jpegsrc.v9b.tar.gz
tar -zxvf jpegsrc.v9b.tar.gz
./configure --prefix=/root/software/lib-jpeg
make
make install
```

### png

```
yum install libpng libpng-devel -y
```

### xpm

```
yum install libXpm libXpm-devel -y
```







### webp

下载地址[https://github.com/webmproject/libwebp/releases](https://github.com/webmproject/libwebp/releases)

依赖[http://www.linuxfromscratch.org/blfs/view/svn/general/libwebp.html](http://www.linuxfromscratch.org/blfs/view/svn/general/libwebp.html)

安装libvpx

```
yum install libvpx-devel libvpx -y
```

安装编译环境

```
yum install gcc make autoconf automake libtool -y
```

安装libtiff、libpng和libjpeg-turbo依赖

```
yum install libtiff libtiff-devel -y
yum install libpng libpng-devel -y
yum install libjpeg-turbo libjpeg-turbo-devel -y
```

```
wget https://github.com/webmproject/libwebp/archive/v0.6.0.tar.gz
tar -zxvf v0.6.0.tar.gz
cd libwebp-0.6.0/
./autogen.sh
./configure --prefix=/root/software/lib-webp
make
make install
```

状态

```
WebP Configuration Summary
--------------------------

Shared libraries: yes
Static libraries: yes
Threading support: yes
libwebp: yes
libwebpdecoder: no
libwebpdemux: no
libwebpmux: no
libwebpextras: no

Tools:
cwebp : yes
  Input format support
  ====================
  JPEG : yes
  PNG  : yes
  TIFF : yes
  WIC  : no
dwebp : yes
  Output format support
  =====================
  PNG  : yes
  WIC  : no
GIF support : yes
anim_diff   : no
gif2webp    : no
img2webp    : no
webpmux     : no
vwebp       : no
```






### FreeType 2

```
yum install freetype freetype-devel -y
```

### 添加gd扩展

```
yum install autoconf -y
cd php-5.6.31/ext/gd
phpize
php-config
export LD_LIBRARY_PATH=/root/software/lib-webp/lib:$LD_LIBRARY_PATH
export LIBDIR=/root/software/lib-webp/lib:$LIBDIR
./configure --with-php-config=php-config --with-jpeg-dir=/root/software/lib-jpeg --with-xpm-dir --with-vpx-dir
```

添加`extension=gd.so`到`php.ini`

```
gd

GD Support => enabled
GD Version => bundled (2.1.0 compatible)
GIF Read Support => enabled
GIF Create Support => enabled
JPEG Support => enabled
libJPEG Version => 9 compatible
PNG Support => enabled
libPNG Version => 1.2.49
WBMP Support => enabled
XPM Support => enabled
libXpm Version => 30411
XBM Support => enabled
WebP Support => enabled
```

## 参考

- [需求](http://php.net/manual/zh/image.requirements.php)
- [如何使GD支持webpq](http://www.voidcn.com/blog/morose999/article/p-6042753.html)