
 
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "os3.h"

int main(int argc, char *argv[])
{
	int pidParent, pidChild; // 父进程和子进程的进程号
	
	signal(SIGINT, (sighandler_t)sigint); // SIGINT信号，优先级加１
	signal(SIGTSTP, (sighandler_t)sigtstp); // SIGTSTP信号，优先级减１
	
	pidParent = getpid();
	pidChild = fork(); // 创建子进程
	
	// 父子进程循环输出
	if (pidChild < 0)
	{
		printf("子进程创建失败！\n");
		exit(EXIT_FAILURE);
	}
	else if (pidChild > 0)
	{
		// 父进程输出
		for (int i = 0; i < 10; i++)
		{
			printf("我是父进程%d，策略为%d，优先级为%d\n", 
			pidParent, sched_getscheduler(pidParent), getpriority(PRIO_PROCESS, 0));
			sleep(4);
		}
	}
	else 
	{
		// 子进程输出
		pidChild = getpid();
		for (int i = 0; i < 10; i++)
		{
			printf("我是子进程%d，策略为%d，优先级为%d\n", 
			getpid(), sched_getscheduler(getpid()), getpriority(PRIO_PROCESS, 0));
			sleep(4);
		}
	}
	
	return EXIT_SUCCESS;	
}

