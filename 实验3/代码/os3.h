#ifndef EXP3_H_INCLUDED
#define EXP3_H_INCLUDED

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// 进程自定义的时间信号
typedef void (*sighandler_t)(int);

void sigint()
{
	// 进程收到SIGINT信号（在控制台输入Ctrl+C），优先数加１
    int pri = 0;
    pri = getpriority(PRIO_PROCESS, 0); // 获取当前进程的优先级
    if (pri >= -20 && pri < 19)
		pri += 1;
	printf("当前进程为%d，优先级+1\n", getpid());
    setpriority(PRIO_PROCESS, getpid(), pri);
}

void sigtstp()
{
	// 进程收到SIGTSTP信号（在控制台输入Ctrl+Z），优先数减１
	int pri  = 0;
	pri = getpriority(PRIO_PROCESS, 0); //　获取当前进程的优先级
	if (pri > -20 && pri <= 19)
		pri -= 1;
	printf("当前进程为%d，优先级-1\n", getpid());
	setpriority(PRIO_PROCESS, getpid(), pri);
}

#endif // EXP3_H_INCLUDED

