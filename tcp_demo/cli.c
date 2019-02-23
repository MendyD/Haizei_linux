/*************************************************************************
	> File Name: cli.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 五  2/22 17:02:52 2019
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

int main(){
    int sockfd_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in client_sock;

    client_sock.sin_family = AF_INET;
    client_sock.sin_port = htons(8282);
    client_sock.sin_addr.s_addr = inet_addr("192.168.2.29");

    int con = connect(sockfd_client, (struct sockaddr*)(&client_sock), sizeof(struct sockaddr));
    if(con == -1){
        printf("connect wrong\n");
        perror("/root/noexitfile");
        return 1;
    }
    char name[10] = "Mendy";
    write(sockfd_client, name, sizeof(name));
    char buff[128];
    buff[sizeof(buff) - 1] = '\0';
    while(scanf("%s", buff)){
        if(send(sockfd_client, buff, sizeof(buff), 0) == -1){
            printf("send wrong\n");
        }
    }
//    close(sockfd_client);
    return 0;
}
