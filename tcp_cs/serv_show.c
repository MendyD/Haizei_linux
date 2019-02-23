/*************************************************************************
	> File Name: serv_show.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 10:17:36 2019
 ************************************************************************/
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

#include<stdio.h>
int main(int argc, char *argv[]){
    int port, server_listen, sock_fd, pid;
    if(argc != 2){
        printf("Usage: ./serv_show port1!\n");
        exit(1);
    }

    port = atoi(argv[1]);//转化为整形

    struct sockaddr_in server_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   
    if((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create socket:");
        return -1;
    }

    if(bind(server_listen, (struct sockaddr*)(&server_addr), sizeof(server_addr)) < 0){
        perror("bind:");
        close(server_listen);
        return -1;
    }

    if(listen(server_listen, 20) < 0){
        perror("listen:");
        close(server_listen);
        return -1;
    }

    while(1){
        struct sockaddr_in client_addr;//存放客户端地址
        char name[20] = {0};
        char buff[256];
        socklen_t len = sizeof(client_addr);//sizeof需要指针
        if((sock_fd = accept(server_listen, (struct sockaddr *)(&client_addr), &len)) < 0){
            perror("accept:");
            continue;
        }
        if ((pid = fork()) < 0){
            printf("error in fork!\n");
            continue;
        }
        //0为子进程
        //父进程里pid 返回子进程pid
        //子进程里返回0
        if(pid == 0) {
            close(server_listen);
            recv(sock_fd, name, 20, 0);
            printf("用户%s登录\n", name);
            while(recv(sock_fd, buff, sizeof(buff), 0) > 0){
                printf("%s : %s\n", name, buff);
                fflush(stdout);//强制刷新输出缓冲区，立即输出
                memset(buff, 0, sizeof(buff));//清空buff
            }
            printf("%s下线\n", name);
            close(sock_fd);
            exit(0);

        }
        close(sock_fd);

    }
    return 0;

}
