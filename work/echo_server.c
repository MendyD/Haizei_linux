/*************************************************************************
	> File Name: echo_server.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  4/ 6 19:28:16 2019
 ************************************************************************/

#include "common.h"
int main(){
    int shmid = 0;
    shmid = create_shm(2048);
    void *addr = shmat(shmid, NULL, 0);//int shmflg 0;
    while(1){
        scanf("%[^\n]s", (char *)addr);
        getchar();
        strcat(addr,"\n");
        fflush(stdin);
        usleep(2000);
        memset(addr, 0, sizeof(addr));
    }
    shmdt(addr);
    destory(shmid);
    return 0;
}
