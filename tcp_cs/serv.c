/*************************************************************************
	> File Name: serv.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 五  2/22 17:03:36 2019
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
    int sockfd_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    struct sockaddr_in server_sock;

    bzero(&server_sock, sizeof(server_sock));
    server_sock.sin_family = AF_INET;
    server_sock.sin_port = htons(8282);
    server_sock.sin_addr.s_addr = /*inet_addr("192.168.2.29");*/INADDR_ANY;

    while(bind(sockfd_server, (struct sockaddr*)(&server_sock), sizeof(struct sockaddr)) == -1){
        printf("bind wrong\n");
        perror("/root/noexitfile");
    }

    while(listen(sockfd_server,100) == -1){
        printf("listen wrong\n");
    }

    socklen_t len = 0;
    struct sockaddr_in client_socket;
    int accept_fd = accept(sockfd_server, (struct sockaddr*)&client_socket, &len);

    printf("用户:");
    char name[10];
    write(accept_fd, name, strlen(name) + 1);
    
    char buff[128];
    int buff_char;

    while((buff_char = recv(accept_fd, buff, sizeof(buff), 0)) > 0){
        printf("%s\n",buff);
    }
    close(accept_fd);
    close(sockfd_server);
    return 0;
}
