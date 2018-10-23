# Linux简要介绍

Linux是一个开源的操作系统内核，发布于GPL协议，全称是GNU/Linux。

- **Linux和Unix是不同的**，但它们看起来很像。因为Linux参考了Unix的设计思想。
- Linux简洁、高效、功能强大。

安装UbuntuServer16.04 -- 详情见Qu1.docx

# **关机和重启**

Linux上使用shutdown命令进行关机重启，定时关机等操作。

 实际上Windows启动cmd或者是PowerShell运行shutdown也是可以的，当点
击关机的时候调用的就是shutdown。

```c
// 关机命令
frewen@ubuntu:~$ sudo shutdown -h now
// 重启命令
frewen@ubuntu:~$ sudo shutdown -r now
```



