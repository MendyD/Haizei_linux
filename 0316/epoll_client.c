/*************************************************************************
	> File Name: epoll_client.c
	> Author: 
	> Mail: 
	> Created Time: Thu 04 Apr 2019 19:52:09 CST
 ************************************************************************/

#include<stdio.h>
#include "common.h"
int main(){
    int fd;
    fd = socket_connect(7731, "192.168.1.41");
    char buff[1024] = {0};
    while(scanf("%s", buff) != EOF){
        send(fd, buff, strlen(buff), 0);
        memset(buff, 0, sizeof(buff));
        recv(fd, buff, sizeof(buff), 0);
        printf("%s\n", buff);
    }
    return 0;
}
