```
# 安装httpd
yum install httpd

# 安装squid
yum install squid

# 生成密码（用户名是proxy_username，密码是password123456）
htpasswd -c /etc/squid/passwd proxy_username
New password: 
Re-type new password:

# 看下ncsa_auth在哪个文件夹中
ll /usr/lib/squid/ncsa_auth
ll /usr/lib64/squid/ncsa_auth
ll /usr/lib64/squid/basic_ncsa_auth

# 添加如下内容到/etc/squid/squid.conf
auth_param basic program /usr/lib/squid/ncsa_auth /etc/squid/passwd
acl auth_user proxy_auth REQUIRED
http_access allow auth_user

# 开放端口3128
iptables -I INPUT -p tcp -m state --state NEW -m tcp --dport 3128 -j ACCEPT
service iptables save

# 添加开机自动启动
service squid start
/etc/init.d/squid start
```