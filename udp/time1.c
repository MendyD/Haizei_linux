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
static int len;
void prompt_info(){
    printf("hello world\n");
}
 // 建立信号处理机制
void init_sigaction(){
    struct sigaction tact;
    tact.sa_handler= prompt_info;
    tact.sa_flags=0;
    sigemptyset(&tact.sa_mask);
    sigaction(SIGALRM,&tact, NULL);
}
void init_time(){
    struct itimerval value;
    value.it_value.tv_sec=2;
    value.it_value.tv_usec=0;
    value.it_interval= value.it_value;
    setitimer(ITIMER_REAL,&value, NULL);
}
int main(){
    init_sigaction();
    init_time();
}
