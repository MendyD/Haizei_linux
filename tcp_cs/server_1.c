/*************************************************************************
	> File Name: server_1.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 五  2/22 16:08:12 2019
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void doit(int sockfd);

int main()
{
    int server_sockfd = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    pid_t pid;

    if(server_sockfd == -1){
        printf("socket error");
        return -1;
    }

    struct sockaddr_in server_sockaddr;/*声明一个变量，类型为协议地址类型*/
    server_sockaddr.sin_family = AF_INET;/*使用IPv4协议*/
    server_sockaddr.sin_port = htons(8863);/*监听8887端口*/
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);/*绑定本机IP，使用宏定义绑定*/

    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1){
        printf("bind error");
        return -1;
    }

    if(listen(server_sockfd, 20) == -1){
        printf("listen error");
        return -1;
    }

    for( ; ; ){
        struct sockaddr_in clnt_addr;/*只是声明，并没有赋值*/
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        int clnt_sock = accept(server_sockfd, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

        if(clnt_sock == -1){
            printf("appect error");
            return -1;
        }

        if( (pid = fork()) == 0 ){
            close(server_sockfd);/*子进程不需要监听，关闭*/
            doit(clnt_sock);/*针对已连接的客户端套接字进行读写*/
        }

        close(clnt_sock);
        /*close(server_sockfd);*/
    }
}

void doit(int sockfd){

    char buff[128];
    recv(sockfd, buff, sizeof(buff), 0);
    send(sockfd, buff, sizeof(buff), 0);
}
