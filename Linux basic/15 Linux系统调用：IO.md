# open函数

 open函数用于打开文件操作，打开指定的文件

> int open(const char *pathname, int flags, mode_t mode); 

参数依次为**文件路径名称**，**标志位**，**模式**。成功返回值为打开的文件描述符，错误返回-1。
flags选项：

- O_CREAT 没有则创建文件
- O_WRONLY 写模式打开文件
- O_RDONLY 只读模式打开文件
- O_RDWR 读写方式打开

mode选项：

- S_IRWXU 文件所有者具有可读，可写，可执行的权限
- S_IRUSR 文件所有者有可读权限
- S_IWUSR 文件所有者具有可写权限

## open函数实例

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char * argv[])
{
  	if(argc<2)
  	{
  		dprintf("Error:less arguments!\n");
      	return -1;
	}
  	int fd = open(argv[1],O_CREAT,S_IRUSR|S_IWUSR);
  	if(fd<0)
    {
  		perror("open error\n");
      	return -1;
	}
  	close(fd);// 打开的文件需要进行关闭 open和close是配套使用的
  	return 0;
}
// 执行函数
frewen@Ubuntu：~/c$ ./creat op_cl// 创建了一个名字为op_cl的文件
```

# close函数

在文件操作最后要记得使用close关闭打开的文件

> int close(int fd); // close函数成功返回0，错误返回-1。

# read函数

read函数从一个文件读取数据：

> ssize_t read(int fd, const void *buf, int count);

参数依次为**打开的文件描述符，指向数据的指针，要读取的字节数**。**返回值是成功读取的字节数**，如果有错误则返回-1。

## read函数实例

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char * argv[])
{
  	int fd = open("op_cl",O_RDONLY);
  	if(fd<0)
    {
  		perror("open error\n");
      	return -1;
	}
  	char buf[1024] = {'\0'};
  	int count = 0;
  	count = read(fd,buf,1000);
  	if(count < 0)
      	perror("read error\n");
  	else
      	printf("%s--read:%d bytes",buf,count);
  	close(fd);// 打开的文件需要进行关闭 open和close是配套使用的
  	return 0;
}
```

# write函数

write函数向一个文件写入数据：

> ssize_t write(int fd, const void *buf, int count);

参数依次为**打开的文件描述符，指向数据的指针，要写入的字节数**。返回值是成功写入的字节数，错误则返回-1。

## write函数实例

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char * argv[])
{
  	/*
  		* 在末尾进行追加：O_APPEND
  		* 将长度置为0(会截断文件长度为0)：O_TRUNC
		（O_WRONLY或O_RDWR配合O_TRUNC会导致这种效果）
  	*/
  	int fd = open("op_cl",O_WRONLY|O_APPEND);
  	if(fd<0)
    {
  		perror("open error\n");
      	return -1;
	}
  	char * buf = "Hello\n Linux\n"
  	int count = 0;
  	count = write(fd,buf,strlen(buf));
  	if(count < 0)
      	perror("write error\n");
  	else
      	printf("write:%d bytes",count);
  	close(fd);// 打开的文件需要进行关闭 open和close是配套使用的
  	return 0;
}
```

## 综合练习

编写一个简单的复制命令：接受两个参数，第一个参数作为要复制的文件，第二个参数是要复制的文件名

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char * argv[])
{
  	int fd1 = open(argv[1],O_RDONLY);
  	int fd2 = open(argv[2],O_WRONLY);
  	if(fd1<0 || fd2<0)
    {
  		perror("open error\n");
      	return -1;
	}
  	char * buf = "\0";
  	int count = 0;
  	while(count = read(fd1,buf,strlen(buf))>0)// 为什么非要用while循环呢
  	{
  		write(fd2,buf,count);
	}
  	close(fd1);// 打开的文件需要进行关闭 open和close是配套使用的
  	close(fd2);
  	return 0;
}
```

# IO重定向

IO重定向基于这样一个设计原则：**最低可用文件描述符**（Lowest Availablefd）原则。即：**在打开文件时，分配的描述符总是数组中最低可用的索引位置（索引数字最小的位置）。**

文件描述符是一个数组索引号，每个进程都有一组打开的文件，这些打开的文件信息保存在一个数组中，文件描述符就是数组的索引号。（一般来说0,1,2是标准输入，标准输出，标准错误输出）

在Linux上，使用0，1，2作为程序的标准输入，标准输出，标准错误输出。而如果关闭描述符1，然后打开其他文件，这样文件就被分配了文件描述符1，于是标准输出就会写入到新打开的文件。这就是IO重定向。

## 编程实现的方式（以文件描述符1为例）

```c
(1)方式一：
/*
close-open-close方式，先close(1)，然后open(filename, O_RDWR,S_IWUSR); 操作完成，close关闭新打开的文件。
*/
(2)方式二：
/*
open-close-dup-close方式，open打开文件，返回的文件描述符不是1，然后close(1)，现在最低可用描述符是1，dup(fd)会把新打开的描述符复制到1，然后close(fd)关闭新打开的文件。
*/
(3)方式三：
/*
open-dup2-close方式，dup2(oldfd, newfd)，关闭newfd，把oldfd复制到newfd，close关闭新打开的描述符。
*/
```

## IO重定向实例

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char * argv[])
{
  	int fd = open("ioout",O_WRONLY|O_APPENF|OCREAT,S_IRUSR|S_IRWUSR);
  	//close(1);
  	if(fd<0)
    {
  		perror("open error\n");
      	return -1;
	}
  	//dup(fd);
  	dup2(fd,1);//关闭fd，把1复制到fd
  	close(fd);
  	return 0;
}
```

