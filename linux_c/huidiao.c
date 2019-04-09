/*************************************************************************
	> File Name: huidiao.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Feb 2019 18:33:06 CST
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <string.h>
struct Mypara {
    char name[20];
    int age;
};

void *print(void *argv){
    char name[20];
    struct Mypara *para;
    para = (struct Mypara *)argv;
    printf("hello %s! you are %d years old! \n", para->name, para->age);
    return NULL;
}


int main(){
    pthread_t print_t;
    printf("start!\n");
    struct Mypara para;
    char name_in[20] = {0};
    scanf("%s", name_in);
    int age = 0;
    scanf("%d", &age);
    para.age = age;
    strcpy(para.name, name_in);
    pthread_create(&print_t, NULL, print, (void *)&para);
    pthread_join(print_t, NULL);
    return 0;
}
