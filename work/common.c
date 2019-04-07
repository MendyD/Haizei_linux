/*************************************************************************
	> File Name: common.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  4/ 6 19:27:44 2019
 ************************************************************************/

#include "common.h"
int create_shm(int size){
    int shmid;
    key_t key= ftok(".", PROJ_ID);
    if((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0){
        perror("shmget");
    }
    return shmid;
}

int get_shm(int size){
    int shmid;
    key_t key = ftok(".", PROJ_ID);
    if((shmid = shmget(key, size, IPC_CREAT)) < 0){
        perror("errget");
    }
    return shmid;
}

int destory(int shmid){
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

