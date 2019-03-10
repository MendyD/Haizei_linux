/*************************************************************************
	> File Name: b.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Feb 2019 21:08:46 CST
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>


void *print(){
    printf("hello world!\n");
    return NULL;
}

int main(){
    pthread_t print_t;
    printf("start!\n");
    pthread_create(&print_t, NULL, print, NULL);
    pthread_join(print_t, NULL);
    return 0;
}
