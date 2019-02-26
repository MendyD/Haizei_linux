/*************************************************************************
	> File Name: cli.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course:task855实现可以接收私信
	> Created Time: 六  2/23 20:11:22 2019
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>//socket、sockaddr
#include <unistd.h>//close
#include<netinet/in.h>//sockaddr_in
#include <stdlib.h>//atoi
#include <arpa/inet.h>//inet_addr、htoni
#include <string.h>
#include "common.h"
int main(int argc, char *argv[]){ 



    char *ip_addr = argv[1];
    int port = atoi(argv[2]);
    char *name = argv[3];
    if(argc < 4){
        printf("Usage: ./cli IP PORT NAME!\n");
        return -1;
    }

    /*socket*/
    int client_socketfd, listen_socketfd, accept_socketfd;
    if((client_socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("client_socketfd");
        return -1;
    }
    if((listen_socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("listen_socketfd");
        return -1;
    }

    /*struct sockaddr_in 要连接的server_addr, 自己进行通讯的client_addr*/
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(8732);//绑定监听的端口
    client_addr.sin_addr.s_addr = INADDR_ANY;


    if((bind(listen_socketfd, (struct sockaddr*)(&client_addr), sizeof(client_addr))) < 0){
        perror("bind");
        close(listen_socketfd);
        return -1;
    }

    if((listen(listen_socketfd, 20)) < 0){
        perror("listen");
        close(listen_socketfd);
        return -1;
    }

    if((connect(client_socketfd, (struct sockaddr*)(&server_addr), sizeof(server_addr))) < 0){
        perror("connect");
        close(client_socketfd);
        return -1;
    }
    
    send(client_socketfd, name, strlen(name) + 1, 0);
    
    int pid;
    char buff[256];
    socklen_t len = sizeof(server_addr);
        
    struct Message{  
     char from[20];  
     int flag;//若flag为1则为私聊信息，0为公聊信息，2则为服务器的通知信息  
     char message[1024];
    };

    struct Message mess_recv;
    if((pid = fork()) < 0){
        printf("error in fork\n");
        return -1;
    }

    
	if(pid == 0){
	    
        close(client_socketfd);

        while(1){
            
            if((accept_socketfd = accept(listen_socketfd, (struct sockaddr *)(&server_addr), &len)) < 0){
                perror("accept");
                return -1;
            }
	    
            while(recv(accept_socketfd, (char *)&mess_recv, sizeof(mess_recv), 0) > 0) {
                printf("\033[1m\033[43;34m%s\033[0m : %s\n", mess_recv.from, mess_recv.message);
	            fflush(stdout);
	        }
            //close(listen_socketfd);
        }
    }

    close(listen_socketfd);
    while(1){
        scanf("%[^\n]s", buff);
        getchar();
        send(client_socketfd, buff, strlen(buff), 0);
        memset(buff, 0, sizeof(buff));       
    }
    close(client_socketfd);
    close(accept_socketfd);
    return 0;
}
