# 系统编程简介

系统编程就是调用Linux系统提供的API（方法）完成需要的任务。

Linux上的大多数命令都是用C编写的，多数都需要用到系统调用。

```c
//man命令是Linux下的帮助指令，通过man指令可以查看Linux中的指令帮助、配置文件帮助和编程帮助等信息。
/*
man参数的确定:
	1是普通的命令
	2是系统调用,如open,write之类的(通过这个，至少可以很方便的查到调用这个函数，需要加什么头文件)
	3是库函数,如printf,fread
*/
frewen@ubuntu:~$ man ls // 默认调用的是1,等价于man 1 ls
frewen@ubuntu:~$ man 2 open // 查看系统的接口文档
frewen@ubuntu:~$ man 3 printf // 查看系统的库函数
frewen@ubuntu:~$ man syscalls // 查看系统的所有调用
```

# 获取自己的PID

系统调用：getpid();

程序如下：

```c
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(void)
{
  	printf("My pid %d",getpid());
  	printf("My parent pid %d",getppid());
  	return 0;
}
```

# fork创建子进程

## 调用fork函数，创建子进程

系统调用：fork();

- fork会创建子进程，调用fork，新创建的进程会和父进程一样继续执行。

- fork出错返回**-1**，并且不会创建新的进程；如果fork正确，则在父进程返回创建子进程的PID，在子进程中pid返回的是0。

  ![frok流程](C:\Users\FUZIWANG\Pictures\csdn\linux\fork.png)

  ​

- 由于父进程和子进程不同的返回值。可以**通过判断返回值**控制父进程和子进程执行不同的代码。

```c
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(void)
{
  	int pid = 0;
  	pid = fork();
  	printf("当前的pid值为：%d\n",pid);
  	printf("My pid %d\n",getpid());//返回当前自身的pid
  	printf("My parent pid %d\n",getppid());// 返回父进程的pid
  	return 0;
}
/*
	当前的pid值为：1481
	My pid 1480
	My parent pid 1358// shell的pid为1358,shell是父进程的父进程
	当前的pid值为：0
	My pid 1481
	My parent pid 1父进程先于子进程退出，子进程被init进程接管
*/
```

## 等待子进程退出

系统调用：wait(int *status);

- wait等待子进程退出，并把子进程退出状态设置到status变量。返回退出进程的PID。
- wait调用会挂起父进程，直到子进程退出。

`类似的调用还有waitpid(pid_t pid, int *status, intoptions);详细说明可在终端运行man 2 waitpid查看。`

> wait调用相当于调用waitpid(-1, &status, 0);

```c
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main(void)
{
  	int pid = 0;
  	int status = 0;
  	pid = fork();
  	if(pid == -1)
    {
      	perror("fork");
		return -1;	
	}
  	else if(pid > 0)
    {
  		printf("I am parent,wait child running\n");
      	wait(&status);//不是很理解
      	printf("child exited\n");
	}
  	else
    {
  		sleep(2);
		printf("I am child,my parent:%d",getppid());
	}
}
/*
父进程先于子进程退出，子进程被init进程接管
父进程退出后，子进程继续执行，此时父进程是init（ID为1的进程）。而在终端运行程序，当前shell是父进程的父进程，但是由于父进程的提前退出，导致子进程被init进程接管。(shell也就不再管理)
*/
```

