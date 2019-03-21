/*************************************************************************
	> File Name: client_cw.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 日  3/17 18:17:38 2019
 ************************************************************************/

#include<stdio.h>
#include "../sys_monitor/common.h"
int main(){

    int sockfd;
    for(int i = 0; i < 88; i++){
        sockfd = socket_connect(8733, "192.168.1.41");
        close(sockfd);
    }
    return -1;

}
