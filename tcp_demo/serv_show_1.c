/*************************************************************************
	> File Name: serv_show.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 10:17:36 2019
 ************************************************************************/
#include "common.h"
int main(int argc, char *argv[]){
    int port, server_listen, sock_fd, pid;
    if(argc != 2){
        printf("Usage: ./serv_show port1!\n");
        exit(1);
    }
    
    port = atoi(argv[1]);//转化为整形

    if((server_listen = socket_create(port)) < 0){
        printf("error in create socket!\n");
        return -1;
    }

    while(1){
        struct sockaddr_in client_addr;//存放客户端地址
        char name[20] = {0};
        char buff[256];
        socklen_t len = sizeof(client_addr);//sizeof需要指针
        if((sock_fd = accept(server_listen, (struct sockaddr *)(&client_addr), &len)) < 0){
            perror("accept:");
            continue;
        }
        if ((pid = fork()) < 0){
            printf("error in fork!\n");
            continue;
        }
        //0为子进程
        //父进程里pid 返回子进程pid
        //子进程里返回0
        if(pid == 0) {
            close(server_listen);
            recv(sock_fd, name, 20, 0);
            printf("用户%s登录\n", name);
            while(recv(sock_fd, buff, sizeof(buff), 0) > 0){
                printf("%s : %s\n", name, buff);
                fflush(stdout);//强制刷新输出缓冲区，立即输出
                memset(buff, 0, sizeof(buff));//清空buff
            }
            printf("%s下线\n", name);
            close(sock_fd);
            exit(0);

        }
        close(sock_fd);

    }
    return 0;

}
