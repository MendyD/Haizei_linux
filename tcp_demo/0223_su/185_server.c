/*************************************************************************
	> File Name: 185_server.c
	> Author: 
	> Mail: 
	> Created Time: Sat 23 Feb 2019 10:16:15 CST
 ************************************************************************/

#include<stdio.h>
#include"common1.h"
int main(int argc, char *argv[]) {
    int port, server_listen, sock_fd;

    if (argc != 2) {
        printf("Usage: ./185_test port!\n");
        exit(1);
    }
    
    port = atoi(argv[1]);
    
    if ((server_listen = socket_create(port)) < 0) {
        printf("Error in create socket!\n");
        return -1;
    }

    while (1) {
        struct sockaddr_in client_addr;
        char name[20] = {0};
        char buff[256] = {0};
        int pid = 0;
        int len = sizeof(client_addr);
        if ((sock_fd = accept(server_listen, (struct sockaddr*)&client_addr, &len)) < 0) {
            perror("accept");
            continue;
        }
        if ((pid = fork()) < 0) {
            printf("Error in Fork!\n");
            continue;
        }
        if (pid == 0) {
            close(server_listen);
            recv(sock_fd, name, 20, 0);
            printf("%s 上线！\n", name);
            while( recv(sock_fd, buff, sizeof(buff), 0) > 0) {
                printf("%s: %s\n", name, buff);
                fflush(stdout);
                memset(buff, 0, sizeof(buff));
            }
            printf("%s 下线\n", name);
            close(sock_fd);
            exit(0);
        } 
        close(sock_fd);
    }

    perror("nothing");
    return 0;
}
