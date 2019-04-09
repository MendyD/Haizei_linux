/*************************************************************************
	> File Name: sum_pthread.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  3/ 2 09:44:16 2019
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <inttypes.h>
int64_t end, now, start, sum;
pthread_mutex_t now_t;//加锁

void *add(){
    while(1){
        pthread_mutex_lock(&now_t);
        if(now > end){
            pthread_mutex_unlock(&now_t);
            break;
        }
        sum += now;
        now++;
        pthread_mutex_unlock(&now_t);
    }
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage:./a.out num num_of_pthread!\n");
        return -1;
    }
    int num_of_pthread = atoi(argv[2]);
    end = atoi(argv[1]);
    pthread_t tid[num_of_pthread];
    now = 0;
    sum = 0;
    for(int i = 0; i < num_of_pthread; ++i){
        pthread_create(&tid, NULL, add, NULL);//线程， 参数，函数指针，参数
    }
    //等待所有线程
    for(int i = 0; i < num_of_pthread; ++i){
        pthread_join(tid[i], NULL);//相当于wait等待tid结束，回收资源
    }
    printf("sum = %lld\n", sum);

    return 0;
}
