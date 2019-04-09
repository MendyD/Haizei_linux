/*************************************************************************
	> File Name: a.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 16:33:47 2019
 ************************************************************************/
 #include "common.h"

int main(int argc, char *argv[]){
    char *host = argv[1];
    struct sockaddr_in sock_addr;
    sock_addr.sin_addr.s_addr = inet_addr(host);

    for(int i = 0; i < 3; i++){
        int a = sock_addr.sin_addr.s_addr & 255;
        sock_addr.sin_addr.s_addr = sock_addr.sin_addr.s_addr >> 8;
        printf("%d.",a);
    }
    int a = sock_addr.sin_addr.s_addr & 255;
    sock_addr.sin_addr.s_addr = sock_addr.sin_addr.s_addr >> 8;
    printf("%d\n", a);
    return 0;
 }
