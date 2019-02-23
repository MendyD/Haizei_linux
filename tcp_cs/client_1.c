/*************************************************************************
	> File Name: client_1.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 五  2/22 16:10:11 2019
 ************************************************************************/

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
    int sock_cli = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);

    if(sock_cli == -1){
        printf("socket error");
        return -1;
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;/*使用IPv4协议*/
    servaddr.sin_port = htons(8863);/*需要连接的远程服务器端口*/
    servaddr.sin_addr.s_addr = inet_addr("192.168.2.29");/*需要连接的远程服务器IP*/

    if(connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr))  == -1){
        printf("connect error");
        return -1;
    }
    for( ; ; ){
        char buff[128];
        send(sock_cli, buff, sizeof(buff), 0);
        
    }

    close(sock_cli);
}
