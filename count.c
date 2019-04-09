/*************************************************************************
	> File Name: count.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  3/ 2 09:08:49 2019
***********************************************************************/
#include<stdio.h>
#include <pthread.h>
#define MAX 100
void *count(){
    int sum = 0;
    for(int i = 0; i < MAX; i++){
        sum += i;
    }
    printf("%d\n", sum);
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage : ./a.out count_no. pthread_no.\n");
    }
    for(int i = 0; i < (int)argv[2]; i++){
        pthread_t count_t[i];
        pthread_create(&count_t[i], NULL, count(i), NULL);
        pthread_join(count_t[i], NULL);
    }
    
    return 0;
}

