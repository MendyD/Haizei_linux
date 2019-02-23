/*************************************************************************
	> File Name: server.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 五  2/22 14:47:51 2019
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

#define _PORT_ 9999
#define _BACKLOG_ 10

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server_socket;
    struct sockaddr_in client_socket;                                           
    bzero(&server_socket, sizeof(server_socket));
    server_socket.sin_family = AF_INET;
    server_socket.sin_addr.s_addr = htonl(INADDR_ANY);
    server_socket.sin_port = htons(_PORT_);

    if(bind(sock, (struct sockaddr*)&server_socket, sizeof(struct sockaddr_in)) < 0)
    {
        perror("bind");
        close(sock);
        exit(2);
    }

    if(listen(sock, _BACKLOG_) < 0)
    {
        perror("listen");
        close(sock);
        exit(3);
    }

    printf("bind and listen success, wait accept..\n");

    while(1)
    {
        socklen_t len = 0;                                                      
        int client_sock = accept(sock, (struct sockaddr*)&client_socket, &len);
        if(client_sock < 0)
        {
            perror("accept");
            close(sock);
            exit(4);
        }
        char buf_ip[INET_ADDRSTRLEN];
        memset(buf_ip, '\0', sizeof(buf_ip));
        inet_ntop(AF_INET,&client_socket.sin_addr, buf_ip, sizeof(buf_ip));
        printf("get connect, ip is : %s port is : %d\n",buf_ip, ntohs(client_socket.sin_port));
        while(1)
        {
            char buf[1024];
            memset(buf, '\0',sizeof(buf));
            read(client_sock, buf, sizeof(buf));
            printf("client#:%s\n",buf);
            printf("server#:");

            memset(buf, '\0', sizeof(buf));
            fgets(buf, sizeof(buf), stdin);
            buf[strlen(buf)-1] = '\0';
            write(client_sock, buf, strlen(buf)+1);
            printf("please wait...\n");                                         
        }
    }
    close(sock);
    return 0;
}
