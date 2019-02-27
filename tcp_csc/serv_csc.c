/*************************************************************************
	> File Name: serv_show.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 10:17:36 2019
 ************************************************************************/
#include "common.h"
int main(int argc, char *argv[]){
    int port, listen_socketfd ,sock_fd, pid, ;
    if(argc != 2){
        printf("Usage: ./serv_show port1!\n");
        exit(1);
    }
    
    port = atoi(argv[1]);//转化为整形

    if((listen_socketfd = socket_create(port)) < 0){
        printf("error in create socket!\n");
        return -1;
    }



    while(1){
        struct sockaddr_in client_addr;//存放客户端地址
        char name[20] = {0};
        char buff[256];
        socklen_t len = sizeof(client_addr);//sizeof需要指针
        if((sock_fd = accept(listen_socketfd, (struct sockaddr *)(&client_addr), &len)) < 0){
            perror("accept:");
            continue;
        }
        if ((pid = fork()) < 0){
            printf("error in fork!\n");
            continue;
        }
        //0为子进程
        if(pid == 0) {
            close(listen_socketfd);
            recv(sock_fd, name, 20, 0);
            printf("\033[1m\033[43;31m用户\033[0m");
            printf("\033[1m\033[43;35m%s\033[0m", name);
            printf("\033[1m\033[43;31m登录\033[0m\n");
            while(recv(sock_fd, buff, sizeof(buff), 0) > 0){
            printf("\033[1m\033[;35m%s\033[0m", name);
            printf(" : %s\n", buff);
                fflush(stdout);//强制刷新输出缓冲区，立即输出
                memset(buff, 0, sizeof(buff));//清空buff
            }
            printf("\033[1m\033[43;34m用户\033[0m");
            printf("\033[1m\033[43;35m%s\033[0m", name);
            printf("\033[1m\033[43;34m下线\033[0m\n");
            close(sock_fd);
            exit(0);

        }
        close(sock_fd);

    }
    return 0;

}
