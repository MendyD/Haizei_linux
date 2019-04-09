/*************************************************************************
	> File Name: client_udp.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 二  3/19 20:28:01 2019
 ************************************************************************/

#include<stdio.h>
#include "common.h"
int main(){
    char *config = "./chat_c.conf";
    char temp_port[5] = {0};
    char temp_ip[20] = {0};
    int port;
    int fd;
    char buff[255] = {0};

    get_conf_value(config, "Server_Port", temp_port);
    get_conf_value(config, "Server_Ip", temp_ip);
    port = atoi(temp_port);
   
    struct sockaddr_in addr;

    if((fd = udp_socket_connect(port, temp_ip, &addr)) < 0){
        perror("socket");
        return -1;
    }

    while(1){
        scanf("%[^\n]s", buff);
        getchar();
        int len_sendto;
        if((len_sendto = sendto(fd, buff, strlen(buff), 0, (struct sockaddr*)(&addr), sizeof(addr))) < 0){
            perror("sendto");
            return -1;
        }
        printf("sendto_buff = %s\n", buff);
        printf("sendto_length = %d\n", len_sendto);
        printf("---------------------------\n");
        fflush(stdout);

    }
    
    close(fd);
    return 0;
}
