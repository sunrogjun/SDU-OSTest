/*
 * Filename: os1.c
 * Copyright: 2023 by srj 
 * Function: 父子协作进程,父进程创建一个子进程并控制它每隔 3 秒显示一次当前目录中的文件名列表。
 */

#include "os1.h"

int main(int argc, char *argv[])
{
	int i;
	int pid; // 存放子进程号
	int status; // 存放子进程返回状态
	int count; // 记录执行次数
	count = 1;
	char *args[] = {"/bin/ls", "-l", NULL}; // 子进程需要执行的命令
	signal(SIGCONT, (sighandler_t)sigcat); 
	
	pid = fork(); // 建立子进程
	if (pid < 0)
	{
		// 建立子进程失败
		printf("子进程创建失败！\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		while(1)
		{
			// 子进程执行代码段
			printf("我是子进程%d，我的父进程是%d\n", getpid(), getppid());
			printf("开始执行任务：显示当前目录中文件名列表\n");
			pid = fork(); // 用新创建的子进程实现exec函数，否则当前子进程中的内容会被覆盖
			if (pid == 0)
				status = execve(args[0], args, NULL); // 装入并执行程序
			else
			{
				waitpid(pid, &status, 0); // 等待新创建的子进程结束
				kill(getppid(), SIGCONT); // 通知父进程继续执行
				pause(); // 执行父进程，子进程等待父进程的开始信号
			}
		}
	}
	else
	{
		
		// 父进程执行代码段
		printf("开始第%d次执行\n", count);
		printf("我是父进程%d，接下来交给子进程%d\n", getpid(), pid);
		pause(); // 执行子进程，等待子进程任务结束信号
		printf("第%d次执行结束，休眠3秒\n", count++);
		sleep(3);
		printf("\n");
		while (1)
		{
			printf("开始第%d次执行\n", count);
			printf("我是父进程%d，接下来交给子进程%d\n", getpid(), pid);
			kill(pid, SIGCONT); // 向子进程发送开始信号
			pause(); // 等待子进程任务结束信号
			printf("第%d次执行结束，休眠3秒\n", count++);
			sleep(3);
			printf("\n");
		}
	}
	
	return EXIT_SUCCESS;
}
