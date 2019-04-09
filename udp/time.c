/*************************************************************************
	> File Name: time.c
	> Author: 
	> Mail: 
	> Created Time: Wed 20 Mar 2019 19:39:34 CST
 ************************************************************************/
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
static char msg[]= "time is running out\n";
static int len;
//向标准错误输出信息，告诉用户时间到了
 void prompt_info(int signo){
 write(STDERR_FILENO, msg, len);}
 // 建立信号处理机制
void init_sigaction(void){
    struct sigaction tact;
    tact.sa_handler= prompt_info;
    tact.sa_flags=0;
    /*初始化信号集*/
    sigemptyset(&tact.sa_mask);
    /*建立信号处理机制*/
    sigaction(SIGALRM,&tact, NULL);
}
void init_time(){
    struct itimerval value;
    /*设定初始时间计数为2秒0微秒*/
    value.it_value.tv_sec=2;
    value.it_value.tv_usec=0;
    /*设定执行任务的时间间隔也为2秒0微秒*/
    value.it_interval= value.it_value;
    /*设置计时器ITIMER_REAL*/
    setitimer(ITIMER_REAL,&value, NULL);
}
int main(){
    len =strlen(msg);
    init_sigaction();
    init_time();
    while(1);
    exit(1);
}
