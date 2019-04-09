/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Mar 2019 14:26:44 CST
 ************************************************************************/

#include<stdio.h>
#include "common.h"
int main(){
    int sockfd, connSockFd;
    char tempServPort[6] = {0};
    char tempConnPort[6] = {0};
    char tempConnIp[20] = {0};
    int server_port, connect_port;
    char *config = "./chat_c.conf";
    get_conf_value(config, "Server_Port", tempServPort);//8733
    get_conf_value(config, "Connect_Port", tempConnPort);//10000
    get_conf_value(config, "Connect_Ip", tempConnIp);
    server_port = atoi(tempServPort);
    connect_port = atoi(tempConnPort);
    if((sockfd = socket_create(server_port)) < 0){
        perror("socket_create");//socket, bind, listen
        return -1;
    }

    if((connSockFd = socket_connect(connect_port, tempConnIp)) < 0){
        perror("connect");
        return -1;
    }
    send(connSockFd, "100", sizeof(int), 0);

    return 0;
}
