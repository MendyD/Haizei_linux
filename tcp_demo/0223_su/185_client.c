/*************************************************************************
	> File Name: 185_client.c
	> Author: 
	> Mail: 
	> Created Time: Sat 23 Feb 2019 14:26:47 CST
 ************************************************************************/

#include "common1.h"

int main(int argc, char *argv[]) {
    int sock_fd;
    char buff[256] = {0};
    if (argc != 4) {
        printf("Usage: ./185_client IP port username\n");
        exit(1);
    }
    char *ip_addr = argv[1];
    int port = atoi(argv[2]);
    char *name = argv[3];
    
    if ((sock_fd = socket_connect(port, ip_addr)) < 0) {
        printf("Error in connect!\n");
        return -1;
    }

    send(sock_fd, name, strlen(name) + 1, 0);
    
    while(1) {
        scanf("%[^\n]s", buff);
        getchar();
        send(sock_fd, buff, strlen(buff), 0);
        memset(buff, 0, sizeof(buff));
    }
    
    close(sock_fd);
    return 0;
}

