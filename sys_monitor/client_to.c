/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Mar 2019 14:28:13 CST
 ************************************************************************/

#include<stdio.h>
#include "common.h"
#define MAX_SIZE 1024  
int main(){
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        close(sockfd);
        return -1;
    }
    struct sockaddr_in client_addr;
    char *ip_addr = "192.168.1.40";
    int port = atoi("8731");
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = inet_addr(ip_addr);

    if((connect(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr))) < 0){
        perror("connect");
        close(sockfd);
        return -1;
    }
    
    char buff[MAX_SIZE] = {0};
    FILE *file;
    if((file = popen("ls", "r")) == NULL ){
        printf("---fopen1111\n");
    }
    while(1){
        int read = fread(buff, 1, MAX_SIZE ,file);
        fflush(stdout);
        if((send(sockfd, buff, strlen(buff), 0)) < 0){
            perror("send");
            return -1;
        }
        if(read == 0){
            break;
        }
        memset(buff, 0, sizeof(buff));
    }
    fclose(file);
    close(sockfd);
    return 0;
}
