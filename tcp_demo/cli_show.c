/*************************************************************************
	> File Name: cli_show.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 14:21:03 2019
 ************************************************************************/

#include "common.h"
int main(int argc, char *argv[]){
    int sock_fd;
    char *ip_addr = argv[1];
    int port = atoi(argv[2]);
    char *name = argv[3];
    
    if(argc != 3) {
        printf("Usage: ./cli_show IP port username \n");}

    if((sock_fd = socket_connect(port, ip_addr)) < 0){
        printf("error in connect!\n");
        return -1;
    }

    send(sock_fd, name, strlen(name) + 1, 0);
    char buff[256];
    while(1){
        scanf("%[^\n]s", buff);
        getchar();
        send(sock_fd, buff, strlen(buff), 0);
        memset(buff, 0, sizeof(buff));

    }
    close(sock_fd);
    return 0;
}
