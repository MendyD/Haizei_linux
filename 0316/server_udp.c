/*************************************************************************
	> File Name: server_udp.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 二  3/19 21:00:05 2019
 ************************************************************************/

#include<stdio.h>
#include "common.h"
int main(){
    char *config = "./chat_c.conf";
    char buff[255] = {0};
    char temp_port[5] = {0};
    int port;
    int fd;
    get_conf_value(config, "Server_Port", temp_port);
    port = atoi(temp_port);

    struct sockaddr_in addr;

    if((fd = udp_socket_create(port, &addr)) < 0){
        perror("udp_socket_create");
        return -1;
    }

    socklen_t len = sizeof(addr);
    int len_recv;
    while(1){
        if((len_recv = recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr*)(& addr), &len)) < 0){
            perror("recvfrom");
            return -1;
        }
        printf("recv_buff = %s\n", buff);
        printf("recv_length = %d\n", len_recv);
        printf("-----------------------------\n");
        fflush(stdout);
        memset(buff, 0, sizeof(buff));
    }
    close(fd);
    return 0;
}
