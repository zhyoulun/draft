## 正文

安装软件

```
yum install -y samba samba-client
```

编辑`/etc/samba/smb.conf`：

```
[tmp]
    path = /dataz/share
    writeable = yes
    browseable = yes
    valid users = demo
```

添加系统用户demo并给samba设置密码

```
useradd demo
smbpasswd -a demo
```

启动服务

```
/sbin/service smb start
/sbin/service nmb start
```

重启

```
/sbin/service smb restart
/sbin/service nmb restart
```

状态查询

```
/sbin/service smb status
/sbin/service nmb status
```

打开137 138 139 445端口

```
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 137 -j ACCEPT
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 138 -j ACCEPT
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 139 -j ACCEPT
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 445 -j ACCEPT
service iptables save
```

赋予共享文件夹足够的权限

```
chmod 777 share_folder/
```

## 参考

- [Sharing Files between CentOS 6 and Windows Systems with Samba](http://www.techotopia.com/index.php/Sharing_Files_between_CentOS_6_and_Windows_Systems_with_Samba)