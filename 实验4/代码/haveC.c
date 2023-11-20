#include "ipc.h"
int main(int argc,char *argv[])
{
    int rate;
//可在在命令行第一参数指定一个进程睡眠秒数，以调解进程执行速度
    if(argv[1] != NULL)
        rate = atoi(argv[1]);
    else
        rate = 1; //不指定为 1 秒
//共享内存 使用的变量
    buff_key = 101; //缓冲区任给的键值
    buff_num = 1; //缓冲区任给的长度
    cget_key = 103; //消费者取产品指针的键值
    cget_num = 1; //指针数
    shm_flg = IPC_CREAT | 0644; //共享内存读写权限
//获取缓冲区使用的共享内存，buff_ptr 指向缓冲区首地址
    buff_ptr = (char *)set_shm(buff_key,buff_num,shm_flg);
//获取消费者取产品指针，cget_ptr 指向索引地址
    cget_ptr = (int *)set_shm(cget_key,cget_num,shm_flg);
//信号量使用的变量
    ab_key = 201;//有C的消费者控制键值
    ac_key = 202;//有B的消费者控制键值
    bc_key = 203;//有A的消费者控制键值
    all_key = 204;//对一个缓冲区的控制键值
    produce_key = 205;//对两个生产者的同步键值
    sem_flg = IPC_CREAT | 0644;
//生产者同步信号灯初值设为缓冲区最大可用量
    sem_val = buff_num;
//获取生产者同步信号灯，引用标识存 all_int
    all_int = set_sem(all_key,sem_val,sem_flg);
//消费者初始无产品可取，同步信号灯初值设为 0
    sem_val = 0;
    ab_int = set_sem(ab_key,sem_val,sem_flg);
//    ac_int = set_sem(ac_key,sem_val,sem_flg);
//    bc_int = set_sem(ab_key,sem_val,sem_flg);
//生产者互斥信号灯初值为 1
//    sem_val = 1;
//获取生产者互斥信号灯，引用标识存 produce_int
//    produce_int = set_sem(produce_key,sem_val,sem_flg);
    while(1)
    {
        down(ab_int);
        sleep(rate);
        printf("%d  3号吸烟者得到了:胶水和烟草 [%d]%c\n",getpid(),*cget_ptr ,buff_ptr[*cget_ptr]);
        *cget_ptr = (*cget_ptr+1) % buff_num;
        up(all_int);
    }
    return EXIT_SUCCESS;
}


