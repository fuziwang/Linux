# 必备知识

```c
(1) Linux的开发者是Linus--林纳斯·托瓦兹
(2) 查看自己电脑的系统的发行版
frewen@Ubuntu:~$ uname -a
/*.....
版本：Ubuntu 16.04
内核：GNU/Linux
发布协议：GPL协议(类似的协议有Apache MIT)
文件系统：Ext4
*/
```

# 目录结构

```c
(1) / 表示的是根目录 . 表示当前目录 .. 表示上一级目录
(2) 常用的目录
l /   -- 查看根目录下的文件信息
bin/  -- 存放系统内置软件，和内置命令
sbin/ -- 存放超级用户使用的命令
dev/  -- 保存设备文件
etc/  -- 系统配置文件、内核配置文件、软件配置文件、网络配置文件
/*尤其注意*/
/etc/passwd 保存用户的基本信息
/etc/shadow 保存用户的密码信息
/etc/group  保存用户组的信息
```

常用的简单的命令

```c
ls     --显示目录/文件 //常用参数 ls -a（显示隐藏文件） ls -l（显示权限） ls -R（递归的显示文件目录）
cd     --切换目录 // 在任何目录下cd都是当前目录 cd- 返回到上一次使用的目录 cd .. 返回到上一级目录
df     --查看磁盘使用情况
fdisk  --磁盘格式化
mkfs   --创建文件系统
mount  --挂载设备
umount --卸载设备
```

# 命令终端基础

区分几个概念

```c
终端：终端就是一个具有输入和输出功能的设备
虚拟控制台：就是window上的任务窗口，不同的桌面环境
shell：shell一方面是一个程序，另一方面是一个编程语言，用户通过shell将输入给了系统内核，系统内核还需通过shell将输出信息给了用户
```

Linux命令

```c
Linux将命令可以分为内部命令和外部命令
(1) 区分内部命令和外部命令 type commond// 如果是内部命令，就是内置的程序，如果是外部命令也是一个程序，只不过需要根据路径进行查找
(2) ls -a ls --color ls -al
(3) 获取命令的帮助：frewen@Ubuntu:~$ man cp//查看不是shell内建命令的帮助手册
  frewen@Ubuntu:~$ help cd//查看shell内建命令的帮助手册 
(4) 命令的搜索路径 .profile记录了系统会在哪些目录下查找命令
vim .profile可以在这个文件里面添加PATH=$HOME/ins
将ins目录添加到了环境变量里面去了
然后运行 source .profile
通过env可以查看环境变量
```

终端常用命令

| 命令    | 说明                                       |
| ----- | ---------------------------------------- |
| ls    | 列出文件、目录信息                                |
| cd    | 切换当前的工作目录                                |
| mkdir | 创建目录                                     |
| rmdir | 删除空目录                                    |
| touch | 创建空文件                                    |
| rm    | 删除文件或目录，rm -rf bin/ 删除了目录及文件             |
| cp    | 讲一个或多个源文件或者目录复制到指定的文件或目录                 |
| mv    | 将一个文件从一个目录移动到另一个目录，同时实现重命名的功能            |
| cat   | 将文件的所有内容显示在设备上                           |
| more  | 以全屏幕的显示文本的内容                             |
| less  | 分页显示，多用于管道中，功能要比more的强大                  |
| env   | 显示环境变量                                   |
| find  | 在指定的目录下查找文件 find 目录 -iname `*gcc*`(不区分大小写) |

# IO重定向和管道

文件描述符

```c
当文件描述符为0：这表示的是标准的输入
当文件描述符为1：这表示的是标准的输出
当文件描述符为2：这表示的是标准的错误
```

所谓IO重定向就是标准的输出指向的是终端（屏幕），通过重定向的作用，将标准的输出指向某一个文件

控制重定向的shell（shell通过创建子程序来控制）

IO重定向的符号

```c
< 输入重定向
> 输出重定向  >> 追加内容
2> 错误输出重定向 2>> 错误输出追加内容
&> 或 >& 标准的输出和错误重定向
```

管道

```c
所谓管道就是将前者的进行输出重定向，将后者进行输入重定向（将两个进程的输入输出重定向到管道）
实例：
查找名称含有curl的文件进行计数，并把错误信息重定向到/dev/null
find / -iname *gcc* 2> /dev/null  | wc -l
查找名称含有ssh的进程
ps -ef | grep ssh
分页查看内容
cat /etc/passwd | less
```

# 用户和组管理

用户

```c
linux用户可以分为三类：普通用户 root用户 系统用户
用户的基本信息存放在 /etc/passwd
用户的密码信息存放在 /etc/shadow
用户组的相关信息存放在 /etc/group
Linux用户组的分类：
// 1 普通用户组 root用户组 系统用户组
// 2 基本组（一个用户只属于一个基本组） 附加组（一个用户可以属于多个附加组）
// 3 私有组（一个用户只能属于一个私有组） 公共组
```

用户的权限

```c
root用户的UID为0 root用户的权限最高
su - OKLinux // 切换用户
sudo // 在执行kill 或者ps操作的时候，有时候需要进行sudo操作
adduser deluser addgroup delgroup
(1) adduser添加用户
sudo adduser --shell /bin/bash oklinux --gid 1000
(2) deluser删除用户
sudo deluser oklinux
(3) addgroup添加用户组
sudo addgroup oklinux
(4) delgroup删除用户组
sudo delgroup oklinux
```

# 文件编辑

Linux中主要的编辑器是nano和vim

vim的搜索和匹配

```c
其中注意0代表首行 $表示的是尾行
:/php 匹配到所有的php
:s/php/c 将当前行的第一个PHP用c来替换
:s/php/c/g 将当前行的所有的php用c来替换
:%s/php/c 将所有行的第一个PHP用c来替换
:%s/php/c/g 将所有行的php用c来替换
:1,$s/php/c 将从第一行到最后一行的所有的PHP用c来替换
注意：在vim中运行命令:!ls
```

# 文件管理

相关命令

```c
ls 列出文件/目录信息
stat 显示文件详细信息
rmdir 删除空目录
cp rm mv 赋值、删除、移动
/**********************************
1 复制tmp/a文件，到tmp目录，命名为b  
cp tmp/a tmp/b
2 复制c/fst.c文件到tmp目录，名称不变  
cp c/fst.c tmp/
3 递归复制目录c到tmp  
cp c/ tmp/ -R
4 删除tmp目录，目录必须为空  
rmdir tmp
5 删除c/test.c文件  
rm c/test.c
6 强制删除tmp目录，目录不为空也可以删除  
rm -rf tmp/
7 移动c/fst文件到bin目录  
mv c/fst bin/
8 移动c/fst1文件到bin目录，命名为fst  
mv c/fst1 bin/fst
9 显示文件详细信息
stat tmp.sh
**********************************/
ln 创建硬链接或软链接-s
// 硬链接：硬链接并没有创建新的文件，而是相当于一个指针指向了某一个文件的内容（iNode一样），当删除某一个文件，只不过这个文件的硬链接的数目-1，当这个文件的硬链接数目为0，这个文件才真正的删除
// 软链接：软链接创建了新的文件，这个文件存放的是文件的路径（iNode不一样），当软链接所对应的文件进行删除后，便找不到这个文件了
创建链接的时候最好用绝对路径
ln 目标文件 链接
ln -s 目标文件 链接
chmod 给文件改变权限
// 预备知识umask
# 掩码的计算规则：用777按位减去掩码中的相应位，并且文件还要减去可执行位。
# umask 显示权限掩码
# umask 022 设置权限掩码的值
chmod 755 frewen
chmod +x frewen
chown 改变文件的所有者
chown oklinux:oklinux frewen
chown oklinux: frewen
chown :oklinux frewen
chown oklinux:oklinux c/ -R
```

# 进程管理

常见命令

```c
pid 当前进程id ppid 父进程的id
# ps 显示当前的进程
ps -e显示所有的进程
ps -e | grep ssh// 通过管道匹配所有进程中的含有ssh进程
# kill 向进程发送信号，通常是终止进程
kill 25183(如果是root用户，则应该用sudo，其他用户也应该用sudo) 默认的信号是SIGNTERM
kill -9 25183发送信号SIGNKILL强制进程停止执行 
# bg shell内建命令，后台的任务继续执行，就像在命令后面加入&
# fg shell内建命令，后台任务转至前台
# jobs shell内建命令，显示后台运行的任务
# pgrep 搜索进程
# top/htop 动态监控进程的情况，系统资源的使用情况
# nice/renice 调整进程的优先级
```

# shell脚本基础-变量

变量

```c
(1) shell环境变量通过export实现全局变量
echo $PWD echo $HOME
a=12 export a env//可实现全局变量的定义
(2) shell中的通配符 * ls a* //把以a开头的所有文件或目录展示出来
(3) shell脚本
/********************
#!/bin/bash
a=12
echo $a
echo $PWD
exit 0
运行shell脚本
bash 文件名或者 chmod 755 文件名 文件名
********************/
(4) shell变量
变量的命名方式：字母、下划线开头由字母或下划线或数组组成的
a=1+2 =左右不能有空格，其中等号后面的内容实质上是文本，变量是什么，输出就是什么
echo $a 获取a的结果
使用set | grep a可以对变量进行查看和筛选 unset a//清除变量
readonly a 只读变量
(5) 对变量进行运算
$(())可以进行运算 --算术运算 逻辑运算
```

脚本中特殊的变量

```shell
$0：当前脚本的文件名/当前执行的进程/程序名
$n：n为从1开始的数字，$1是第一个参数，$2是第二个参数，${10}是第十个参数（从${10}开始参数号需要用花括号括起来）
$#：传入脚本的参数的个数
$*：所有的位置参数(作为单个字符串)
$@：所有的位置参数(每个都作为独立的字符串)。
$?：当前shell进程中，上一个命令的返回值，如果上一个命令成功执行则$?的值为0，否则为其他非零值，常用做if语句条件
$$：当前shell进程的pid
$!：后台运行的最后一个进程的pid
```

# shell脚本基础-逻辑判断和循环

逻辑判断

```c
test内建命令 相当于[] 当[]里面存在逻辑与或者逻辑或的时候，需要用到[[]]
逻辑判断的基本结构
# -gt:> ; -lt:< ; -eq:= ; -ne:!= -le:<= ; -ge:>=
/************************
方式1：
if []; 其中;可以加也可以不加
then
fi
方式2：
if [];then
	command
else
	command
fi
方式3:
if [];then
	command
elif [];then
	command
else
	command
fi
************************/
case语句的实现
/*****************************
case word in
	time)
		;;
	cpu)
		;;
	*)
		;;
esac
*****************************/
```

循环

```shell
# shell循环基本结构
for name in words;
  do
      command
  done
while [command];
  do
  done
```

# Linux中C编程

```c
#include <stdio.h>
int main(int argc, char* argv[])
{
    printf(“program name: %s\n”, argv[0]);
    for (int i=1; i<argc; i++) 
        printf(“%s ”, argv[i]);
    if (argc>1)
        printf(“\n”);
    return 0;
}
gcc program.c
./a.out//不易于区分
gcc -o program program.c
./program
```

# Linux系统编程

```c
(1) getpid()得到当前进程的id getppid()
(2) fork()创建子进程进行操作，有多少个fork操作就有2的多少次方个子进程，当父进程结束的时候，谁是子进程的父进程呢？ init是子进程的父进程
(3) wait()等待子进程的结束，之后父进程再结束
```

# Linux系统调用

```c
(1) open close函数 O_RDONLY O_WRONLY O_CREAT O_RDWR S_IRUSR S_IWUSR S_IRWXU
(2) read函数 write函数
(3) close fd=1 close / close(1) dup(fd) / dup2(fd,1)
```



