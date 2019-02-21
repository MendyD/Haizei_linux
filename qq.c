/*************************************************************************
	> File Name: qq.c
	> Author: 
	> Mail: 
	> Created Time: Thu 21 Feb 2019 17:39:57 CST
 ************************************************************************/

#include<stdio.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>    
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>


int main(){
    char buf[100];
    int num;
    int client_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(client_sockfd == -1){
        printf("socket error\n");
        return -1;
    }
    
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8731);
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.40");

    if(connect(client_sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        printf("connect error\n");
        return -1;
    }

    char str[64];
    send(client_sockfd,str,64,0);
    printf("%s\n", str);

    close(client_sockfd);
    return 0;
}
