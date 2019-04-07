/*************************************************************************
	> File Name: echo_client.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  4/ 6 19:28:24 2019
 ************************************************************************/

#include "common.h"
int main(){
    int shmid = 0;
    shmid = get_shm(2048);
    void *addr = shmat(shmid, NULL, 0);
    while(1){
        usleep(2000);
        printf("%s", addr);
        fflush(stdout);
    }
    shmdt(addr);
    destory(shmid);
    return 0;
}

