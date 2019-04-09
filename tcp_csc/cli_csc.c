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

struct Message{  
    char from[20];  
    int flag;
    char message[1024];
};

int main(int argc, char *argv[]){ 
    char *ip_addr = argv[1];
    int port = atoi(argv[2]);
    char *name = argv[3];
    int pid;
    struct Message mess_recv;
    if(argc < 4){
        printf("Usage: ./cli IP PORT NAME!\n");
        return -1;
    }

    int client_socketfd;
    if((client_socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("client_socketfd");
        return -1;
    }

    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);

    if((connect(client_socketfd, (struct sockaddr*)(&server_addr), sizeof(server_addr))) < 0){
        perror("connect");
        close(client_socketfd);
        return -1;
    }
    send(client_socketfd, name, strlen(name) + 1, 0);
    
    if((pid = fork()) < 0){
        printf("error in fork\n");
        return -1;
    }

	if(pid == 0){
        while(recv(client_socketfd, (char *)&mess_recv, sizeof(mess_recv), 0) > 0) {
           // freopen("conf.log", "a", stdout);
            printf("\033[1m\033[43;34m%s\033[0m : %s\n", mess_recv.from, mess_recv.message);
           // fclose(stdout);
	        fflush(stdout);
	    }
    }

    while(1){
        char  buff[256] = {0};
        scanf("%[^\n]s", buff);
        getchar();
        send(client_socketfd, buff, strlen(buff), 0);
        memset(buff, 0, sizeof(buff));       
    }
    close(client_socketfd);
    return 0;
}
