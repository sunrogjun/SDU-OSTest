#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// 进程自定义的时间信号
typedef void (*sighandler_t)(int);

void sigcat()
{
    printf("父进程%d收到任务结束信号\n", getpid());
}


