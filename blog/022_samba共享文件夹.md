```
yum install samba -y

useradd samba
mkdir /dataz/share
chown samba:samba /dataz/share
```

添加用户，设置密码

```
useradd samba
smbpasswd -a samba
```

在`/etc/samba/smb.conf`添加

```
[samba]
    path= /dataz/samba
    browseable = yes
    writable = yes
    valid users = samba
```


添加开机自动启`/etc/rc.local`

```
/etc/init.d/smb start
/etc/init.d/nmb start
```

开启端口

```
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 137 -j ACCEPT
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 138 -j ACCEPT
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 139 -j ACCEPT
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 445 -j ACCEPT
service iptables save
```