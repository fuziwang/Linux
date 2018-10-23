# shell的概念

Shell是一个命令行解释器，它为用户提供了一个向Linux内核发送请求以便运行程序的界面系统级程序，用户可以用Shell来启动、挂起、停止甚至时编写一些程序。

Shell还是一个功能相当**强大的编程语言**，易编写，易调试，灵活性较强。Shell是解释执行的脚本语言，在Shell中可以直接调用Linux系统命令

![shell详细解答](file:///C:/Users/FUZIWANG/AppData/Local/Temp/msohtmlclip1/01/clip_image002.jpg)

```c
/*Shell执行命令的过程*/
比如某一个用户在系统中输入ls命令
（1）shell会将ls命令转换成所需的二进制代码
（2）将命令传递给内核，由内核调用硬件来完成命令
（3）系统会将命令运行的结果（此时的结果仍然是二进制）转换为Ascll码，再通过shell传递给用户
```

## shell在系统的角色

- shell是用户和系统交互的桥梁（通过shell用户和系统进行沟通）
- shell是Linux的一个程序，实现版本有多种。shell的主要工作就是运行命令。
- sh是shell的简写，**shell**的实现版本有：sh，bash，csh，tcsh，zsh。
- **多数Linux**默认的shell**是bash**。Linux启动登录以后，会运行一个shell等待用户输入命令。

## shell环境变量

**（1）环境变量的概念**

当前shell运行时保存的信息，包括终端类型，当前目录，主目录，语言编码，默认命令搜索路径等信息。**运行env命令可以查看当前环境变量**。

```c
frewen@ubuntu:~$env
```

PS：环境变量就是一个对象，这个对象包括当前用户所对应的系统的环境信息

**（2）添加临时的环境变量的命令export**

环境变量是一个名称和值的对应列表。一种是shell启动时解析配置文件生成，还有一种临时的环境变量是**在shell中使用export生成**。

```c
利用vim打开/etc/ profile文件，用export指令添加环境变量。 
export MYNAME=”root”
```

**（3）PATH、PSW、HOME三者的用法（重点）**

PATH变量记录了要查找命令的路径顺序；HOME**记录当前用户主目录**；PWD是**当前工作目录，每次切换目录都会变化。**

使用`$`取值：`echo $PWD`，而`echo PWD`仅仅是输出PWD字符串

```c
frewen@ubuntu:~echo PWD
frewen@ubuntu:~echo HOME
```

![center](file:///C:/Users/FUZIWANG/AppData/Local/Temp/msohtmlclip1/01/clip_image004.jpg)

## shell运行命令的基本过程

（1）输入一条命令并确认后，实际shell获取的是**一行字符串**，shell**要对字符串进行解析**，**并确定命令名称，参数等信息。**shell支持从文件读取文本逐条解释执行。

（2）shell要根据配置文件的**搜索**路径，从每个路径寻找命令，没有找到则提示错误信息，找到就**调用Linux提供的系统**调用运行命令。

**注意：真正运行命令的不是shell，而是内核**，shell去调用内核提供的接口，shell是调用fork创建子进程去运行命令。

![](file:///C:/Users/FUZIWANG/AppData/Local/Temp/msohtmlclip1/01/clip_image006.jpg)

例如：

```c
frewen@ubuntu:~$ls –l
/*
shell要将命令解析成字符串，也就是解析成‘ls’,‘-l’，’ls’就是命令名称，并在PATH设置的路径中寻找，找到/bin/ls这个命令，fork一个子进程调用execv等系统调用传递参数运行命令。并等待结束。
*/
```

## shell中的通配符

（1）shell支持通配符，使用*****表示匹配任意长度的字符，**?**匹配任意一个字符。

（2）shell在遇到通配符会进行扩展，比如输入ls ./a*，会匹配a开头的所有文件并显示，如果存在ab.txt，ac.txt，则会扩展成  ls ./ab.txt ./ac.txt。

```c
frewen@ubuntu:~$ls ./a*
frewen@ubuntu:~$ls ./a?
```

**注意：扩展通配符的是shell，不是命令自身**，如果是命令本身实现的，那就每个命令都要实现。

## shell脚本

**（1）shell脚本的概念**

shell可以从一个文件读取命令并逐条执行。文件一般被称为脚本。大多数Linux发行版的默认shell都是bash。

**（2）shell脚本的编写和执行**

文件第一行使用**#!/bin/bash**表明这是一个bash脚本，注意有些脚本程序使用**#!/bin/sh**表示。

一个简单的脚本：**开头声明这是一个bash脚本**，然后是主要操作代码，最后以**exit 0**退出。

简单的脚本程序：

```c
#！/bin/bash
echo “Hello World”
exit 0
执行脚本可以使用 bash [SCRIPT NAME]，此时bash读取脚本文件并执行，#!/bin/bash是被解释为注释。
另一种方式就是给脚本添加可执行权限：chmod +x [SCRIPT NAME]，给脚本添加执行权限，脚本开头的#!/bin/bash声明这是一个脚本文件，要用/bin/bash执行。

//上述为使程序可以执行的代码如下：
frewen@ubuntu:~$ bash bin/a.sh
Hello World
frewen@ubuntu:~$ chmod 755 bin/a.sh
frewen@ubuntu:~$ bin/a.sh
Hello World
```

# 变量

## 变量的基本操作

### **（1）定义变量**

```c
frewen@ubuntu:~$ a=123 //定义了一个变量(定义变量不能有空格)

shell运行a=123就定义了a变量。shell中的变量就是为某些需要保存的数据用一个名称标记，方便以后使用。
shell中的变量就是键值对（key-value）的列表，都是以文本的形式存储的。a=1+2不会进行计算把3赋值给a，而是a的值就是‘1+2’这段文本。变量的值可以用双引号/单引号括起来，包含空格的变量就必须要这么做。
  
frewen@ubuntu:~$ a=1+2// 此时a的值不是3，而是1+2这个字符串
frewen@ubuntu:~$ a=123// 如果想包含空格，那么可以使用a=”1 + 2” 
```

### **（2）变量的命名规则**

变量的名称以字母或是下划线符号开头，后可跟任意长度的字母、数字、下划线。

注意：

```c
= 左右不能有空格，否则会按照运行命令的方式去执行。
frewen@ubuntu:~$ a = 123 //这种定义变量的方式就是错误的

a=`ls` 会把ls运行的结果赋值给a。注意ls不是被单引号包含，而是反引号。

frewen@ubuntu:~$ a=`ls` // 会把ls运行的结果赋值给a
```

### **（3）读取变量**

```c
获取变量的值要用$，echo $a可以输出变量的值。
frewen@ubuntu:~$ echo $a //这样可以输出a的值 
```

### **（4）变量查看与清除**

```c
用set命令可以查看所有的变量。
frewen@ubuntu:~$ set
可以使用 set | grep linux 进行搜索
frewen@ubuntu:~$ set | grep linux // 搜索linux变量
unset VAR 命令可以清除变量VAR，相当于没有定义过。使用空格分隔多个变量。
frewen@ubuntu:~$ unset a // 清除a变量
```

### **（5）只读变量**

```c
变量设置后，是可以修改值的。

frewen@ubuntu:~$ a=12
frewen@ubuntu:~$ a=13 //此时a的值是13

readonly把变量设置为只读：readonly a
frewen@ubuntu:~$ readonly a// 只读变量设置之后，只读变量就无法更改和清除。除非重置shell环境。
```

## 放进环境变量（需要用到关键词export）

- 环境变量是全局存在的，在任何shell脚本中都可以直接使用。
- 使用env查看环境变量。
- export a：把变量放到环境变量，环境变量是一个名称与值的简单列表。

```c
使用示例，shell中执行：
frewen@ubuntu:~$ env | grep linux
frewen@ubuntu:~$ linux=1
frewen@ubuntu:~$ export linux
frewen@ubuntu:~$ env | grep linux
```

## 变量的引用

| **${#var}**                   | 返回变量值（字符串）的长度                            |
| ----------------------------- | ---------------------------------------- |
| **${var:start_index}**        | 返回从start_index开始一直到字符串结尾的字符串             |
| **${var:start_index:length}** | 返回从start_index开始的length个字符               |
| **${var:-newstring}**         | 如果var未定义或为空值，则返回newstring；否则返回var的值      |
| **${var:=newstring}**         | 如果var未定义或为空值，则返回newstring，并把newstring赋给var；否则返回var的值 |
| **${var:+newstring}**         | 如果var不为空，则返回newstring；否则返回空值（其实也是var的值）  |
| **${var:?newstring}**         | 如果var未定义或为空值，则将newstring写入标准错误，本语句失败；否则返回var的值 |

## 脚本的特殊变量

![](file:///C:/Users/FUZIWANG/AppData/Local/Temp/msohtmlclip1/01/clip_image009.jpg)

# 算数运算

```c
shell支持算术运算，并且shell会对$((····))里的算数表达式进行运算。
frewen@ubuntu:~$ a=12
frewen@ubuntu:~$ b=14
frewen@ubuntu:~$ x=$(($a+$b))
frewen@ubuntu:~$ echo $x
```

注意：

- 如果b=12a，此时会报错
- 但是如果以字母开头的文本，比如b=a12，则`x=$(($a+$b))`则直接就计算为a的数值，b转成数字为0

# 逻辑运算

（1）逻辑运算：&&，||， !。分别是AND，OR，NOT。

（2）对逻辑运算来说，任何非0值都是真。

（3）在linux中，输出的是1或者是0

举例代码如下：

```c
数字格式逻辑运算：
frewen@ubuntu:~$ echo ((1&&0))// 0
frewen@ubuntu:~$ echo ((2||0))// 1

非数字格式逻辑运算：
frewen@ubuntu:~$ b=abc
frewen@ubuntu:~$ echo $(( 1 && $b ))//0
frewen@ubuntu:~$ b=12a
frewen@ubuntu:~$ echo $(( 1 && $b)) //提示错误
```

# 本节课任务

```c
· 创建脚本文件：varstudy.sh
· 赋予可执行权限
· 脚本运行时输出参数个数
· 并输出参数个数，以及程序的名称和参数字符串
· 显示当前工作目录以及用户主目录

frewen@ubuntu:~$ vim bin/varstydy.sh

#!/bin/bash
echo# 0 @ PWD $HOME
exit0

frewen@ubuntu:~$ chmod 755 bin/varstudy.sh
frewen@ubuntu:~$ bin/varstudy.sh
```

